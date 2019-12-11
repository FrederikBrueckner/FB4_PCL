EESchema Schematic File Version 4
EELAYER 29 0
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
L Transistor_FET:DMG2301L Q1
U 1 1 6189340F
P 4350 3950
F 0 "Q1" V 4693 3950 50  0000 C CNN
F 1 "DMG2301L" V 4602 3950 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4550 3875 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMG2301L.pdf" H 4350 3950 50  0001 L CNN
	1    4350 3950
	0    1    -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 61895388
P 4850 4450
F 0 "R2" H 4920 4496 50  0000 L CNN
F 1 "100k" H 4920 4405 50  0000 L CNN
F 2 "" V 4780 4450 50  0001 C CNN
F 3 "~" H 4850 4450 50  0001 C CNN
	1    4850 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 618957D2
P 6050 4450
F 0 "R4" H 6120 4496 50  0000 L CNN
F 1 "1M" H 6120 4405 50  0000 L CNN
F 2 "" V 5980 4450 50  0001 C CNN
F 3 "~" H 6050 4450 50  0001 C CNN
	1    6050 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6189597C
P 5650 4450
F 0 "R3" H 5720 4496 50  0000 L CNN
F 1 "100k" H 5720 4405 50  0000 L CNN
F 2 "" V 5580 4450 50  0001 C CNN
F 3 "~" H 5650 4450 50  0001 C CNN
	1    5650 4450
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:MMBT3904 Q2
U 1 1 61896169
P 4450 4950
F 0 "Q2" H 4641 4996 50  0000 L CNN
F 1 "MMBT3904" H 4641 4905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4650 4875 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 4450 4950 50  0001 L CNN
	1    4450 4950
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:MMBT3904 Q3
U 1 1 61896AA2
P 5750 5300
F 0 "Q3" H 5941 5346 50  0000 L CNN
F 1 "MMBT3904" H 5941 5255 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5950 5225 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 5750 5300 50  0001 L CNN
	1    5750 5300
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 61897320
P 6050 5500
F 0 "C1" H 6165 5546 50  0000 L CNN
F 1 "22µ" H 6165 5455 50  0000 L CNN
F 2 "" H 6088 5350 50  0001 C CNN
F 3 "~" H 6050 5500 50  0001 C CNN
	1    6050 5500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW1
U 1 1 6189871B
P 5250 4950
F 0 "SW1" H 5250 5185 50  0000 C CNN
F 1 "SW_SPST" H 5250 5094 50  0000 C CNN
F 2 "" H 5250 4950 50  0001 C CNN
F 3 "~" H 5250 4950 50  0001 C CNN
	1    5250 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 61898ED8
P 4350 5250
F 0 "#PWR01" H 4350 5000 50  0001 C CNN
F 1 "GND" H 4355 5077 50  0000 C CNN
F 2 "" H 4350 5250 50  0001 C CNN
F 3 "" H 4350 5250 50  0001 C CNN
	1    4350 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 61899209
P 5650 5800
F 0 "#PWR02" H 5650 5550 50  0001 C CNN
F 1 "GND" H 5655 5627 50  0000 C CNN
F 2 "" H 5650 5800 50  0001 C CNN
F 3 "" H 5650 5800 50  0001 C CNN
	1    5650 5800
	1    0    0    -1  
$EndComp
Text GLabel 6150 3850 2    50   Input ~ 0
PWR_OUT
Text GLabel 3900 3850 0    50   Input ~ 0
PWR_IN
Wire Wire Line
	4350 4150 4350 4600
Wire Wire Line
	3900 3850 4000 3850
Connection ~ 4000 3850
Wire Wire Line
	4000 3850 4100 3850
Wire Wire Line
	4000 4400 4000 4600
Wire Wire Line
	4000 4600 4350 4600
Connection ~ 4350 4600
Wire Wire Line
	4350 4600 4350 4750
Wire Wire Line
	4000 3850 4000 4100
$Comp
L Device:R R1
U 1 1 61894E6F
P 4000 4250
F 0 "R1" H 4070 4296 50  0000 L CNN
F 1 "100k" H 4070 4205 50  0000 L CNN
F 2 "" V 3930 4250 50  0001 C CNN
F 3 "~" H 4000 4250 50  0001 C CNN
	1    4000 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4600 4850 4950
Wire Wire Line
	4850 4950 4650 4950
Wire Wire Line
	4850 4950 5050 4950
Connection ~ 4850 4950
Wire Wire Line
	4350 5250 4350 5150
Wire Wire Line
	5450 4950 5650 4950
Wire Wire Line
	5650 4600 5650 4950
Wire Wire Line
	5650 4950 5650 5100
Connection ~ 5650 4950
Wire Wire Line
	5650 5500 5650 5700
Wire Wire Line
	6050 5650 6050 5700
Wire Wire Line
	6050 5700 5650 5700
Connection ~ 5650 5700
Wire Wire Line
	5650 5700 5650 5800
Wire Wire Line
	6050 5350 6050 5300
Wire Wire Line
	6050 5300 5950 5300
Wire Wire Line
	6050 4600 6050 5300
Connection ~ 6050 5300
Wire Wire Line
	6150 3850 6050 3850
Wire Wire Line
	6050 3850 6050 4300
Wire Wire Line
	6050 3850 4850 3850
Connection ~ 6050 3850
Wire Wire Line
	4850 4300 4850 3850
Connection ~ 4850 3850
Wire Wire Line
	4850 3850 4550 3850
Wire Wire Line
	4100 3850 4100 3500
Wire Wire Line
	4100 3500 5650 3500
Wire Wire Line
	5650 3500 5650 4300
Connection ~ 4100 3850
Wire Wire Line
	4100 3850 4150 3850
Text Notes 3600 3150 0    50   ~ 0
Soft latch power toggle\nFür Batteriebetrieb 2 - 10V
$EndSCHEMATC
