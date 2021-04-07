# EXAM01
SPEC:
uLCD
BT1(UP) - A3
BT2(DOWN) - A4
BT3(SELECT) - A5
DAC output PA_4
ADC input A0
(Note that PA_4 is connected to A0 for the ADC!)

1. Download the file to a clean dir.
2. After compile the mbed, you can see that uLCD displays 1, 1/2, 1/4, 1/8
3. You can use the UP and DOWN button to choose the different slew rate(a red "<" is there for you to confirm the current choice).
4. You can push the SELECT button to active DAC, then PA_4 would start output the voltage.
5. Execute the FFT.py before you confirm the slew rate, then you can get the graphic made bt python.

1-1 is from the picoscope measuring the slew rate = 1.
2-1 is from the picoscope measuring the slew rate = 1/2.
4-1 is from the picoscope measuring the slew rate = 1/4.
8-1 is from the picoscope measuring the slew rate = 1/8.

1-2 is from the ADC of the slew rate = 1.
2-2 is from the ADC of the slew rate = 1/2.
4-2 is from the ADC of the slew rate = 1/4.
8-2 is from the ADC of the slew rate = 1/8.

DSC_0531 is a pic that I'm testing the program.
