EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Driver_Motor:L293D H-Bridge1
U 1 1 614DE23E
P 6250 3250
F 0 "H-Bridge1" H 6250 4431 50  0000 C CNN
F 1 "L293D" H 6250 4340 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_LongPads" H 6500 2500 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/l293.pdf" H 5950 3950 50  0001 C CNN
	1    6250 3250
	1    0    0    -1  
$EndComp
Text GLabel 5750 3050 0    50   Input ~ 0
F_ENABLE
Text GLabel 5750 2650 0    50   Input ~ 0
F_IN_1
Text GLabel 5750 2850 0    50   Input ~ 0
F_IN_2
Text GLabel 6050 4050 3    50   Input ~ 0
GND
Text GLabel 6150 4050 3    50   Input ~ 0
GND
Text GLabel 6350 4050 3    50   Input ~ 0
GND
Text GLabel 6450 4050 3    50   Input ~ 0
GND
Text GLabel 5950 2150 1    50   Input ~ 0
VCC
Wire Wire Line
	5950 2150 5950 2200
Wire Wire Line
	5950 2200 6150 2200
Wire Wire Line
	6150 2200 6150 2250
$Comp
L Device:R_Small R1
U 1 1 614E94E6
P 4250 3350
F 0 "R1" V 4054 3350 50  0000 C CNN
F 1 "1M" V 4145 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4250 3350 50  0001 C CNN
F 3 "~" H 4250 3350 50  0001 C CNN
F 4 "C22935" H 4250 3350 50  0001 C CNN "LCSC Part Number"
F 5 "C22935" H 4250 3350 50  0001 C CNN "LCSC"
	1    4250 3350
	0    1    1    0   
$EndComp
Text GLabel 3900 3350 0    50   Input ~ 0
F_TOUCH_1
Wire Wire Line
	3900 3350 4150 3350
Text GLabel 4600 3350 2    50   Input ~ 0
F_TOUCH_2
Wire Wire Line
	4350 3350 4600 3350
Text GLabel 6750 2650 2    50   Input ~ 0
F_OUT_1
Text GLabel 6750 2850 2    50   Input ~ 0
F_OUT_2
Text GLabel 6500 1900 2    50   Input ~ 0
9V
Wire Wire Line
	6500 1900 6350 1900
Wire Wire Line
	6350 1900 6350 2250
NoConn ~ 5750 3250
NoConn ~ 5750 3450
NoConn ~ 5750 3650
NoConn ~ 6750 3450
NoConn ~ 6750 3250
$EndSCHEMATC
