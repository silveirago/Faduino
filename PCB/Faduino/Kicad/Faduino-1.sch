EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 6
Title "Faduino"
Date "2021-09-14"
Rev "1"
Comp "Nerd Musician"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L promicro:Arduino_Pro_Micro U1
U 1 1 61426EDF
P 5700 4900
F 0 "U1" H 5700 5937 60  0000 C CNN
F 1 "Arduino_Pro_Micro" H 5700 5831 60  0000 C CNN
F 2 "Arduino_Shield_Modules_for_KiCad:ArduinoProMicro" H 5800 3850 60  0001 C CNN
F 3 "" H 5800 3850 60  0000 C CNN
	1    5700 4900
	1    0    0    -1  
$EndComp
$Sheet
S 1500 1200 2100 1450
U 6142C6EC
F0 "Buttons" 50
F1 "Buttons.sch" 50
$EndSheet
$Sheet
S 4250 1200 1800 1400
U 6142C989
F0 "Leds" 50
F1 "Leds.sch" 50
$EndSheet
$Sheet
S 6950 1200 1900 1350
U 6142C9D7
F0 "Motorized_Fader" 50
F1 "Motorized_Fader.sch" 50
$EndSheet
Text GLabel 5000 4750 0    50   Input ~ 0
S0
Text GLabel 5000 4850 0    50   Input ~ 0
S1
Text GLabel 5000 4350 0    50   Input ~ 0
GND
Text GLabel 6400 4950 2    50   Input ~ 0
S2
Text GLabel 6400 5050 2    50   Input ~ 0
S3
Text GLabel 6400 4750 2    50   Input ~ 0
SIG_1
Text GLabel 6400 4650 2    50   Input ~ 0
SIG_2
Text GLabel 6400 4450 2    50   Input ~ 0
VCC
Text GLabel 5000 4450 0    50   Input ~ 0
GND
Text GLabel 6400 4250 2    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x04_Female Fader_conn1
U 1 1 614EE1CF
P 3400 4400
F 0 "Fader_conn1" H 3428 4376 50  0000 L CNN
F 1 "Conn_01x04" H 3428 4285 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 3400 4400 50  0001 C CNN
F 3 "~" H 3400 4400 50  0001 C CNN
	1    3400 4400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female dc_motor_conn1
U 1 1 614EF413
P 3400 5050
F 0 "dc_motor_conn1" H 3428 5026 50  0000 L CNN
F 1 "Conn_01x02" H 3428 4935 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3400 5050 50  0001 C CNN
F 3 "~" H 3400 5050 50  0001 C CNN
	1    3400 5050
	1    0    0    -1  
$EndComp
Text GLabel 3200 4300 0    50   Input ~ 0
GND
Text GLabel 3200 4500 0    50   Input ~ 0
VCC
Text GLabel 3200 4400 0    50   Input ~ 0
F_TOUCH_1
Text GLabel 3200 4600 0    50   Input ~ 0
F_WIPER
Text GLabel 3200 5050 0    50   Input ~ 0
F_OUT_1
Text GLabel 3200 5150 0    50   Input ~ 0
F_OUT_2
Text GLabel 6400 5250 2    50   Input ~ 0
F_TOUCH_1
Text GLabel 6400 4850 2    50   Input ~ 0
F_WIPER
Text GLabel 6400 5150 2    50   Input ~ 0
F_TOUCH_2
Text GLabel 5000 5250 0    50   Input ~ 0
F_ENABLE
Text GLabel 5000 5050 0    50   Input ~ 0
F_IN_1
Text GLabel 5000 5150 0    50   Input ~ 0
F_IN_2
$Sheet
S 9250 1250 1250 1300
U 614F3959
F0 "Encoder" 50
F1 "Encoder.sch" 50
$EndSheet
Text GLabel 5000 4550 0    50   Input ~ 0
ENC_A
Text GLabel 5000 4650 0    50   Input ~ 0
ENC_B
Text GLabel 5000 4950 0    50   Input ~ 0
addressable_led
$Sheet
S 8200 3100 1200 1100
U 615C89CA
F0 "voltage_regulator" 50
F1 "voltage_regulator.sch" 50
$EndSheet
NoConn ~ 6400 4150
$Comp
L power:PWR_FLAG #FLG01
U 1 1 614791AF
P 7850 5250
F 0 "#FLG01" H 7850 5325 50  0001 C CNN
F 1 "PWR_FLAG" H 7850 5423 50  0000 C CNN
F 2 "" H 7850 5250 50  0001 C CNN
F 3 "~" H 7850 5250 50  0001 C CNN
	1    7850 5250
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 6147933D
P 8300 5250
F 0 "#FLG02" H 8300 5325 50  0001 C CNN
F 1 "PWR_FLAG" H 8300 5423 50  0000 C CNN
F 2 "" H 8300 5250 50  0001 C CNN
F 3 "~" H 8300 5250 50  0001 C CNN
	1    8300 5250
	1    0    0    -1  
$EndComp
Text GLabel 7850 5350 3    50   Input ~ 0
GND
Wire Wire Line
	7850 5350 7850 5250
Text GLabel 8300 5400 3    50   Input ~ 0
9V
Wire Wire Line
	8300 5400 8300 5250
$Comp
L Connector:Conn_01x06_Female Extra_pins1
U 1 1 614572A0
P 1950 4700
F 0 "Extra_pins1" H 1978 4676 50  0000 L CNN
F 1 "Conn_01x06" H 1978 4585 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 1950 4700 50  0001 C CNN
F 3 "~" H 1950 4700 50  0001 C CNN
	1    1950 4700
	1    0    0    -1  
$EndComp
Text Label 5000 4150 2    50   ~ 0
TX
Text Label 5000 4250 2    50   ~ 0
RX
Text Label 6400 4350 0    50   ~ 0
RST
Text Label 6400 4550 0    50   ~ 0
A3
Text GLabel 1750 4500 0    50   Input ~ 0
GND
Text GLabel 1750 4600 0    50   Input ~ 0
VCC
Text Label 1750 4700 2    50   ~ 0
TX
Text Label 1750 4800 2    50   ~ 0
RX
Text Label 1750 4900 2    50   ~ 0
A3
Text Label 1750 5000 2    50   ~ 0
RST
$EndSCHEMATC
