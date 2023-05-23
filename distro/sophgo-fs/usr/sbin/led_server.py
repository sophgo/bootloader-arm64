import subprocess
import socket
from socket import error as SocketError
import threading
import errno
import time


red_led_status = 0

alarm_sleep = 'sleep'
alarm_heating = 'heating'
alarm_fan = 'fan'
alarm_temp = 'temperature'
alarm_user = 'user'
alarm_net = 'network'

fan_timer = 0
product = ''

def turn_on_green():
    if product == "SE6-CTRL" or product == "SM7 CTRL" or product == "SE6 CTRL":
        er,res = subprocess.getstatusoutput("ps -ef | grep bmrt_setup.sh | grep -v grep | awk 'NR==1{print $2}'")
        if len(res) == 0:
            er,res = subprocess.getstatusoutput("i2cget -f -y 2 0x20 0x2")
            val = int(res,16) & ~0x1
            er,res = subprocess.getstatusoutput("i2cset -f -y 2 0x20 0x2 "+ str(val))

            er,res = subprocess.getstatusoutput("i2cget -f -y 2 0x20 0x3")
            val = int(res,16) | 0x10
            er,res = subprocess.getstatusoutput("i2cset -f -y 2 0x20 0x3 " + str(val) )
    else:
        er,res = subprocess.getstatusoutput("i2cset -y 1 0x6c 0x02 0x09")
        er,res = subprocess.getstatusoutput("i2cset -y 1 0x6c 0x03 0xd")


def turn_off_green():
    if product == "SE6-CTRL" or product == "SM7 CTRL" or product == "SE6 CTRL":
        er,res = subprocess.getstatusoutput("ps -ef | grep bmrt_setup.sh | grep -v grep | awk 'NR==1{print $2}'")
        if len(res) == 0:
            # se6 will turn off all
            er,res = subprocess.getstatusoutput("i2cget -f -y 2 0x20 0x2")
            val = int(res,16) & ~0x1
            er,res = subprocess.getstatusoutput("i2cset -f -y 2 0x20 0x2 "+ str(val))

            er,res = subprocess.getstatusoutput("i2cget -f -y 2 0x20 0x3")
            val = int(res,16) & ~0x10
            er,res = subprocess.getstatusoutput("i2cset -f -y 2 0x20 0x3 " + str(val) )

    else:
        # se5 only turn off green,keep red state.
        er,res = subprocess.getstatusoutput("i2cset -y 1 0x6c 0x02 0x19")
        er,res = subprocess.getstatusoutput("i2cset -y 1 0x6c 0x03 0x05")


def turn_on_red():
    if product == "SE6-CTRL" or product == "SM7 CTRL" or product == "SE6 CTRL":
        er,res = subprocess.getstatusoutput("ps -ef | grep bmrt_setup.sh | grep -v grep | awk 'NR==1{print $2}'")
        if len(res) == 0:
            er,res = subprocess.getstatusoutput("i2cget -f -y 2 0x20 0x2")
            val = int(res,16) | 0x1
            er,res = subprocess.getstatusoutput("i2cset -f -y 2 0x20 0x2 "+ str(val))

            er,res = subprocess.getstatusoutput("i2cget -f -y 2 0x20 0x3")
            val = int(res,16) & ~0x10
            er,res = subprocess.getstatusoutput("i2cset -f -y 2 0x20 0x3 " + str(val) )

    else:
        er,res = subprocess.getstatusoutput("i2cset -y 1 0x6c 0x03 0x05")
        er,res = subprocess.getstatusoutput("i2cset -y 1 0x6c 0x02 0x19")


def turn_off_red():
    if product == "SE6-CTRL" or product == "SM7 CTRL" or product == "SE6 CTRL":
        er,res = subprocess.getstatusoutput("ps -ef | grep bmrt_setup.sh | grep -v grep | awk 'NR==1{print $2}'")
        if len(res) == 0:
            er,res = subprocess.getstatusoutput("i2cget -f -y 2 0x20 0x2")
            val = int(res,16) & ~0x1
            er,res = subprocess.getstatusoutput("i2cset -f -y 2 0x20 0x2 "+ str(val))

            er,res = subprocess.getstatusoutput("i2cget -f -y 2 0x20 0x3")
            val = int(res,16) & ~0x10

            er,res = subprocess.getstatusoutput("i2cset -f -y 2 0x20 0x3 " + str(val) )

    else:
        er,res = subprocess.getstatusoutput("i2cset -y 1 0x6c 0x03 0x05")
        er,res = subprocess.getstatusoutput("i2cset -y 1 0x6c 0x02 0x09")


# call turn off green at first
# red led twinkle
def fan_led(interval):
    global red_led_status
    global fan_timer
    #print ('fan_led: {}',red_led_status)
    if red_led_status == 1:
        turn_on_red()
        red_led_status = 2
    elif red_led_status == 2:
        turn_off_red()
        red_led_status = 1

    if red_led_status != 0 :
        fan_timer = threading.Timer(float(interval), fan_led,["0.5"])
        fan_timer.start()

def server():
    global red_led_status
    global fan_timer


    servce=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    servce.bind(("localhost",3456))
    servce.listen(6)
    print ('led server start 3456 ,debian system is ready set led to green')
    turn_on_green()
    current_action = 0
    # proir list for led
    dic_list = [alarm_sleep,alarm_heating,alarm_temp, alarm_fan, alarm_user,alarm_net]
    dic = {alarm_sleep: 'off',alarm_heating: 'off',alarm_temp: 'off', alarm_fan: 'off', alarm_user: 'off', alarm_net: 'off'}
    while True:
        conn,addr=servce.accept()
        while True:
            try:
                data=conn.recv(1024)
                if (len(data) > 4) :
                    cmd = str(data, encoding = "utf-8")
                    print('socket server exec : {}'.format(cmd))
                    cmdlist = cmd.split(' ')
                    for key in dic:
                        if cmdlist[0] == str(key):
                            dic[key]=cmdlist[1].strip('\n\r')

                    red_led_status = 0
                    green_led_status = 1
                    for key in dic_list:
                        if dic[key] == 'on':
                            # heating will close green_led,red_led will light by pic mcu
                            if key == alarm_heating or key == alarm_sleep :
                                red_led_status = 0
                                green_led_status = 0
                            else:
                                red_led_status = 1
                            break

                    if red_led_status == 1:
                        if fan_timer != 0 and fan_timer.is_alive() == True:
                            print('already led running!!')
                        else:
                            err,result=subprocess.getstatusoutput(cmd)
                            fan_timer = threading.Timer(1, fan_led,["0.5"])
                            fan_timer.start()

                        conn.send(bytes("100", encoding = "utf8"))
                    else :
                        red_led_status = 0
                        conn.send(bytes("100", encoding = "utf8"))

                        if green_led_status == 0:
                            # turn off green led
                            turn_off_green()
                        else:
                            # return to green led
                            turn_on_green()

                else:
                    conn.close()
                    break
            except SocketError as e:
                print('socket error is :  {}'.format(e.errno))
                if e.errno != errno.ECONNRESET:
                    print('socket error is :  {}'.format(e.errno))
                pass
    print("out accept")

if __name__ == '__main__':

    croninfo = []
    with open("/sys/bus/i2c/devices/1-0017/information") as f:
        lines = f.readlines()
        for line in lines:
            if "model" in line:
                croninfo = line.split('"')
                product=croninfo[3]
                print(product)
    time.sleep(15)
    server()
