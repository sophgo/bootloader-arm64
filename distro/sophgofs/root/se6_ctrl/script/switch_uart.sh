#!/bin/bash

source /root/se6_ctrl/se6ctr.sh 

se6ctr_switch_cpld $1

se6ctr_switch_mcu_uart $2 $3  
