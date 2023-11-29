#!/bin/bash

source /root/se_ctrl/sectr.sh

sectr_switch_cpld $1

sectr_switch_mcu_uart $2 $3
