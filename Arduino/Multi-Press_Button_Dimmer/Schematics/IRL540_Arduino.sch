EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:switches
LIBS:IRL540_Arduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L IRLB8721PBF Q1
U 1 1 5A4B840E
P 8300 3800
F 0 "Q1" H 8550 3875 50  0000 L CNN
F 1 "IRL540" H 8550 3800 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220_Horizontal" H 8550 3725 50  0001 L CIN
F 3 "https://www.vishay.com/docs/91300/91300.pdf" H 8300 3800 50  0001 L CNN
	1    8300 3800
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR3
U 1 1 5A4B8516
P 8400 2600
F 0 "#PWR3" H 8400 2450 50  0001 C CNN
F 1 "+12V" H 8400 2740 50  0000 C CNN
F 2 "" H 8400 2600 50  0001 C CNN
F 3 "" H 8400 2600 50  0001 C CNN
	1    8400 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 5A4B852C
P 8400 4400
F 0 "#PWR4" H 8400 4150 50  0001 C CNN
F 1 "GND" H 8400 4250 50  0000 C CNN
F 2 "" H 8400 4400 50  0001 C CNN
F 3 "" H 8400 4400 50  0001 C CNN
	1    8400 4400
	1    0    0    -1  
$EndComp
$Comp
L LED_Series D1
U 1 1 5A4B8582
P 8400 3150
F 0 "D1" H 8400 3375 50  0000 C CNN
F 1 "LED_Series" H 8400 3300 50  0000 C CNN
F 2 "" H 8300 3150 50  0000 C CNN
F 3 "" H 8300 3150 50  0000 C CNN
	1    8400 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8400 3400 8400 3600
Wire Wire Line
	8400 4400 8400 4000
Wire Wire Line
	8400 2600 8400 2900
$Comp
L R R2
U 1 1 5A4B8781
P 7900 4150
F 0 "R2" V 7980 4150 50  0000 C CNN
F 1 "100kΩ" V 7900 4150 50  0000 C CNN
F 2 "" V 7830 4150 50  0001 C CNN
F 3 "" H 7900 4150 50  0001 C CNN
	1    7900 4150
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5A4B87B4
P 7550 3850
F 0 "R1" V 7630 3850 50  0000 C CNN
F 1 "100Ω" V 7550 3850 50  0000 C CNN
F 2 "" V 7480 3850 50  0001 C CNN
F 3 "" H 7550 3850 50  0001 C CNN
	1    7550 3850
	0    1    1    0   
$EndComp
$Comp
L NCP1117-5.0_SOT223 U2
U 1 1 5A4B88BA
P 7400 2700
F 0 "U2" H 7550 2504 50  0000 C CNN
F 1 "TSR 0.5-2450" H 7400 2900 50  0000 C CNN
F 2 "" H 7400 2700 50  0001 C CNN
F 3 "https://www.tracopower.com/products/tsr05.pdf" H 7400 2700 50  0001 C CNN
	1    7400 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	7900 4400 7900 4300
Connection ~ 7900 4400
Wire Wire Line
	7700 2700 8400 2700
Connection ~ 8400 2700
Wire Wire Line
	8100 3850 7700 3850
Wire Wire Line
	7900 4000 7900 3850
Connection ~ 7900 3850
Wire Wire Line
	7000 4400 8400 4400
$Comp
L ATmega32U4 U1
U 1 1 5A4B8D1F
P 4900 3950
F 0 "U1" H 4000 5650 50  0000 C CNN
F 1 "ATmega32U4" H 4250 2400 50  0000 C CNN
F 2 "Arduino Shields:Arduino_Pro_Micro" H 6100 5050 50  0001 C CNN
F 3 "" H 6100 5050 50  0001 C CNN
	1    4900 3950
	1    0    0    -1  
$EndComp
$Comp
L SW_DPST_x2 SW1
U 1 1 5A4B8DC5
P 6800 4400
F 0 "SW1" H 6800 4525 50  0000 C CNN
F 1 "SW_DPST_x2" H 6800 4300 50  0000 C CNN
F 2 "" H 6800 4400 50  0001 C CNN
F 3 "" H 6800 4400 50  0001 C CNN
	1    6800 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3850 6400 3850
Wire Wire Line
	6400 3850 6400 3100
Wire Wire Line
	6400 3100 6100 3100
$Comp
L GND #PWR1
U 1 1 5A4B8F17
P 3600 5600
F 0 "#PWR1" H 3600 5350 50  0001 C CNN
F 1 "GND" H 3600 5450 50  0000 C CNN
F 2 "" H 3600 5600 50  0001 C CNN
F 3 "" H 3600 5600 50  0001 C CNN
	1    3600 5600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 5A4B8F40
P 7700 2100
F 0 "#PWR2" H 7700 1850 50  0001 C CNN
F 1 "GND" H 7700 1950 50  0000 C CNN
F 2 "" H 7700 2100 50  0001 C CNN
F 3 "" H 7700 2100 50  0001 C CNN
	1    7700 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 2500 3500 2500
Wire Wire Line
	3500 2500 3500 2100
Wire Wire Line
	3500 2100 6900 2100
Wire Wire Line
	6900 2100 6900 2700
Wire Wire Line
	6900 2700 7100 2700
Wire Wire Line
	7700 2100 7400 2100
Wire Wire Line
	7400 2100 7400 2400
Wire Wire Line
	3650 5300 3600 5300
Wire Wire Line
	3600 5300 3600 5600
Wire Wire Line
	6100 3700 6300 3700
Wire Wire Line
	6300 3700 6300 4400
Wire Wire Line
	6300 4400 6600 4400
$EndSCHEMATC