import serial,threading,time
import os
import subprocess
import socket
from socket import error as SocketError
import errno
import configparser
import re


class serialCom():
    def __init__(self, ttyusb):
        self.ttyusb = ttyusb
        self.serial = serial.Serial(ttyusb, 115200, timeout=1)
        print("Open serial ", ttyusb)
        self.intf = self.find_interface()
        self.rec_state = False
        self.send_state = True

    def find_interface(self):
        cmd = "ip link show"
        err, result = subprocess.getstatusoutput(cmd)
        if err:
            raise Exception("Failed to list network interfaces")

        pattern = re.compile(r"^\d+: (wwan\w+|wwx\w+|enx\w+|usb\w+|):", re.MULTILINE)
        matches = pattern.findall(result)

        if matches:
            return matches[0]
        else:
            raise Exception("No suitable interface found")



    def send(self):
        print("serialCom send thread start")
        while self.send_state:
            time.sleep(1)
            self.serial.write(str('AT+CPIN? \r').encode('utf-8'))
            time.sleep(1)
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

    def monitor(self):
        print("serialCom monitor thread start")
        self.send_thread.join()
        self.rec_thread.join()
        self.serial.close()
        while True:
            cmd = "ifconfig | grep ppp"
            err, result = subprocess.getstatusoutput(cmd)
            if 'ppp' in result:
                print('4g network is available...self.confg_changed is ' +
                      str(self.confg_changed))
                if self.confg_changed == True:
                    # config route table
                    print('simstatus :' + self.simstatus)
                    print('self.ltefirst is ' + self.ltefirst)
                    if self.ltefirst == 'True':
                        cmd = 'route add default dev ppp0'
                        err, result = subprocess.getstatusoutput(cmd)
                    else:
                        cmd = 'route del default dev ppp0'
                        err, result = subprocess.getstatusoutput(cmd)
                    cmd = "sudo resolvectl dns " + "ppp0" + " 8.8.8.8"
                    err, result = subprocess.getstatusoutput(cmd)
                    self.confg_changed = False

            elif self.operator == 'NULL':
                print('sim card check failed')

            else:
                if "CHN-CU" in self.operator or "CHN-UN" in self.operator:
                    cmd = 'pppd call  modem_CUCC &'

                elif "CHN-TE" in self.operator or "CHINA Te" in self.operator:
                    cmd = 'pppd call  modem_CTCC &'

                elif "CHN-CM" in self.operator or "CHINA MO" in self.operator:
                    cmd = 'pppd call  modem_CMCC &'

                os.system(cmd)
                # err1,result=subprocess.getstatusoutput(cmd)

                print('4g is dialing...')

            time.sleep(20)

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


class SAserialCom(serialCom):
    def __init__(self, ttyusb, mode):
        self.ttyusb = ttyusb
        self.mode = mode
        self.serial = serial.Serial(ttyusb, 115200, timeout=1)
        print("Open serial ", ttyusb)
        self.rec_state = False
        self.send_state = True

        self.intf = self.find_interface()
        print(self.intf)

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
                print('sim card check failed')

            else:
                self.diag()
                self.getIpAddress()

                print('Module is dialing...')

            time.sleep(20)

    def send_msg(self, msg):
        self.serial.write(str(msg).encode('utf-8'))

    def recv_msg(self):
        self.recv = []
        while self.serial.isOpen():
            self.data = self.serial.readline()
            self.recv.append(self.data)
            if self.data == b'OK\r\n' or self.data == b'ERROR\r\n':
                break

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
            elif "CHN-TE" in self.recv[1].decode('utf-8') or "CHINA Te" in self.recv[1].decode('utf-8'):
                self.send_msg('AT+CGDCONT=1,"IP","ctnet" \r')
                self.recv_msg()
                print(self.recv)
            elif "CHN-CM" in self.recv[1].decode('utf-8') or "CHINA MO" in self.recv[1].decode('utf-8'):
                self.send_msg('AT+CGDCONT=1,"IP","cmnet" \r')
                self.recv_msg()
                print(self.recv)
            else:
                print("product error")
        else:
            print("get AT+COPS? error")

        self.send_msg('AT+CESQ \r')
        self.recv_msg()
        print(self.recv)

        self.send_msg('AT+CGREG? \r')
        self.recv_msg()
        print(self.recv)

        self.send_msg('AT+GTRNDIS=1,1 \r')
        self.recv_msg()
        print(self.recv)

        self.send_msg('AT+GTRNDIS? \r')
        self.recv_msg()
        print(self.recv)

    def getIpAddress(self):
        cmd = "ifconfig -a| grep " + self.intf
        err, result = subprocess.getstatusoutput(cmd)
        print(result)

        ethname = result.split(":")[0]
        print(ethname)

        if 'wwan' in self.mode:
            if os.path.isfile('/usr/sbin/fibocom-dial'):
                cmd = "fibocom-dial -f /var/log/qmi_wwan.log &"
            else:
                self.serial.write(str('AT+GTUSBMODE=18 \r').encode('utf-8'))
                return
        else:
            cmd = "dhclient " + ethname

        os.system(cmd)
        print("Get ip success!")

        self.serial.close()


def check_usb_mode(driver):
    cmd = f'usb-devices | grep {driver}'
    err, output = subprocess.getstatusoutput(cmd)
    return output.strip()

def check_product(product):
    cmd = f'lsusb | grep {product}'
    err, output = subprocess.getstatusoutput(cmd)
    return output.strip()

drivers = ['cdc_ether', 'cdc_ncm', 'rndis_host', 'wwan', 'cdc_mbim']
products = ['Fibocom', 'Quectel']

if __name__ == '__main__':
    modes = [check_usb_mode(driver) for driver in drivers if check_usb_mode(driver)]
    product = [check_product(product) for product in products if check_product(product)]

    mode_str = ''.join(modes)
    pro_str = ''.join(product)
    print(mode_str)
    print(pro_str)

    if 'Fibocom' in pro_str:
        if 'cdc_ncm' in mode_str or 'rndis_host' in mode_str:
            ser_obj = SAserialCom('/dev/ttyUSB0', mode_str)
        elif 'cdc_ether' in mode_str:
            ser_obj = SAserialCom('/dev/ttyUSB1', mode_str)
        elif 'wwan' in mode_str:
            ser_obj = serialCom('/dev/ttyUSB1')
        else:
            print("mode not support!")
            exit
    elif 'Quectel' in pro_str: # for quectel EC25
        ser_obj = serialCom('/dev/ttyUSB2')
    else: 
        print("product not support!")
        exit


    ser_obj.start()

