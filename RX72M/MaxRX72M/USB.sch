EESchema Schematic File Version 4
LIBS:MaxRX72M-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 9
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
L Connector:USB_A J?
U 1 1 5DC3C34C
P 3250 4350
F 0 "J?" H 3307 4817 50  0000 C CNN
F 1 "USB_A" H 3307 4726 50  0000 C CNN
F 2 "" H 3400 4300 50  0001 C CNN
F 3 " ~" H 3400 4300 50  0001 C CNN
	1    3250 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 4450 4500 4450
Wire Wire Line
	3550 4350 4150 4350
$Comp
L power:GND #PWR?
U 1 1 5DC405BA
P 3250 5000
F 0 "#PWR?" H 3250 4750 50  0001 C CNN
F 1 "GND" H 3255 4827 50  0000 C CNN
F 2 "" H 3250 5000 50  0001 C CNN
F 3 "" H 3250 5000 50  0001 C CNN
	1    3250 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 4750 3250 4900
Wire Wire Line
	3250 4900 3150 4900
Wire Wire Line
	3150 4900 3150 4750
Connection ~ 3250 4900
Wire Wire Line
	3250 4900 3250 5000
$Comp
L Device:D_Zener_Small_ALT D?
U 1 1 5DC4137C
P 4150 4650
F 0 "D?" V 4104 4718 50  0000 L CNN
F 1 "6.8V" V 4195 4718 50  0000 L CNN
F 2 "" V 4150 4650 50  0001 C CNN
F 3 "~" V 4150 4650 50  0001 C CNN
	1    4150 4650
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener_Small_ALT D?
U 1 1 5DC41E0F
P 4500 4650
F 0 "D?" V 4454 4718 50  0000 L CNN
F 1 "6.8V" V 4545 4718 50  0000 L CNN
F 2 "" V 4500 4650 50  0001 C CNN
F 3 "~" V 4500 4650 50  0001 C CNN
	1    4500 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	4150 4550 4150 4350
Wire Wire Line
	4500 4450 4500 4550
Connection ~ 4500 4450
Wire Wire Line
	4500 4450 5400 4450
Wire Wire Line
	4150 4750 4150 4900
Wire Wire Line
	4150 4900 4500 4900
Wire Wire Line
	4500 4900 4500 4750
Wire Wire Line
	4150 4900 4150 5000
Connection ~ 4150 4900
$Comp
L power:GND #PWR?
U 1 1 5DC438AD
P 4150 5000
F 0 "#PWR?" H 4150 4750 50  0001 C CNN
F 1 "GND" H 4155 4827 50  0000 C CNN
F 2 "" H 4150 5000 50  0001 C CNN
F 3 "" H 4150 5000 50  0001 C CNN
	1    4150 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC43B20
P 5100 4900
F 0 "#PWR?" H 5100 4650 50  0001 C CNN
F 1 "GND" H 5105 4727 50  0000 C CNN
F 2 "" H 5100 4900 50  0001 C CNN
F 3 "" H 5100 4900 50  0001 C CNN
	1    5100 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4900 5100 4750
Wire Wire Line
	5100 4750 5400 4750
$Comp
L renesas:RX72M_176 U?
U 5 1 5E871650
P 6000 4400
F 0 "U?" H 6428 4446 50  0000 L CNN
F 1 "RX72M_176" H 6428 4355 50  0000 L CNN
F 2 "Package_QFP:LQFP-176_24x24mm_P0.5mm" H 6050 2200 50  0001 C CNN
F 3 "" H 5950 4100 50  0001 C CNN
	5    6000 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 4350 5400 4350
Connection ~ 4150 4350
$EndSCHEMATC
