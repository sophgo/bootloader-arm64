#!/bin/bash
#
#FOR SE6 CTRL BOARD
#jun.hu@sophgo.com

#=================================================
I2C_RETRY_MAX=5
#================================================
#CPLD
#------------------------------------------------
CPLD0_I2C_ADDR=0x57
CPLD1_I2C_ADDR=0x56

MUX_CH0_MASK=1
MUX_CH1_MASK=2
MUX_CH2_MASK=4 #cpld1 0x56
MUX_CH3_MASK=8 #cpld0 0x57
MUX_CH0=0
MUX_CH1=1
MUX_CH2=2   #cpld1 0x56
MUX_CH3=3   #cpld0 0x57
#PCIEE RESET
CPLD_PCIEE_RST_REG=0x07
CPLD_MCU_SW_I2C_REG=0x0a
CPLD_MCU_SW_UART_REG=0x09

MCU1_PCIEE_RST=0x01
MCU2_PCIEE_RST=0x02
MCU3_PCIEE_RST=0x04
MCU4_PCIEE_RST=0x08
MCU5_PCIEE_RST=0x10
MCU6_PCIEE_RST=0x20

#core fullin
CPLD_CORE_FULLIN_REG=0x03

#core power good
CPLD_CORE_PG_REG=0x04

CORE1_BIT=0x01
CORE2_BIT=0x02
CORE3_BIT=0x04
CORE4_BIT=0x08
CORE5_BIT=0x10
CORE6_BIT=0x20

#TCA6416
#------------------------------------------------
P0_IN_REG=0x0
P1_IN_REG=0x1
P0_OUT_REG=0x2
P1_OUT_REG=0x3
P0_CFG_REG=0x6
P1_CFG_REG=0x7

##P0 output pin
TCA6416_LED0=0x01 #LED0 P00 state red led
TCA6416_LED1=0x02 #LED1 P01 power green led
TCA6416_PON1=0x04 #PON1	P02
TCA6416_PON2=0x08 #PON2	P03


##P1 output pin
TCA6416_CU0=0x02 #aiub0 reset P11
TCA6416_CU1=0x04 #aiub1 reset P12
TCA6416_LED2=0x10 #LED2 green led P14

##P0 input pin
TCA6416_PG0=0x10 #PG0  P04
TCA6416_PG1=0x20 #PG0  P05
TCA6416_FULLIN0=0x40 #PULLIN1  P06
TCA6416_FULLIN1=0x80 #PULLIN2  P07

PORT_VAL_MASK=0xFF
P0_CFG_VALUE=0xF0   #11110000
P1_CFG_VALUE=0xE9   #11101001

##P0/P1 default value
P0_DEF_VALUE=0xFE
P1_DEF_VALUE=0xFF

#power get default value
POWER_AVERAGE_CNT=0X10
FILE_NAME=adc_val.txt

# the caller name must be "bmrt_setup"
SE6_CALLER=bmrt_setup.sh
#-------------------------------------------------
SE6CTR_VERSION=4.0

PRINT_ERROR=0
PRINT_DEBUG=1
PRINT_INFO=2
SE6CRT_PRINT_LEVEL=$PRINT_INFO
# $1: log levle
# $2: print string
sectr_print()
{
    if [ $# -lt 2 ]; then
	return
    fi

    if [ $1 -gt $SE6CRT_PRINT_LEVEL ]; then
	return
    fi
    if [ $1 -eq $PRINT_ERROR ]; then
	echo "SE6_EER: $2"
    elif [ $1 -eq $PRINT_DEBUG ]; then
	echo "SE6_DBG: $2"
    elif [ $1 -eq $PRINT_INFO ]; then
	echo "SE6_INF: $2"
    fi
}

###################################################
sectr_help()
{
    echo "====================sectrl(ver:$seCTR_VERSION)========================="

    echo "sectr_detect					--detect i2c2 dev"
    echo "sectr_cpld0_dump				--dump cpld0 reg"
    echo "sectr_cpld1_dump				--dump cpld1 reg"
    echo "sectr_mcu_dump				--dump mcu reg"
    echo "sectr_6416_dump				--dump tca6416 reg"
    echo "sectr_switch_cpld	    input:0/1,	--switch i2c2 to cpld0/1"
    echo "sectr_switch_i2c	    input:1~12,	--switch i2c2 to mcu1~mcu12"
    echo "sectr_switch_uart	    input:1~12,	--switch uart to mcu1~mcu12"
    echo "sectr_set_core_ipaddr    input:ipaddr	--set ipaddr to core"
    echo "sectr_mcu_core_poweron			--power on 1684"
    echo "sectr_set_led	    input:led id,open/close	--set led0/led1/led2"
    echo "sectr_set_pon	    input:aiub id,on/off	--set pon0/pon1"
    echo "sectr_get_pg		    input:aiub id		--get pg0/pg1"
    echo "sectr_get_aiu_pg	    input:coreid    --get aiu core power good"
    echo "sectr_get_fullin	    input:aiub id   --get fullin0/fullin1"
    echo "sectr_get_aiu_fullin	    input:core id   --get aiu core fullin"
    echo "sectr_aiub_soft_reset input: cpld id,0/1	--aiub0/aiub1 soft reset"
    echo "sectr_aiub_reset	input:aiub id,0/1	--aiub0/aiub1 reset"
    echo "sectr_enable_aiub	input:aiub id,on/off	--aiub0/aiub1 on/off"
    echo "sectr_set_aiu_ipaddr	input:aiu0/aiu1 ip	--set aiub0/aiub1 ip"
    echo "sectr_set_aiu0_ipaddr	input:aiu0 ip	--set aiub0 ip"
    echo "sectr_set_aiu1_ipaddr	input:aiu1 ip	--set aiub1 ip"
    echo "sectr_set_reset		input:core id	--set aiu core reset"
    echo "sectr_adc_get_power_average  [012] --get power from ADC device"
    echo "======================================================================"

}

#return 0:no auth  1:has auth
sectr_get_auth()
{
    pid=$(ps -ef | grep $SE6_CALLER | grep -v grep | awk 'NR==1{print $2}')
    #sectr_print $PRINT_INFO "$FUNCNAME caller pid:$pid, my pid:$$"

    if [ ! -n "$pid" ];then
	echo "1"
	return
    fi

    if [ $pid -eq $$ ];then
            echo "1"
    else
            echo "0"
    fi
}

sectr_detect()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi

    i2cdetect -r -y 2
}

sectr_cpld0_dump()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    i2cdump -f -y 2 $CPLD0_I2C_ADDR
}

sectr_cpld1_dump()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    i2cdump -f -y 2 $CPLD1_I2C_ADDR
}

sectr_mcu_dump()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    i2cdump -f -y 2 0x38
}

sectr_6416_dump()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    i2cdump -f -y 2 0x20
}

#============================================================
#I2C MUX (NCA9545)
# ret: success echo value; fail echo "err"
sectr_i2c_read_mux()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    for ((rtry=0; rtry<$I2C_RETRY_MAX; rtry++))
    do
	val=$(i2cget -f -y 2 0x70)
	if [ $? -eq 0 ];then
	    break
	fi
    done
    if [ $rtry -lt $I2C_RETRY_MAX ];then
	echo $val
    else
	echo "err"
    fi
}

# $1 value
# ret: success echo 0; fail echo 1
sectr_i2c_write_mux()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    for ((rtry=0; rtry<=$I2C_RETRY_MAX; rtry++))
    do
	i2cset -f -y 2 0x70 $1
	if [ $? -eq 0 ];then
	    break
	fi
    done
    if [ $rtry -lt $I2C_RETRY_MAX ];then
	echo "0"
    else
	echo "1"
    fi
}

# $1 switch channel
# 0:ch0, 1:ch1, 2:ch2, 3:ch3
sectr_i2c_switch_mux()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    val=$(sectr_i2c_read_mux)
    if [[ $val == "err" ]];then
	sectr_print $PRINT_ERROR "$FUNCNAME error!"
	return
    fi
    sleep 0.5
    #switch to 0x56
    if [ $1 == $MUX_CH2 ]; then
	vl=$(($val & $MUX_CH2_MASK))
	if [ $vl -eq $MUX_CH2_MASK ];then
	    sectr_print $PRINT_DEBUG "$FUNCNAME in ch2"
	    return
	fi
	vl=$(($val & $MUX_CH3_MASK))
	if [ $vl -eq $MUX_CH3_MASK ];then
	    #before switch cpld need clear uart switch
	    sectr_switch_mcu_uart 0x00 $CPLD0_I2C_ADDR
	fi
    elif [ $1 == $MUX_CH3 ]; then
    #switch to 0x57
	vl=$(($val & $MUX_CH3_MASK))
	if [ $vl -eq $MUX_CH3_MASK ];then
	    sectr_print $PRINT_DEBUG "$FUNCNAME in ch3"
	    return
	fi
	vl=$(($val & $MUX_CH2_MASK))
	if [ $vl -eq $MUX_CH2_MASK ];then
	    #before switch cpld need clear uart switch
	    sectr_switch_mcu_uart 0x00 $CPLD1_I2C_ADDR
	fi
    fi

    val=$(($val & $MUX_CH0_MASK))
    case $1 in
	1 ) val=$((val | MUX_CH1_MASK));;
	2 ) val=$((val | MUX_CH2_MASK));;
	3 ) val=$((val | MUX_CH3_MASK));;
    esac
    sectr_print $PRINT_INFO "$FUNCNAME set $val"
    sectr_i2c_write_mux $val
}

# $1: swich channel
# 0: CPLD0; 1: CPLD1
# ch2: cpld1(0x56)
# ch3: cpld0(0x57)
sectr_switch_cpld()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    if [ $1 == 1 ]; then
	#switch to cpld1
	sectr_print $PRINT_INFO "$FUNCNAME CPLD1"
	sectr_i2c_switch_mux $MUX_CH2
    elif [ $1 == 0 ]; then
	#switch to cpld0
	sectr_print $PRINT_INFO "$FUNCNAME CPLD0"
	sectr_i2c_switch_mux $MUX_CH3
    fi
}

#============================================================
#GPIO EX (TCA6416)

# $1 offset
# $2 value
# ret: success echo 0; fail echo 1
sectr_i2c_write_tca6416()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    for ((rtry=0; rtry<=$I2C_RETRY_MAX; rtry++))
    do
	i2cset -f -y 2 0x20 $1 $2
	if [ $? -eq 0 ];then
	    break
	fi
    done
    if [ $rtry -lt $I2C_RETRY_MAX ];then
	echo "0"
    else
	echo "1"
    fi
}

# $1 offset
# ret: success- echo value; fail- echo "err"
sectr_i2c_read_tca6416()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    for ((rtry=0; rtry<$I2C_RETRY_MAX; rtry++))
    do
	val=$(i2cget -f -y 2 0x20 $1)
	if [ $? -eq 0 ];then
	    break
	fi
    done
    if [ $rtry -lt $I2C_RETRY_MAX ];then
	echo $val
    else
	echo "err"
    fi
}

# ret: success -echo 0; fail -echo 1
sectr_init_tca6416()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    val1=$(sectr_i2c_write_tca6416 $P0_CFG_REG $P0_CFG_VALUE)
    val2=$(sectr_i2c_write_tca6416 $P1_CFG_REG $P1_CFG_VALUE)
    val=$(($val1 | $val2))
    if [ $val -eq 1 ]; then
	return
    fi
    val1=$(sectr_i2c_write_tca6416 $P0_OUT_REG $P0_DEF_VALUE)
    val2=$(sectr_i2c_write_tca6416 $P1_OUT_REG $P1_DEF_VALUE)
    val=$(($val1 | $val2))
    echo $val
}

# $1:led id 0/1/2
# $2:open/close 1:open 0:close
sectr_set_led()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
		sectr_print $PRINT_INFO "$FUNCNAME no permission"
		return
    fi
    if [ $# -lt 2 ]; then
		sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
		return
    fi

	if [ $1 -eq 2 ]; then
		val=$(sectr_i2c_read_tca6416 $P1_OUT_REG)
	else
		val=$(sectr_i2c_read_tca6416 $P0_OUT_REG)
	fi

    if [[ $val == "err" ]];then
		sectr_print $PRINT_ERROR "$FUNCNAME error!"
		return
    fi

    if [ $2 -eq 1 ]; then
		if [ $1 -eq 0 ]; then
			val=$(($val | $TCA6416_LED0))
		elif [ $1 -eq 1 ]; then
			val=$(($val | $TCA6416_LED1))
		else
			val=$(($val | $TCA6416_LED2))
		fi
    elif [ $2 -eq 0 ]; then
		if [ $1 -eq 0 ]; then
			val=$(($val&~$TCA6416_LED0))
		elif [ $1 -eq 1 ]; then
			val=$(($val&~$TCA6416_LED1))
		else
			val=$(($val&~$TCA6416_LED2))
		fi
    else
		return
    fi
	if [ $1 -eq 2 ]; then
		sectr_print $PRINT_INFO "$FUNCNAME reg($P1_OUT_REG) $val"
		sectr_i2c_write_tca6416 $P1_OUT_REG $val
	else
		sectr_print $PRINT_INFO "$FUNCNAME reg($P0_OUT_REG) $val"
		sectr_i2c_write_tca6416 $P0_OUT_REG $val
	fi
}

# $1:pon id
# $2:open/close 1:on 0:off
sectr_set_pon()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi

    val=$(sectr_i2c_read_tca6416 $P0_OUT_REG)
    if [[ $val == "err" ]];then
	sectr_print $PRINT_ERROR "$FUNCNAME error!"
	return
    fi
    if [ $2 -eq 1 ]; then
	if [ $1 -eq 0 ]; then
	    val=$(($val | $TCA6416_PON1))
	else
	    val=$(($val | $TCA6416_PON2))
	fi
    elif [ $2 -eq 0 ]; then
	if [ $1 -eq 0 ]; then
	    val=$(($val&~$TCA6416_PON1))
	else
	    val=$(($val&~$TCA6416_PON2))
	fi
    else
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    sectr_print $PRINT_INFO "$FUNCNAME $P0_OUT_REG $val"
    sectr_i2c_write_tca6416 $P0_OUT_REG $val
}

# $1:cpld 0/1
sectr_aiub_soft_reset()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    sectr_switch_cpld $1

	if [ "$1" = "1" ];then
		sectr_i2c_write_cpld $CPLD_PCIEE_RST_REG 0x00 $CPLD1_I2C_ADDR
		sectr_i2c_write_cpld $CPLD_PCIEE_RST_REG 0x3f $CPLD1_I2C_ADDR
	else
		sectr_i2c_write_cpld $CPLD_PCIEE_RST_REG 0x00 $CPLD0_I2C_ADDR
		sectr_i2c_write_cpld $CPLD_PCIEE_RST_REG 0x3f $CPLD0_I2C_ADDR
	fi
}

# $1:aiub reset id
# $2:reset 0/1
sectr_aiub_reset()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi

    val=$(sectr_i2c_read_tca6416 $P1_OUT_REG)
    if [[ $val == "err" ]];then
	sectr_print $PRINT_ERROR "$FUNCNAME error!"
	return
    fi
    if [ $2 -eq 1 ]; then
	if [ $1 -eq 0 ]; then
	    val=$(($val | $TCA6416_CU0))
	else
	    val=$(($val | $TCA6416_CU1))
	fi
    elif [ $2 -eq 0 ]; then
	if [ $1 -eq 0 ]; then
	    val=$(($val&~$TCA6416_CU0))
	else
	    val=$(($val&~$TCA6416_CU1))
	fi
    else
	sectr_print $PRINT_ERROR "$FUNCNAME error!"
	return
    fi
	sectr_print $PRINT_INFO "$FUNCNAME reg($P1_OUT_REG) $val"
    sectr_i2c_write_tca6416 $P1_OUT_REG $val
}

# $1:pg id
# ret: value
sectr_get_pg()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    val=$(sectr_i2c_read_tca6416 $P0_IN_REG)
    if [[ $val == "err" ]];then
	sectr_print $PRINT_ERROR "$FUNCNAME error!"
	return
    fi

    if [ $1 -eq 0 ]; then
	val=$(($val & $TCA6416_PG0))
    else
	val=$(($val & $TCA6416_PG1))
    fi
    echo $val
}

# $1:fullin id
# ret: value
sectr_get_fullin()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    val=$(sectr_i2c_read_tca6416 $P0_IN_REG)
    if [[ $val == "err" ]];then
	sectr_print $PRINT_ERROR "$FUNCNAME error!"
	return
    fi

    if [ $1 -eq 0 ]; then
	val=$(($val & $TCA6416_FULLIN0))
    else
	val=$(($val & $TCA6416_FULLIN1))
    fi
    echo $val
}

#============================================================
#STM32L05- 0x38
# $1 offset
# ret: success echo value; fail echo "err"
sectr_i2c_read_mcu()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    for ((rtry=0; rtry<$I2C_RETRY_MAX; rtry++))
    do
	val=$(i2cget -f -y 2 0x38 $1)
	if [ $? -eq 0 ];then
	    break
	fi
    done
    if [ $rtry -lt $I2C_RETRY_MAX ];then
	echo $val
    else
	echo "err"
    fi
}

# $1 offset
# $2 value
# ret: success echo 0; fail echo 1
sectr_i2c_write_mcu()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    for ((rtry=0; rtry<=$I2C_RETRY_MAX; rtry++))
    do
	i2cset -f -y 2 0x38 $1 $2
	if [ $? -eq 0 ];then
	    break
	fi
	sleep 0.2
    done
    if [ $rtry -lt $I2C_RETRY_MAX ];then
	echo "0"
    else
	echo "1"
    fi
}

# ret: success echo 0; fail echo 1
sectr_mcu_core_poweron()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    sectr_print $PRINT_INFO "$FUNCNAME"

	#val=$(sectr_i2c_write_mcu 0x03 0x01)
	val=$(sectr_i2c_write_mcu 0x03 0x09)

    if [ $val -eq 0 ]; then
	echo "0"
    else
	echo "1"
    fi
}

#============================================================
#CPLD- 0x56 0x57

# $1 offset
# $2 value
# $3 cpld addr
# ret: success echo 0; fail echo 1
sectr_i2c_write_cpld()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 3 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    for ((rtry=0; rtry<=$I2C_RETRY_MAX; rtry++))
    do
	i2cset -f -y 2 $3 $1 $2
	if [ $? -eq 0 ];then
	    break
	fi
    done
    if [ $rtry -lt $I2C_RETRY_MAX ];then
	echo "0"
    else
	echo "1"
    fi
}

# $1 offset
# $2 cpld addr
# ret: success echo value; fial echo "err"
sectr_i2c_read_cpld()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    for ((rtry=0; rtry<$I2C_RETRY_MAX; rtry++))
    do
	val=$(i2cget -f -y 2 $2 $1)
	if [ $? -eq 0 ];then
	    break
	fi
    done
    if [ $rtry -lt $I2C_RETRY_MAX ];then
	echo $val
    else
	echo "err"
    fi
}

# $1: swich mcu i2c  0x1~0x6: mcu1~mcu6
# $2: cpld addr
sectr_switch_mcu_i2c()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    sectr_print $PRINT_INFO "$FUNCNAME $1"
    sectr_i2c_write_cpld $CPLD_MCU_SW_I2C_REG $1 $2
}

# $1: swich mcu uart  0x1~0x6: mcu1~mcu6
# $2: cpld addr
sectr_switch_mcu_uart()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    sectr_print $PRINT_INFO "$FUNCNAME $1"
    sectr_i2c_write_cpld $CPLD_MCU_SW_UART_REG $1 $2
}

# $1: swich mcu i2c  1~12: mcu1~mcu12
sectr_switch_i2c()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    if [ $1 -lt 7 ]; then
	sectr_switch_cpld 0
	CPLD_ADDR=$CPLD0_I2C_ADDR
	mcuid=$1
    else
	sectr_switch_cpld 1
	CPLD_ADDR=$CPLD1_I2C_ADDR
	mcuid=$(($1-6));
    fi
    sectr_print $PRINT_INFO "$FUNCNAME (0x$CPLD_ADDR)$mcuid"
    sectr_i2c_write_cpld $CPLD_MCU_SW_I2C_REG $mcuid $CPLD_ADDR
}

# $1: swich mcu uart 1~12: mcu1~mcu12
sectr_switch_uart()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    if [ $1 -lt 7 ]; then
	sectr_switch_cpld 0
	CPLD_ADDR=$CPLD0_I2C_ADDR
	mcuid=$1
    else
	sectr_switch_cpld 1
	CPLD_ADDR=$CPLD1_I2C_ADDR
	mcuid=$(($1-6));
    fi
    sectr_print $PRINT_INFO "$FUNCNAME (0x$CPLD_ADDR)$mcuid"
    sectr_i2c_write_cpld $CPLD_MCU_SW_UART_REG $mcuid $CPLD_ADDR
}

#============================================================
# $1: mcu id  0x1~0x6: mcu1~mcu6
# $2: 0/1  clean/set
# $3: cpld addr
sectr_set_pciee_rst()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 3 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi

    val=$(sectr_i2c_read_cpld $CPLD_PCIEE_RST_REG $3)
    if [[ $val == "err" ]];then
	sectr_print $PRINT_ERROR "$FUNCNAME error!"
	return
    fi
    #enable
    if [ $2 -eq 1 ];then
	case $1 in
	    1 ) val=$(($val | $MCU1_PCIEE_RST));;
	    2 ) val=$(($val | $MCU2_PCIEE_RST));;
	    3 ) val=$(($val | $MCU3_PCIEE_RST));;
	    4 ) val=$(($val | $MCU4_PCIEE_RST));;
	    5 ) val=$(($val | $MCU5_PCIEE_RST));;
	    6 ) val=$(($val | $MCU6_PCIEE_RST));;
	esac
    #disable
    elif [ $2 -eq 0 ];then
	case $1 in
	    1 ) val=$(($val & ~$MCU1_PCIEE_RST));;
	    2 ) val=$(($val & ~$MCU2_PCIEE_RST));;
	    3 ) val=$(($val & ~$MCU3_PCIEE_RST));;
	    4 ) val=$(($val & ~$MCU4_PCIEE_RST));;
	    5 ) val=$(($val & ~$MCU5_PCIEE_RST));;
	    6 ) val=$(($val & ~$MCU6_PCIEE_RST));;
	esac
    fi
    sectr_i2c_write_cpld $CPLD_PCIEE_RST_REG $val $3
}

# $1:reset 1~12: core1~core12
sectr_set_reset()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi

    if [ $1 -lt 7 ]; then
	sectr_switch_cpld 0
	CPLD_ADDR=$CPLD0_I2C_ADDR
	mcuid=$1
    else
	sectr_switch_cpld 1
	CPLD_ADDR=$CPLD1_I2C_ADDR
	mcuid=$(($1-6));
    fi
    sectr_set_pciee_rst $mcuid 0 $CPLD_ADDR
    sleep 0.5
    sectr_set_pciee_rst $mcuid 1 $CPLD_ADDR
}

# $1: mcu id  0x1~0x6: mcu1~mcu6
# $2: cpld addr
# ret: 0:present  !0:absent
sectr_get_core_fullin()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi

    val=$(sectr_i2c_read_cpld $CPLD_CORE_FULLIN_REG $2)
    if [[ $val == "err" ]];then
	sectr_print $PRINT_ERROR "$FUNCNAME error!"
	return
    fi

    case $1 in
	1 ) val=$(($val & $CORE1_BIT));;
	2 ) val=$(($val & $CORE2_BIT));;
	3 ) val=$(($val & $CORE3_BIT));;
	4 ) val=$(($val & $CORE4_BIT));;
	5 ) val=$(($val & $CORE5_BIT));;
	6 ) val=$(($val & $CORE6_BIT));;
    esac

    echo $val
}

# $1:id: 1~12: core1~core12
# ret: 0:present  !0:absent
sectr_get_aiu_fullin()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi

    if [ $1 -lt 7 ]; then
	sectr_switch_cpld 0
	CPLD_ADDR=$CPLD0_I2C_ADDR
	mcuid=$1
    else
	sectr_switch_cpld 1
	CPLD_ADDR=$CPLD1_I2C_ADDR
	mcuid=$(($1-6));
    fi
    sectr_get_core_fullin $mcuid $CPLD_ADDR
}

# $1: mcu id  0x1~0x6: mcu1~mcu6
# $2: cpld addr
# ret: !0:good  0:not good
sectr_get_core_pg()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi

    val=$(sectr_i2c_read_cpld $CPLD_CORE_PG_REG $2)
    if [[ $val == "err" ]];then
	sectr_print $PRINT_ERROR "$FUNCNAME error!"
	return
    fi

    case $1 in
	1 ) val=$(($val & $CORE1_BIT));;
	2 ) val=$(($val & $CORE2_BIT));;
	3 ) val=$(($val & $CORE3_BIT));;
	4 ) val=$(($val & $CORE4_BIT));;
	5 ) val=$(($val & $CORE5_BIT));;
	6 ) val=$(($val & $CORE6_BIT));;
    esac

    echo $val
}

# $1:id: 1~12: core1~core12
# ret: !0:good  0:not good
sectr_get_aiu_pg()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi

    if [ $1 -lt 7 ]; then
	sectr_switch_cpld 0
	CPLD_ADDR=$CPLD0_I2C_ADDR
	mcuid=$1
    else
	sectr_switch_cpld 1
	CPLD_ADDR=$CPLD1_I2C_ADDR
	mcuid=$(($1-6));
    fi
    sectr_get_core_pg $mcuid $CPLD_ADDR
}

#============================================================
# $1: aiub id 0: aiub0  1:aiub1
# $2: 0/1 - enable/disable
sectr_enable_aiub()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    #disable
    if [ $2 == 0 ]; then
	if [ $1 == 0 ]; then
	    sectr_set_pon 0 0
	else
	    sectr_set_pon 1 0
	fi
	sectr_print $PRINT_DEBUG "$FUNCNAME $1 disable"
    else
    #enable
	if [ $1 == 0 ]; then
	    sectr_set_pon 0 1
	else
	    sectr_set_pon 1 1
	fi
	sectr_print $PRINT_DEBUG "$FUNCNAME $1 enable"
    fi
    sleep 0.5
}

# $1: cpld addr
# $2: mcu id 1~6
sectr_set_core_id()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 2 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi

    if [ $1 == $CPLD0_I2C_ADDR ]; then
	sectr_print $PRINT_DEBUG "$FUNCNAME set CPLD0 $2"
	sectr_i2c_write_mcu 0x3d $2
    else
	id=$(($2+6));
	sectr_print $PRINT_DEBUG "$FUNCNAME set CPLD1 $id"
	sectr_i2c_write_mcu 0x3d $id
    fi
}

# $1: ip address
sectr_set_core_ipaddr()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    if [ $# -lt 1 ]; then
	sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	return
    fi
    sectr_print $PRINT_INFO "$FUNCNAME:$1"
    offset=0x61
    ip=1
    for ((j=1; j<=4; j++))
    do
	case $j in
	    1 ) ip=$(echo $1 | awk -F. '{print $1}');;
	    2 ) ip=$(echo $1 | awk -F. '{print $2}');;
	    3 ) ip=$(echo $1 | awk -F. '{print $3}');;
	    4 ) ip=$(echo $1 | awk -F. '{print $4}');;
	esac
	sectr_i2c_write_mcu $offset $ip
	let offset++
    done
}

# $1: IP_STR
# $2: cpld addr
sectr_set_aiub_ipaddr()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi

	product=$(cat /sys/bus/i2c/devices/1-0017/information | grep model | awk -F \" '{print $4}')
	if [ "$product" = "SM7 CTRL" ] || [ "$product" = "SE8 CTRL" ]; then
        num=10
        for ((i=1; i<=6; i++))
        do
	    	case $i in
		    	1 ) val=0x00;;
		    	2 ) val=0x01;;
	    		3 ) val=0x03;;
	    		4 ) val=0x07;;
	    		5 ) val=0x0f;;
	    		6 ) val=0x1f;;
	    esac
	    sectr_i2c_write_cpld $CPLD_PCIEE_RST_REG $val $2
	    sectr_switch_mcu_i2c $i $2
	    sleep 1
	    let num++
	    sectr_set_core_ipaddr "$1$num"
	    sectr_set_core_id $2 $i
	    sectr_mcu_core_poweron
	    sleep 0.04
        done
	    i2cset -f -y  2 $2 0x7 0x3f
	else
        num=10
        for ((i=1; i<=6; i++))
        do
        sectr_switch_mcu_i2c $i $2
        sleep 1
        let num++
        sectr_set_core_ipaddr "$1$num"
        sectr_set_core_id $2 $i
        sectr_mcu_core_poweron
        sleep 0.5
        done
	fi
}

# $1: IP_STR0
sectr_set_aiu0_ipaddr()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    IP_STR="${1}."
    #sectr_init_tca6416
    sectr_enable_aiub 0 1
    sectr_switch_cpld 0
    sectr_set_aiub_ipaddr $IP_STR $CPLD0_I2C_ADDR
}

# $1: IP_STR1
sectr_set_aiu1_ipaddr()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    IP_STR="${1}."
    #sectr_init_tca6416
    sectr_enable_aiub 1 1
    sectr_switch_cpld 1
    sectr_set_aiub_ipaddr $IP_STR $CPLD1_I2C_ADDR
}


# $1: IP_STR0
# $2: IP_STR1
sectr_set_aiu_ipaddr()
{
    auth=$(sectr_get_auth)
    if [ $auth -eq 0 ]; then
	sectr_print $PRINT_INFO "$FUNCNAME no permission"
	return
    fi
    IP_STR0="${1}."
    IP_STR1="${2}."

    sectr_init_tca6416
    sectr_enable_aiub 0 1
    sectr_switch_cpld 0
    sectr_set_aiub_ipaddr $IP_STR0 $CPLD0_I2C_ADDR
    #enable aiub 1
    sectr_enable_aiub 1 1
    sectr_switch_cpld 1
    sectr_set_aiub_ipaddr $IP_STR1 $CPLD1_I2C_ADDR
}

#get the board power from i2c ADC device.
#there are three ADC device, called 0, 1, 2
#example: sectr_power_get_from_adc 1
#V = 0.5LSB+(N-1)*LSB /100= 0.5 *  VA/256 +(N-1)*VA/256/100 = (N-0.5) * VA/25600
sectr_power_get_from_adc()
{
	nc=$(i2cdetect -y -r 2 | grep '50 51' | wc -l)
	if [ $nc -eq 1 ]; then
		power_i2c_val=$(i2cget -f -y 2 $1 0x00 w)
		power_i2c_val=$(i2cget -f -y 2 $1 0x00 w)
		power_low=$((power_i2c_val>>12))
		power_high=$((power_i2c_val & 0xf))
		power_val=$(($power_low + $power_high*16))
		val_f1=`echo $power_val - 0.5 | bc`
		val_f2=`echo $val_f1 \* 3.3 | bc`
		#the real volta value
		val_f2=`echo "scale=8; $val_f2 / 25600" | bc`
		#get the current
		val_f3=`echo $val_f2 \* 2000 | bc`
		val_f4=`echo $val_f3 \* 12 | bc`
	else
		if [ "$1" = "0x50" ];then
			pmbus -d 2 -s 0x48 -w 0x01 -v 0xe3e3
			sleep 1
			val=$(pmbus -d 2 -s 0x48 -w 0x00 | grep 'exchange-value' | awk  '{print $2}')
			rval=$(echo $((16#$val)))
			val_f4=$(echo "scale=5;$rval / 32767 * 4.096 / 0.05 * 12"|bc)

		elif [ "$1" = "0x51" ];then
			pmbus -d 2 -s 0x48 -w 0x01 -v 0xe3d3
			sleep 1
			val=$(pmbus -d 2 -s 0x48 -w 0x00 | grep 'exchange-value' | awk  '{print $2}')
			rval=$(echo $((16#$val)))
			val_f4=$(echo "scale=5;$rval / 32767 * 4.096 / 0.05 * 12 * 2"|bc)

		elif [ "$1" = "0x52" ];then
			pmbus -d 2 -s 0x48 -w 0x01 -v 0xe3c3
			sleep 1
			val=$(pmbus -d 2 -s 0x48 -w 0x00 | grep 'exchange-value' | awk  '{print $2}')
			rval=$(echo $((16#$val)))
			val_f4=$(echo "scale=5;$rval / 32767 * 4.096 / 0.05 * 12 * 2"|bc)

		fi
	fi
	echo $val_f4
}

# $1: boardid (0:ctrl 1:cpld0 2:cpld1)
sectr_adc_get_power_average()
{
	if [ $# -lt 1 ]; then
	    sectr_print $PRINT_ERROR "$FUNCNAME parm error!"
	    return
	fi
	if [ $1 -lt 3 ]; then
	    i2c_val=$1
	else
	    sectr_print $PRINT_ERROR "$FUNCNAME parm only 0,1,2"
	    return
	fi
	if [ $i2c_val == 0 ]; then
		i2c_channel=0x50
	elif [ $i2c_val == 1 ]; then
		i2c_channel=0x51
	elif [ $i2c_val == 2 ]; then
		i2c_channel=0x52
	fi
	power_curr_val=$(sectr_power_get_from_adc $i2c_channel)

	echo "$power_curr_val" |awk 'END {print}'
}
####################################################
#aiub power on
#sectr_enable_aiub 0
#sectr_enable_aiub 1

#cpld0 aiub 0
#sectr_switch_cpld 0
#sectr_set_aiub_ipaddr $IP_STR0


#cpld1 aiub 1
#sectr_switch_cpld 1
#sectr_set_aiub_ipaddr $IP_STR1
#sectr_set_aiu_ipaddr $IP_STR0 $IP_STR0
