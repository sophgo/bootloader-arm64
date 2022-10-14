# -*- coding: UTF-8 -*-
import serial
import serial.tools.list_ports
import os
import datetime
import time
import argparse


class GetSerialOutput:
    def __init__(self):
        self.ser_dev = None
        self.serial = None
        self.uname = 'linaro'
        self.passwd = 'linaro'
        self.ret_lst = []

    def get_ser_devs(self):
        usb_sers = list(serial.tools.list_ports.grep("/dev/ttyS2"))
        ser_dev = [x[0] for x in usb_sers]
        return ser_dev

    def init_test_serials(self):
        try:
            #os.system('sudo chmod 777 %s' % self.ser_dev)
            self.serial = serial.Serial('/dev/ttyS2', 115200, timeout=1)
            return 0
        except Exception as e:
            print("init_test_serials exception:%s" % (str(e)))
            return 1

    def check_control_version(self):
        lst = []
        readlines = self.excute_serial_cmd(self.serial, 'bm_version')
        for line in readlines:
            #print(line)
            if "BUILD TIME" in line:
                lst.append(line)
            elif "VERSION" in line:
                lst.append(line)
            elif "KernelVersion" in line:
                lst.append(line)
        return lst
   
    def enter_serial_root(self, ser_dev, timeout=120, test_log=None):
        try:
            start_time = datetime.datetime.now()
            ser_dev.write('\n'.encode('utf-8'))
            while True:
                #line=str(self.serial.read(128))
                line = str(ser_dev.readline())
                if line:
                    #print(line)
                    if " login:" in line:
                        str1 = str(self.uname) + '\n'
                        ser_dev.write(str1.encode('utf-8'))
                    elif  "Password:" in line:
                        str1 = str(self.passwd) + '\n'
                        ser_dev.write(str1.encode('utf-8'))
                    elif "linaro@"in line:
                        ser_dev.write('sudo -i\n'.encode('utf-8'))
                    elif "root@" in line:
                        return 0
                current_time = datetime.datetime.now()
                run_time = (current_time - start_time).seconds
                if run_time > timeout:
                    return 2
        except Exception as e:
            print("enter_serial_root exception:%s" % (str(e)))
            return 1

    def excute_serial_cmd(self, ser_dev, cmd, timeout=3):
        print (cmd)
        cmd = cmd + '\r'
        ser_dev.write(cmd.encode('utf-8'))
        start_time = datetime.datetime.now()
        wait_flag = 1
        read_lines = []
        while wait_flag:
            line = str(ser_dev.readline())
            cur_time = datetime.datetime.now()
            wait_time = (cur_time - start_time).seconds
            if line:
                read_lines.append(line)
            if wait_time > timeout:
                wait_flag = 0
        return read_lines

    def start_test(self,cmd):
        self.ser_dev = self.get_ser_devs()
        if self.ser_dev is None:
            print("get serial failed")
            return

        ret = self.init_test_serials()
        if ret:
            print("init serial failed")
            return
        self.ret_lst = self.enter_serial_root(self.serial,20)
        self.ret_lst = self.excute_serial_cmd(self.serial,cmd,1)
        if len(self.ret_lst) == 0:
            print("get board version failed")
            return
        for i in range(2):
            self.ret_lst.pop()
        rt_lst = []
        for item in self.ret_lst:
            item = item.split("'")[1]
            item = item.replace('\\r\\n', '')
            rt_lst.append(item)
        return rt_lst


if __name__ == '__main__':
    gso = GetSerialOutput()
    parser = argparse.ArgumentParser()
    parser.add_argument('--cmd', dest='cmd', type=str,required=True,help="input cmd")
    parser.add_argument('--id', dest='id', type=str,required=True,help="input core id")
    parser.add_argument('--format', dest='fmat', type=str,required=False,default='1',help="format print") 
    parser.add_argument('--username', dest='name', type=str,required=False,default='linaro',help="login username for cores")
    parser.add_argument('--password', dest='passwd', type=str,required=False,default='linaro',help="password for cores")
    args = parser.parse_args()

    exe_cmd = args.cmd
    coreid = args.id
    format_print = args.fmat
    gso.uname = args.name
    gso.passwd = args.passwd

    if coreid == "all":
        coreid = "1,2,3,4,5,6,7,8,9,10,11,12"

    coreid = coreid.split(',')
    print (coreid)
    
    out = {}
    for id in coreid:
        if int(id) > 6:
            cpld = "1 "
            core = (int(id) - 6)
            reg = " 0x56"
        else:
            cpld = "0 "
            core = id
            reg = " 0x57"

        os.system('./switch_uart.sh '+ cpld   + str(core) + reg)
        #os.system('/home/linaro/switch_uart.sh '+ str(cpld)  + str(core) + str()
        tem = gso.start_test(exe_cmd)
        if tem:
            out[id]=tem

    if format_print == '1':
        for key in out:
            print("[%s]" % key)
            for index in range(len(out[key])):
                print(out[key][index])
    else:
        print(out)

    print('Serial port execution command completed')

