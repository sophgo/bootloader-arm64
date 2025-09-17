import serial,threading,time
import os
import subprocess
import socket
from socket import error as SocketError
import errno
import configparser
import re


class GTserialCom():
    def __init__(self, ttyusb, name, mode):
        self.ttyusb = ttyusb
        self.name = name
        self.mode = mode
        self.status = True
        self.rec_state = False
        self.send_state = True

        self.intf = self.find_interface()
        print(self.intf)

    def find_interface(self):
        cmd = "ip link show"
        err, result = subprocess.getstatusoutput(cmd)
        if err:
            raise Exception("Failed to list network interfaces")

        pattern = re.compile(r"^\d+: (wwan\w+|wwx\w+|enx\w+|usb\w+|):", re.MULTILINE)
        matches = pattern.findall(result)

        if matches:
            cmd = f"ifconfig {matches[0]} 0.0.0.0"
            err, result = subprocess.getstatusoutput(cmd)
            if err:
                raise Exception("Failed to init interface")
            cmd = f"ifconfig {matches[0]} down"
            err, result = subprocess.getstatusoutput(cmd)
            if err:
                raise Exception("Failed to init interface")
            return matches[0]
        else:
            raise Exception("No suitable interface found")

    def send(self):
        print("SerialCom send thread start")
        while self.send_state:
            self.serial.write(str('AT+CPIN? \r').encode('utf-8'))
            time.sleep(1)
            self.serial.write(str('AT+CPIN? \r').encode('utf-8'))
            time.sleep(3)
            self.serial.write(str('AT+COPS? \r').encode('utf-8'))
            if self.rec_state == False:
                self.rec_state = True
                self.send_state = False
                self.rec_thread.start()

    def received(self):
        print("serialCom received thread start")

        while self.rec_state:
            while self.serial.inWaiting() > 0:
                self.out = self.serial.read(128)
                print(self.out)
                self.simstatus = 'UINIT'
                if len(str(self.out).split(': ')) > 1:
                    self.simstatus = (str(self.out).split(': ')[
                                      1]).split('\\')[0]

                print(self.simstatus)
                if self.simstatus == 'READY' and len(str(self.out).split('"')) > 1:
                    self.operator = str(self.out).split('"')[1]
                else:
                    self.operator = 'NULL'
                print(self.operator)
                self.rec_state = False
                self.mon_thread.start()

    def send_msg(self, msg):
        self.serial.write(str(msg).encode('utf-8'))

    def recv_msg(self):
        self.recv = []
        start_time = time.time()
        timeout = 10
        while self.serial.isOpen():
            self.data = self.serial.readline()
            self.recv.append(self.data)
            if self.data == b'OK\r\n' or self.data == b'ERROR\r\n':
                break
            if time.time() - start_time > timeout:
                break

    def monitor(self):
        print("SerialCom monitor thread start")
        self.send_thread.join()
        self.rec_thread.join()
        # self.serial.close()
        while True:
            cmd = "ifconfig | grep " + self.intf
            err, result = subprocess.getstatusoutput(cmd)
            if self.intf in result:
                print('Module network is available ...confg_changed is ' + str(
                    self.confg_changed))
                if self.confg_changed:
                    # config route table
                    print('simstatus :' + self.simstatus)
                    print('self.ltefirst is ' + self.ltefirst)
                    ethname = result.split(":")[0]
                    cmd = "ifconfig " + ethname + "| grep \"inet \"|awk \'{print $2}\' | cut -d \".\" -f 4 --complement"
                    print('cmd is  ' + cmd)
                    err, result = subprocess.getstatusoutput(cmd)
                    print(err)
                    print(result)
                    gateway = result + ".1"
                    print('ethname is ' + ethname)
                    print("gateway is " + gateway)
                    if self.ltefirst == 'True':
                        cmd = "route add default gw " + gateway + "dev " + ethname
                        err, result = subprocess.getstatusoutput(cmd)
                    else:
                        cmd = "route del default gw " + gateway + "dev " + ethname
                        err, result = subprocess.getstatusoutput(cmd)
                    cmd = "sudo resolvectl dns " + ethname + " 8.8.8.8"
                    err, result = subprocess.getstatusoutput(cmd)
                    self.confg_changed = False

            elif self.operator == 'NULL':
                while self.operator == 'NULL':
                    print('operator check failed, try to check again.')
                    time.sleep(5)
                    self.send_msg('AT+COPS? \r')
                    self.recv_msg()
                    parts = str(self.recv).split('"')
                    self.operator = parts[1] if len(parts) > 1 else "NULL"
                    print("operator:" + self.operator)

            else:
                self.diag()
                self.getIpAddress()

                print('Module is dialing...')

            time.sleep(20)

    def diag(self):
        if self.serial.isOpen():
            print("Open " + self.ttyusb + " success")
        else:
            print("Open " + self.ttyusb + " failed")
            return

        self.serial.flushOutput()
        print("flush all output buffer")
        self.send_msg('AT+CPIN? \r')
        self.recv_msg()
        print(self.recv)

        self.send_msg('AT+COPS? \r')
        self.recv_msg()
        print(self.recv)

        if self.recv[0].decode('utf-8') != b"ERROR\r\n":
            if "CHN-CU" in self.recv[1].decode('utf-8') or "CHN-UN" in self.recv[1].decode('utf-8'):
                self.send_msg('AT+CGDCONT=1,"IP","3gnet" \r')
                self.recv_msg()
                print(self.recv)
            elif "CHN-TE" in self.recv[1].decode('utf-8') or \
                    "CHINA Te" in self.recv[1].decode('utf-8') or \
                    "CHN-CT" in self.recv[1].decode('utf-8'):
                self.send_msg('AT+CGDCONT=1,"IP","ctnet" \r')
                self.recv_msg()
                print(self.recv)
            elif "CHN-CM" in self.recv[1].decode('utf-8') or "CHINA MO" in self.recv[1].decode('utf-8'):
                self.send_msg('AT+CGDCONT=1,"IP","cmnet" \r')
                self.recv_msg()
                print(self.recv)
            else:
                print("product error, try china mobile.")
                self.send_msg('AT+CGDCONT=1,"IP","cmnet" \r')
                self.recv_msg()
                print(self.recv)
        else:
            print("get AT+COPS? error")

        self.send_msg('AT+CESQ \r')
        self.recv_msg()
        print(self.recv)

        self.send_msg('AT+CGREG? \r')
        self.recv_msg()
        print(self.recv)

        self.send_msg('AT+GTRNDIS? \r')
        self.recv_msg()
        print(self.recv)
        if re.search(r'\+GTRNDIS:\s*0\b', str(self.recv)):
            max_retries = 3
            retry_count = 0
            success = False
            while retry_count < max_retries and not success:
                self.send_msg('AT+GTRNDIS=1,1 \r')
                self.recv_msg()
                print(self.recv)
                if 'ERROR' in self.recv:
                    print("Command failed, retrying...")
                    retry_count += 1
                    time.sleep(3)
                else:
                    success = True
            if not success:
                print("get ip from operator failed.")
                exit(1)

    def getIpAddress(self):
        cmd = "ifconfig -a| grep " + self.intf
        err, result = subprocess.getstatusoutput(cmd)
        print(result)

        ethname = result.split(":")[0]
        print(ethname)

        cmd = "dhclient " + ethname

        os.system(cmd)
        print("Get ip success!")

        self.serial.close()

    def socket_handler(self):
        print("serialCom socket_handler thread start")

        self.servce = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.servce.bind(("localhost", 9191))
        self.servce.listen(60)
        while True:
            conn, addr = self.servce.accept()
            while True:
                try:
                    data = conn.recv(1024)
                    if (len(data) > 2):
                        cmd = str(data, encoding="utf-8")
                        print('lte socket handler exec : {}'.format(cmd))
                        cmdlist = cmd.split(' ')
                        if cmdlist[0] == "get":
                            if cmdlist[1] == "ltefirst":
                                conn.send(
                                    bytes(self.ltefirst, encoding="utf8"))
                            elif cmdlist[1] == "simstatus":
                                print('simstatus :' + self.simstatus)
                                if self.simstatus != 'READY':
                                    conn.send(
                                        bytes('SIM CARD FAILED', encoding="utf8"))
                                else:
                                    conn.send(
                                        bytes('SIM CARD OK', encoding="utf8"))

                        elif cmdlist[0] == "set":
                            if cmdlist[1] == "ltefirst":
                                if cmdlist[2] != self.ltefirst:
                                    self.confg_changed = True
                                    self.conf.set(
                                        "base", "ltefirst", cmdlist[2])
                                    self.conf.write(
                                        open(self.cfgpath, "r+", encoding="utf-8"))
                                    self.ltefirst = self.conf.get(
                                        'base', 'ltefirst')
                                conn.send(
                                    bytes(self.ltefirst, encoding="utf8"))
                            else:
                                conn.send(bytes('error', encoding="utf8"))
                        else:
                            conn.send(bytes('error', encoding="utf8"))
                    else:
                        conn.close()
                        break
                except SocketError as e:
                    print('socket error is :  {}'.format(e.errno))
                    if e.errno != errno.ECONNRESET:
                        print('socket error is :  {}'.format(e.errno))
                    pass
        print("lte socket received accept")

    def start(self):
        self.serial = serial.Serial(self.ttyusb, 115200, timeout=1)
        self.status = False
        print("check usb mode.")
        self.send_msg('AT \r')
        self.recv_msg()
        print(self.recv)
        self.send_msg('AT+GTUSBMODE? \r')
        self.recv_msg()
        print(self.recv)
        usbmode = (str(self.recv).split(': ')[1]).split('\\')[0]
        if usbmode != self.mode:
            print('now usbmode: ' + usbmode)
            print('set usbmode: ' + self.mode)
            self.send_msg('AT+GTUSBMODE=' + self.mode + ' \r')
            self.recv_msg()
            print(self.recv)
            self.serial.close()
            print("restart the dialing process.")
            self.status = True
            time.sleep(5)
            return
        else:
            print("soft reboot module.")
            self.send_msg('AT+CFUN=0 \r')
            time.sleep(2)
            self.recv_msg()
            print(self.recv)
            self.send_msg('AT+CFUN=1 \r')
            time.sleep(5)
            self.recv_msg()
            print(self.recv)
            self.send_msg('ATZ \r')
            time.sleep(1)
            self.recv_msg()
            print(self.recv)

            self.send_thread = threading.Thread(target=self.send)
            self.rec_thread = threading.Thread(target=self.received)
            self.mon_thread = threading.Thread(target=self.monitor)
            self.socket_server = threading.Thread(target=self.socket_handler)

            # backup user dns file
            cmd = 'cp /etc/resolv.conf /etc/resolv.conf.user'
            err, result = subprocess.getstatusoutput(cmd)

            # read conf file
            curpath = os.path.dirname(os.path.realpath(__file__))
            self.cfgpath = os.path.join(curpath, "lteModemCfg.ini")
            print(self.cfgpath)

            self.conf = configparser.ConfigParser()
            self.conf.read(self.cfgpath, encoding="utf-8")
            self.confg_changed = True
            self.ltefirst = self.conf.get('base', 'ltefirst')
            self.simstatus = 'UINIT'

            print('lte is first selection ' + self.ltefirst)

            self.send_thread.start()
            self.socket_server.start()


class QserialCom():
    def __init__(self, ttyusb, name):
        self.ttyusb = ttyusb
        self.name = name
        self.operator = "NULL"
        self.status = True
        self.rec_state = False
        self.send_state = True

        self.intf = self.find_interface()
        print(self.intf)

    def find_interface(self):
        cmd = "ip link show"
        err, result = subprocess.getstatusoutput(cmd)
        if err:
            raise Exception("Failed to list network interfaces")

        pattern = re.compile(r"^\d+: (wwan\w+|wwx\w+|enx\w+|usb\w+|):", re.MULTILINE)
        matches = pattern.findall(result)

        if matches:
            cmd = f"ifconfig {matches[0]} 0.0.0.0"
            err, result = subprocess.getstatusoutput(cmd)
            if err:
                raise Exception("Failed to init interface")
            cmd = f"ifconfig {matches[0]} down"
            err, result = subprocess.getstatusoutput(cmd)
            if err:
                raise Exception("Failed to init interface")
            return matches[0]
        else:
            raise Exception("No suitable interface found")

    def send(self):
        print("SerialCom send thread start")
        while self.send_state:
            self.serial.write(str('AT+CPIN?\r').encode('utf-8'))
            time.sleep(1)
            self.serial.write(str('AT+CPIN?\r').encode('utf-8'))
            time.sleep(3)
            self.serial.write(str('AT+COPS?\r').encode('utf-8'))
            if self.rec_state == False:
                self.rec_state = True
                self.send_state = False
                # self.rec_thread.start()

    def received(self):
        print("serialCom received thread start")
        while self.rec_state:
            while self.serial.inWaiting() > 0:
                self.out = self.serial.read(128)
                print(self.out)
                self.simstatus = 'UINIT'
                if len(str(self.out).split(': ')) > 1:
                    self.simstatus = (str(self.out).split(': ')[
                                      1]).split('\\')[0]

                print(self.simstatus)
                if self.simstatus == 'READY' and len(str(self.out).split('"')) > 1:
                    self.operator = str(self.out).split('"')[1]
                else:
                    self.operator = 'NULL'
                print(self.operator)
                self.rec_state = False
                self.mon_thread.start()

    def send_msg(self, msg):
        self.serial.write(str(msg).encode('utf-8'))

    def recv_msg(self):
        self.recv = []
        start_time = time.time()
        timeout = 10
        while self.serial.isOpen():
            self.data = self.serial.readline()
            self.recv.append(self.data)
            if (
                self.data == b'OK\r\n'
                or self.data == b'ERROR\r\n'
                or self.data.startswith(b'+CME ERROR:')
            ):
                break
            if time.time() - start_time > timeout:
                break

    def monitor(self):
        print("SerialCom monitor thread start")
        #self.send_thread.join()
        # self.rec_thread.join()
        # self.serial.close()
        while True:
            cmd = "ifconfig | grep " + self.intf
            err, result = subprocess.getstatusoutput(cmd)
            if self.intf in result:
                print('Module network is available ...confg_changed is ' + str(
                    self.confg_changed))
                if self.confg_changed:
                    # config route table
                    print('simstatus :' + self.simstatus)
                    ethname = result.split(":")[0]
                    cmd = "ifconfig " + ethname + "| grep \"inet \"|awk \'{print $2}\' | cut -d \".\" -f 4 --complement"
                    print('cmd is ' + cmd)
                    err, result = subprocess.getstatusoutput(cmd)
                    print(err)
                    print(result)
                    gateway = result + ".1"
                    print('ethname is ' + ethname)
                    print("gateway is " + gateway)
                    if self.ltefirst == 'True':
                        cmd = "route add default gw " + gateway + "dev " + ethname
                        err, result = subprocess.getstatusoutput(cmd)
                    else:
                        cmd = "route del default gw " + gateway + "dev " + ethname
                        err, result = subprocess.getstatusoutput(cmd)
                    cmd = "sudo resolvectl dns " + ethname + " 8.8.8.8"
                    err, result = subprocess.getstatusoutput(cmd)
                    self.confg_changed = False

            elif self.operator == 'NULL':
                while self.operator == 'NULL':
                    print('operator check failed, try to check again.')
                    time.sleep(5)
                    self.send_msg('AT+COPS?\r')
                    self.recv_msg()
                    parts = str(self.recv).split('"')
                    self.operator = parts[1] if len(parts) > 1 else "NULL"
                    print("operator:" + self.operator)

            else:
                self.diag()
                self.getIpAddress()

                print('Module is dialing...')

            time.sleep(20)

    def diag(self):
        if self.serial.isOpen():
            print("Open " + self.ttyusb + " success")
        else:
            print("Open " + self.ttyusb + " failed")
            return

        self.serial.flushOutput()
        print("flush all output buffer")
        self.send_msg('AT+CPIN?\r')
        self.recv_msg()
        print(self.recv)

        self.send_msg('AT+CESQ\r')
        self.recv_msg()
        print(self.recv)

        self.send_msg('AT+COPS?\r')
        self.recv_msg()
        print(self.recv)

        self.send_msg('AT+QICSGP=1,1,""\r')
        self.recv_msg()
        print(self.recv)

        if self.name == 'RM500U' or self.name == 'ALF66':
            self.send_msg('AT+QNETDEVCTL=1,3,1\r')
            self.recv_msg()
            print(self.recv)

    def getIpAddress(self):
        cmd = "ifconfig -a| grep " + self.intf
        err, result = subprocess.getstatusoutput(cmd)
        print(result)

        ethname = result.split(":")[0]
        print(ethname)

        cmd = "dhclient " + ethname
        os.system(cmd)
        print("Get ip success!")

        self.serial.close()

    def socket_handler(self):
        print("serialCom socket_handler thread start")
        self.servce = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.servce.bind(("localhost", 9191))
        self.servce.listen(60)
        while True:
            conn, addr = self.servce.accept()
            while True:
                try:
                    data = conn.recv(1024)
                    if (len(data) > 2):
                        cmd = str(data, encoding="utf-8")
                        print('lte socket handler exec : {}'.format(cmd))
                        cmdlist = cmd.split(' ')
                        if cmdlist[0] == "get":
                            if cmdlist[1] == "ltefirst":
                                conn.send(
                                    bytes(self.ltefirst, encoding="utf8"))
                            elif cmdlist[1] == "simstatus":
                                print('simstatus :' + self.simstatus)
                                if self.simstatus != 'READY':
                                    conn.send(
                                        bytes('SIM CARD FAILED', encoding="utf8"))
                                else:
                                    conn.send(
                                        bytes('SIM CARD OK', encoding="utf8"))

                        elif cmdlist[0] == "set":
                            if cmdlist[1] == "ltefirst":
                                if cmdlist[2] != self.ltefirst:
                                    self.confg_changed = True
                                    self.conf.set(
                                        "base", "ltefirst", cmdlist[2])
                                    self.conf.write(
                                        open(self.cfgpath, "r+", encoding="utf-8"))
                                    self.ltefirst = self.conf.get(
                                        'base', 'ltefirst')
                                conn.send(
                                    bytes(self.ltefirst, encoding="utf8"))
                            else:
                                conn.send(bytes('error', encoding="utf8"))
                        else:
                            conn.send(bytes('error', encoding="utf8"))
                    else:
                        conn.close()
                        break
                except SocketError as e:
                    print('socket error is :  {}'.format(e.errno))
                    if e.errno != errno.ECONNRESET:
                        print('socket error is :  {}'.format(e.errno))
                    pass
        print("lte socket received accept")

    def start(self):
        self.serial = serial.Serial(self.ttyusb, 115200, timeout=1)
        self.status = False
        usbnet = ""
        print("check module mode.")
        self.send_msg('AT\r')
        self.recv_msg()
        print(self.recv)
        self.send_msg('AT+QCFG="usbnet"\r')
        self.recv_msg()
        print(self.recv)
        match = re.compile(r'\+QCFG:\s*[^,]*,\s*(\d+)').search(str(self.recv))
        if match:
            usbnet = match.group(1)
        if usbnet != '1':
            print('set usbmode to 1.')
            self.send_msg('AT+QCFG="usbnet",1\r')
            self.recv_msg()
            print(self.recv)
            if self.name == 'RM500U':
                usblog = ""
                self.send_msg('AT+QCFG="usbcfg"\r')
                self.recv_msg()
                print(self.recv)
                match = re.compile(r'\+QCFG:[^,]*(?:,[^,]*){4},(\d+)').search(str(self.recv))
                if match:
                    usblog = match.group(1)
                if usblog == "1":
                    self.send_msg('AT+QCFG="usbcfg",0x2c7c,0x0900,1,0,1,1,1,0,0\r')
                    self.recv_msg()
                    print(self.recv)

                self.send_msg('AT+CFUN=1,1\r')
            self.serial.close()
            print("restart the dialing process.")
            self.status = True
            time.sleep(5)
            return
        else:
            print("soft reboot module.")
            self.send_msg('AT+CFUN=0\r')
            time.sleep(2)
            self.recv_msg()
            print(self.recv)
            self.send_msg('AT+CFUN=1\r')
            time.sleep(5)
            self.recv_msg()
            print(self.recv)
            self.send_msg('ATZ\r')
            time.sleep(1)
            self.recv_msg()
            print(self.recv)

            self.mon_thread = threading.Thread(target=self.monitor)

            # backup user dns file
            cmd = 'cp /etc/resolv.conf /etc/resolv.conf.user'
            err, result = subprocess.getstatusoutput(cmd)

            # read conf file
            curpath = os.path.dirname(os.path.realpath(__file__))
            self.cfgpath = os.path.join(curpath, "lteModemCfg.ini")
            print(self.cfgpath)

            self.conf = configparser.ConfigParser()
            self.conf.read(self.cfgpath, encoding="utf-8")
            self.confg_changed = True
            self.ltefirst = self.conf.get('base', 'ltefirst')
            self.simstatus = 'UINIT'

            print('lte is first selection ' + self.ltefirst)

            self.mon_thread.start()


def check_device(device_name=None):
    cnt = 0
    find_dev = False
    dev = None

    print("check usb device...")
    if device_name:
        if device_name not in model_dict:
            print("Device not support.")
            exit(1)
        target_devices = {device_name: model_dict[device_name]}
    else:
        target_devices = model_dict

    while True:
        for k, v in target_devices.items():
            for dev_id in v:
                cmd = "lsusb | grep " + dev_id
                status, output = subprocess.getstatusoutput(cmd)

                if status == 0:
                    dev = k
                    find_dev = True
                    break
            if find_dev is True:
                break
        cnt += 1

        if find_dev or cnt >= 100:
            break

        time.sleep(3)

    if not find_dev:
        print("module can not find")
        exit(1)

    print("module find: " + dev)
    idx = list(model_dict.keys()).index(dev)

    return idx

model_dict = {"NL668": ["1508:1001"],
              "FM160": ["2cb7:0104", "2cb7:0105", "2cb7:0106", "2cb7:0107"],
              "FM650": ["2cb7:0a05", "2cb7:0a06", "2cb7:0a07"],
              "EC20": ["2c7c:0125"],
              "RM500U": ["2c7c:0900"],
              "ALF66": ["1782:4d27"]}

if __name__ == '__main__':
    idx = check_device()
    if idx == 0:
        ser_obj = GTserialCom('/dev/ttyUSB1', "NL668", "18")
    elif idx == 1:
        ser_obj = GTserialCom('/dev/ttyUSB1', "FM160", "18")
    elif idx == 2:
        ser_obj = GTserialCom('/dev/ttyUSB1', "FM650", "36")
    elif idx == 3:
        ser_obj = QserialCom('/dev/ttyUSB2', "EC20")
    elif idx == 4:
        ser_obj = QserialCom('/dev/ttyUSB2', "RM500U")
    elif idx == 5:
        ser_obj = QserialCom('/dev/ttyUSB2', "ALF66")

    while(ser_obj.status):
        check_device(ser_obj.name)
        ser_obj.start()

