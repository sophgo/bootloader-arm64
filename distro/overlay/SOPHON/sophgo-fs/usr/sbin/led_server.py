import subprocess
import socket
from socket import error as SocketError
import threading
import errno
import time
import logging
from logging.handlers import RotatingFileHandler

# Log configuration items for terminal log printing and log file writing
# The maximum size of log files is set to 1MB
logger = logging.getLogger('led_server')
logger.setLevel(logging.INFO)
file_handler = RotatingFileHandler('led_server_run.log', maxBytes=int(1e6), backupCount=1)
file_handler.setLevel(logging.INFO)
console_handler = logging.StreamHandler()
console_handler.setLevel(logging.INFO)
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
formatter_ = logging.Formatter('%(levelname)s - %(message)s')
file_handler.setFormatter(formatter)
console_handler.setFormatter(formatter_)
logger.addHandler(file_handler)
logger.addHandler(console_handler)

# The key-value in this dict correspond to the pin and function for pinmux config
pin_func_led = {'PWR_GPIO4': 'PWR_GPIO4',
                'PWR_GPIO5': 'PWR_GPIO5',
                'PWR_GPIO6': 'PWR_GPIO6'}

# Gpio number of LEDs
gpioNum_A2_STATUS_LED = 292
gpioNum_A2_ALARM_LED = 293
gpioNum_A2_SSD_ALARM_LED = 294

# Flags representing LEDs status
A2_STATUS_LED = 0
A2_ALARM_LED = 0
A2_SSD_STATUS_LED = 0
A2_SSD_ALARM_LED = 0

# Timers for generating LEDs flicker
a2_STATUS_LED_timer = 0
a2_ALARM_LED_timer = 0
a2_SSD_STATUS_LED_timer = 0
a2_SSD_ALARM_LED_timer = 0

def pinmux_config():
    file = '/sbin/cvi_pinmux'
    arg = f'[ -e {file} ]'
    err, res = subprocess.getstatusoutput(arg)
    if err != 0:
        logger.error(f'{file} not exit! Config pinmux failed!')
        return
    arg = f'[ -x {file} ]'
    err, res = subprocess.getstatusoutput(arg)
    if err != 0:
        err, res = subprocess.getstatusoutput(f'chmod +x {file}')
        logger.info(f'chmod +x {file}')

    for pin, func in pin_func_led.items():
        a = f'cvi_pinmux -w {pin}/{func}'
        err, res = subprocess.getstatusoutput(a)
        if err != 0:
            logger.error(f"Run '{a}' failed!")
            return
        else:
            logger.info(a)

    args = [f'echo {N} > /sys/class/gpio/export' for N in [
        gpioNum_A2_STATUS_LED,
        gpioNum_A2_ALARM_LED,
        gpioNum_A2_SSD_ALARM_LED
    ]]
    for a in args:
        err, res = subprocess.getstatusoutput(a)
        if err != 0:
            logger.error(f"Run '{a}' err! {res}")

    args = [f'echo out > /sys/class/gpio/gpio{N}/direction' for N in [
        gpioNum_A2_STATUS_LED,
        gpioNum_A2_ALARM_LED,
        gpioNum_A2_SSD_ALARM_LED
    ]]
    for a in args:
        err, res = subprocess.getstatusoutput(a)
        if err != 0:
            logger.error(f"Run '{a}' err! {res}")

    args = [f'echo {N} > /sys/class/gpio/unexport' for N in [
        gpioNum_A2_STATUS_LED,
        gpioNum_A2_ALARM_LED,
        gpioNum_A2_SSD_ALARM_LED
    ]]
    for a in args:
        err, res = subprocess.getstatusoutput(a)
        if err != 0:
            logger.error(f"Run '{a}' err! {res}")

def set_A2_STATUS_LED(status):
    global A2_STATUS_LED
    if status in ['on', 'ON']:
        cmds = [f'echo {gpioNum_A2_STATUS_LED} > /sys/class/gpio/export',
                f'echo 1 > /sys/class/gpio/gpio{gpioNum_A2_STATUS_LED}/value',
                f'echo {gpioNum_A2_STATUS_LED} > /sys/class/gpio/unexport']
        A2_STATUS_LED = 1
    elif status in ['off', 'OFF']:
        cmds = [f'echo {gpioNum_A2_STATUS_LED} > /sys/class/gpio/export',
                f'echo 0 > /sys/class/gpio/gpio{gpioNum_A2_STATUS_LED}/value',
                f'echo {gpioNum_A2_STATUS_LED} > /sys/class/gpio/unexport']
        A2_STATUS_LED = 0
    else:
        return
    for cmd in cmds:
        err, res = subprocess.getstatusoutput(cmd)
        if err != 0:
            logger.error(f"Run '{cmd}' err! {res}")


def set_A2_ALARM_LED(status):
    global A2_ALARM_LED
    if status in ['on', 'ON']:
        cmds = [f'echo {gpioNum_A2_ALARM_LED} > /sys/class/gpio/export',
                f'echo 1 > /sys/class/gpio/gpio{gpioNum_A2_ALARM_LED}/value',
                f'echo {gpioNum_A2_ALARM_LED} > /sys/class/gpio/unexport']
        A2_ALARM_LED = 1
    elif status in ['off', 'OFF']:
        cmds = [f'echo {gpioNum_A2_ALARM_LED} > /sys/class/gpio/export',
                f'echo 0 > /sys/class/gpio/gpio{gpioNum_A2_ALARM_LED}/value',
                f'echo {gpioNum_A2_ALARM_LED} > /sys/class/gpio/unexport']
        A2_ALARM_LED = 0
    else:
        return
    for cmd in cmds:
        err, res = subprocess.getstatusoutput(cmd)
        if err != 0:
            logger.error(f"Run '{cmd}' err! {res}")


def set_A2_SSD_STATUS_LED(status):
    global A2_SSD_STATUS_LED
    if status in ['on', 'ON']:
        # Notice than after executing this command, the LED light will not flash during SSD reading and writing
        # cmd = 'sudo sh -c "echo 0 > /sys/class/leds/sata\:green\:disk/brightness"'
        A2_SSD_STATUS_LED = 1
        return
    elif status in ['off', 'OFF']:
        cmd = 'echo 255 > /sys/class/leds/sata\:green\:disk/brightness'
        A2_SSD_STATUS_LED = 0
    else:
        return
    err, res = subprocess.getstatusoutput(cmd)
    if err != 0:
        logger.error(f"Run '{cmd}' err! {res}")

def set_A2_SSD_ALARM_LED(status):
    global A2_SSD_ALARM_LED
    if status in ['on', 'ON']:
        cmds = [f'echo {gpioNum_A2_SSD_ALARM_LED} > /sys/class/gpio/export',
                f'echo 1 > /sys/class/gpio/gpio{gpioNum_A2_SSD_ALARM_LED}/value',
                f'echo {gpioNum_A2_SSD_ALARM_LED} > /sys/class/gpio/unexport']
        A2_SSD_ALARM_LED = 1
    elif status in ['off', 'OFF']:
        cmds = [f'echo {gpioNum_A2_SSD_ALARM_LED} > /sys/class/gpio/export',
                f'echo 0 > /sys/class/gpio/gpio{gpioNum_A2_SSD_ALARM_LED}/value',
                f'echo {gpioNum_A2_SSD_ALARM_LED} > /sys/class/gpio/unexport']
        A2_SSD_ALARM_LED = 0
    else:
        return
    for cmd in cmds:
        err, res = subprocess.getstatusoutput(cmd)
        if err != 0:
            logger.error(f"Run '{cmd}' err! {res}")


def a2_STATUS_LED_flicker(interval):
    global A2_STATUS_LED
    global a2_STATUS_LED_timer
    status = ['off', 'on'][not A2_STATUS_LED]
    set_A2_STATUS_LED(status)

    a2_STATUS_LED_timer = threading.Timer(interval, a2_STATUS_LED_flicker, [interval])
    a2_STATUS_LED_timer.start()


def a2_ALARM_LED_flicker(interval):
    global A2_ALARM_LED
    global a2_ALARM_LED_timer
    status = ['off', 'on'][not A2_ALARM_LED]
    set_A2_ALARM_LED(status)

    a2_ALARM_LED_timer = threading.Timer(interval, a2_ALARM_LED_flicker, [interval])
    a2_ALARM_LED_timer.start()


def a2_SSD_STATUS_LED_flicker(interval):
    global A2_SSD_STATUS_LEDsys
    global a2_SSD_STATUS_LED_timer
    status = ['off', 'on'][not A2_SSD_STATUS_LED]
    set_A2_SSD_STATUS_LED(status)

    a2_SSD_STATUS_LED_timer = threading.Timer(interval, a2_SSD_STATUS_LED_flicker, [interval])
    a2_SSD_STATUS_LED_timer.start()


def a2_SSD_ALARM_LED_flicker(interval):
    global A2_SSD_ALARM_LED
    global a2_SSD_ALARM_LED_timer
    status = ['off', 'on'][not A2_SSD_ALARM_LED]
    set_A2_SSD_ALARM_LED(status)

    a2_SSD_ALARM_LED_timer = threading.Timer(interval, a2_SSD_ALARM_LED_flicker, [interval])
    a2_SSD_ALARM_LED_timer.start()

def leds_flicker(name, intvl):
    global a2_STATUS_LED_timer
    global a2_ALARM_LED_timer
    global a2_SSD_STATUS_LED_timer
    global a2_SSD_ALARM_LED_timer
    fun_dic = {'A2_STATUS_LED': a2_STATUS_LED_flicker,
               'A2_ALARM_LED': a2_ALARM_LED_flicker,
               'A2_SSD_STATUS_LED': a2_SSD_STATUS_LED_flicker,
               'A2_SSD_ALARM_LED': a2_SSD_ALARM_LED_flicker}

    led_timer_dic = {'A2_STATUS_LED': a2_STATUS_LED_timer,
                     'A2_ALARM_LED': a2_ALARM_LED_timer,
                     'A2_SSD_STATUS_LED': a2_SSD_STATUS_LED_timer,
                     'A2_SSD_ALARM_LED': a2_SSD_ALARM_LED_timer}

    set_led_dic = {'A2_STATUS_LED': set_A2_STATUS_LED,
                   'A2_ALARM_LED': set_A2_ALARM_LED,
                   'A2_SSD_STATUS_LED': set_A2_SSD_STATUS_LED,
                   'A2_SSD_ALARM_LED': set_A2_SSD_ALARM_LED}
    try:
        led_timer_dic[name].cancel()
    except:
        pass
    set_led_dic[name]('off')
    if intvl > 0:
        fun_dic[name](intvl)


def server():
    global a2_STATUS_LED_timer
    global a2_ALARM_LED_timer
    global a2_SSD_STATUS_LED_timer
    global a2_SSD_ALARM_LED_timer
    a2_STATUS_LED_timer = threading.Timer(1, a2_STATUS_LED_flicker, [1])
    a2_ALARM_LED_timer = threading.Timer(1, a2_ALARM_LED_flicker, [1])
    a2_SSD_STATUS_LED_timer = threading.Timer(1, a2_SSD_STATUS_LED_flicker, [1])
    a2_SSD_ALARM_LED_timer = threading.Timer(1, a2_SSD_ALARM_LED_flicker, [1])

    service = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    service.bind(("localhost", 3456))
    service.listen(6)
    logger.info('Led server start at 3456, system is ready, Set status led to green.')
    pinmux_config()
    set_A2_STATUS_LED('on')
    set_A2_ALARM_LED('off')

    while True:
        conn, addr = service.accept()
        while True:
            try:
                data = conn.recv(1024)
                is_cmd_exc = False
                if len(data) > 4:
                    cmd = str(data, encoding="utf-8").strip()
                    logger.info(f'server received: {cmd}')
                    if cmd == 'A2_STATUS_LED on':
                        set_A2_STATUS_LED('on')
                        is_cmd_exc = True
                    elif cmd == 'A2_STATUS_LED off':
                        set_A2_STATUS_LED('off')
                        is_cmd_exc = True

                    elif cmd == 'A2_ALARM_LED on':
                        set_A2_ALARM_LED('on')
                        is_cmd_exc = True
                    elif cmd == 'A2_ALARM_LED off':
                        set_A2_ALARM_LED('off')
                        is_cmd_exc = True

                    elif cmd == 'A2_SSD_STATUS_LED on':
                        set_A2_SSD_STATUS_LED('on')
                        is_cmd_exc = True
                    elif cmd == 'A2_SSD_STATUS_LED off':
                        set_A2_SSD_STATUS_LED('off')
                        is_cmd_exc = True

                    elif cmd == 'A2_SSD_ALARM_LED on':
                        set_A2_SSD_ALARM_LED('on')
                        is_cmd_exc = True
                    elif cmd == 'A2_SSD_ALARM_LED off':
                        set_A2_SSD_ALARM_LED('off')
                        is_cmd_exc = True

                    elif 'flicker' in cmd:
                        name, _, interval = cmd.split(' ')
                        try:
                            interval = float(interval)
                        except:
                            interval = 0
                        leds_flicker(name, interval)
                        is_cmd_exc = True

                    elif cmd == 'temperature on':
                        set_A2_STATUS_LED('off')
                        leds_flicker('A2_ALARM_LED', 1)
                        is_cmd_exc = True

                    elif cmd == 'temperature off':
                        set_A2_STATUS_LED('on')
                        leds_flicker('A2_ALARM_LED', 0)
                        set_A2_ALARM_LED('off')
                        is_cmd_exc = True

                    elif cmd == 'ssd normal state':
                        set_A2_SSD_STATUS_LED('on')
                        leds_flicker('A2_SSD_ALARM_LED', 0)
                        set_A2_SSD_ALARM_LED('off')
                        is_cmd_exc = True

                    elif cmd == 'ssd mount failed':
                        set_A2_SSD_STATUS_LED('off')
                        if not a2_SSD_ALARM_LED_timer.is_alive():
                            leds_flicker('A2_SSD_ALARM_LED', 1)
                        is_cmd_exc = True

                    elif cmd == 'ssd not present':
                        set_A2_SSD_STATUS_LED('off')
                        set_A2_SSD_ALARM_LED('off')
                        leds_flicker('A2_SSD_ALARM_LED', 0)
                        is_cmd_exc = True

                    conn.send(bytes(f"{cmd}\r\n", encoding="utf8"))
                    if is_cmd_exc:
                        logger.info(f'server exec: {cmd}')
                        is_cmd_exc = False
                else:
                    conn.close()
                    break

            except SocketError as e:
                logger.critical('socket error is :  {}'.format(e.errno))
                if e.errno != errno.ECONNRESET:
                    logger.critical('socket error is :  {}'.format(e.errno))
    logger.critical("out accept")


if __name__ == '__main__':
    time.sleep(5)
    server()
