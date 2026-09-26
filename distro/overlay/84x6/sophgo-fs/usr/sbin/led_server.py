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
file_handler = RotatingFileHandler('/var/log/led_server_run.log', maxBytes=int(1e6), backupCount=1)
file_handler.setLevel(logging.INFO)
console_handler = logging.StreamHandler()
console_handler.setLevel(logging.INFO)
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
formatter_ = logging.Formatter('%(levelname)s - %(message)s')
file_handler.setFormatter(formatter)
console_handler.setFormatter(formatter_)
logger.addHandler(file_handler)
logger.addHandler(console_handler)

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

# Alarm LED arbitration: over-temp steady (wins) > software fault 1Hz > off
temp_active = 0
softfault_active = 0
alarm_mode = 0  # 0=off, 1=steady on, 2=1Hz flicker
_led_err_logged = set()

# The four LEDs controlled in this file correspond to the nodes in the DTS
# with labels of status, error, sata\:green\:disk, and ssd_alarm.
def set_A2_STATUS_LED(status):
    global A2_STATUS_LED
    if status in ['on', 'ON']:
        cmds = ['echo 1 > /sys/class/leds/status/brightness']
        A2_STATUS_LED = 1
    elif status in ['off', 'OFF']:
        cmds = ['echo 0 > /sys/class/leds/status/brightness']
        A2_STATUS_LED = 0
    else:
        return
    for cmd in cmds:
        err, res = subprocess.getstatusoutput(cmd)
        if err != 0 and cmd not in _led_err_logged:
            _led_err_logged.add(cmd)
            logger.error(f"Run '{cmd}' err! {res}")


def set_A2_ALARM_LED(status):
    global A2_ALARM_LED
    if status in ['on', 'ON']:
        cmds = ['echo 1 > /sys/class/leds/error/brightness']
        A2_ALARM_LED = 1
    elif status in ['off', 'OFF']:
        cmds = ['echo 0 > /sys/class/leds/error/brightness']
        A2_ALARM_LED = 0
    else:
        return
    for cmd in cmds:
        err, res = subprocess.getstatusoutput(cmd)
        if err != 0 and cmd not in _led_err_logged:
            _led_err_logged.add(cmd)
            logger.error(f"Run '{cmd}' err! {res}")


def set_A2_SSD_STATUS_LED(status):
    global A2_SSD_STATUS_LED
    if status in ['on', 'ON']:
        # SE13 binds disk-activity-2hz (2Hz flicker on I/O)
        cmds = ['echo 0 > /sys/class/leds/sata\:green\:disk/brightness',
               'echo disk-activity-2hz > /sys/class/leds/sata\:green\:disk/trigger']
        A2_SSD_STATUS_LED = 1
    elif status in ['off', 'OFF']:
        cmds = ['echo 1 > /sys/class/leds/sata\:green\:disk/brightness']
        A2_SSD_STATUS_LED = 0
    else:
        return
    for cmd in cmds:
        err, res = subprocess.getstatusoutput(cmd)
        if err != 0 and cmd not in _led_err_logged:
            _led_err_logged.add(cmd)
            logger.error(f"Run '{cmd}' err! {res}")

def set_A2_SSD_ALARM_LED(status):
    global A2_SSD_ALARM_LED
    if status in ['on', 'ON']:
        cmds = ['echo 1 > /sys/class/leds/ssd_alarm/brightness']
        A2_SSD_ALARM_LED = 1
    elif status in ['off', 'OFF']:
        cmds = ['echo 0 > /sys/class/leds/ssd_alarm/brightness']
        A2_SSD_ALARM_LED = 0
    else:
        return
    for cmd in cmds:
        err, res = subprocess.getstatusoutput(cmd)
        if err != 0 and cmd not in _led_err_logged:
            _led_err_logged.add(cmd)
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


def update_alarm_led():
    # Alarm arbitration: over-temp steady (mode1, wins) > software fault 1Hz
    # (mode2) > off (mode0)
    global alarm_mode
    if temp_active:
        new_mode = 1
    elif softfault_active:
        new_mode = 2
    else:
        new_mode = 0
    if new_mode == alarm_mode:
        return
    alarm_mode = new_mode
    if new_mode == 1:           # over-temp: steady red
        leds_flicker('A2_ALARM_LED', 0)
        set_A2_ALARM_LED('on')
    elif new_mode == 2:         # software fault: 1Hz flicker
        leds_flicker('A2_ALARM_LED', 0.5)
    else:                       # off
        leds_flicker('A2_ALARM_LED', 0)
        set_A2_ALARM_LED('off')


def server():
    global a2_STATUS_LED_timer
    global a2_ALARM_LED_timer
    global a2_SSD_STATUS_LED_timer
    global a2_SSD_ALARM_LED_timer
    global temp_active
    global softfault_active
    a2_STATUS_LED_timer = threading.Timer(1, a2_STATUS_LED_flicker, [1])
    a2_ALARM_LED_timer = threading.Timer(1, a2_ALARM_LED_flicker, [1])
    a2_SSD_STATUS_LED_timer = threading.Timer(1, a2_SSD_STATUS_LED_flicker, [1])
    a2_SSD_ALARM_LED_timer = threading.Timer(1, a2_SSD_ALARM_LED_flicker, [1])

    service = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    service.bind(("localhost", 3456))
    service.listen(6)
    logger.info('Led server start at 3456, set status led to 1Hz green.')
    # SE13: SYS normal = green 1Hz flicker
    leds_flicker('A2_STATUS_LED', 0.5)
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
                        temp_active = 1
                        set_A2_STATUS_LED('off')
                        update_alarm_led()
                        is_cmd_exc = True

                    elif cmd == 'temperature off':
                        # restore SYS 1Hz; Alarm re-arbitrated
                        # (softfault may stay active)
                        temp_active = 0
                        leds_flicker('A2_STATUS_LED', 0.5)
                        update_alarm_led()
                        is_cmd_exc = True

                    # SE13: software anomaly = Alarm red 1Hz
                    elif cmd == 'software_fault on':
                        softfault_active = 1
                        update_alarm_led()
                        is_cmd_exc = True
                    elif cmd == 'software_fault off':
                        softfault_active = 0
                        update_alarm_led()
                        is_cmd_exc = True

                    elif cmd == 'ssd normal state':
                        set_A2_SSD_STATUS_LED('on')
                        leds_flicker('A2_SSD_ALARM_LED', 0)
                        set_A2_SSD_ALARM_LED('off')
                        is_cmd_exc = True

                    elif cmd == 'ssd mount failed':
                        set_A2_SSD_STATUS_LED('off')
                        # SE13: ssd_alarm steady red
                        leds_flicker('A2_SSD_ALARM_LED', 0)
                        set_A2_SSD_ALARM_LED('on')
                        is_cmd_exc = True

                    elif cmd == 'ssd not present':
                        # SE13: absent = yellow
                        set_A2_SSD_STATUS_LED('on')
                        leds_flicker('A2_SSD_ALARM_LED', 0)
                        set_A2_SSD_ALARM_LED('on')
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
