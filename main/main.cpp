// uLCD-144-G2 basic text demo program for uLCD-4GL LCD driver library
//
#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
InterruptIn BT1(A3), BT2(A4), BT3(A5);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
EventQueue queue2(32 * EVENTS_EVENT_SIZE);
EventQueue queue3(128 * EVENTS_EVENT_SIZE);
AnalogOut  aout(PA_4);
AnalogIn ain(A0);
int U = 0;
int DO = 0;
int SEL = 0;
float ADCdata[240];

Thread t, TDAC, TADC;


void ADC_102() {
    TADC.start(callback(&queue3, &EventQueue::dispatch_forever));
    for (int i = 0; i < 240; i++) {
        printf("%f\r\n", ADCdata[i] * 3.3);
        ThisThread::sleep_for(100ms);
    }
}

void UP_() {
    U = 1;
}
void DOWN_() {
    DO = 1;
}
void SEL_() {
    SEL = 1;
}


int ULCD() {
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    BT1.fall(queue.event(UP_));
    BT2.fall(queue.event(DOWN_));
    BT3.fall(queue.event(SEL_));
    int CUR = 1;
    uLCD.background_color(WHITE);
    uLCD.cls();
    uLCD.color(BLUE);
    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.locate(1,1);
    uLCD.printf(" 1 \n");
    uLCD.locate(1,2);
    uLCD.printf("1/2\n");
    uLCD.locate(1,3);
    uLCD.printf("1/4\n");
    uLCD.locate(1,4);
    uLCD.printf("1/8\n");
    uLCD.color(RED);
    while(SEL == 0) {
        while(CUR == 1) {
            uLCD.locate(7,2);
            uLCD.printf(" ");
            uLCD.locate(7,3);
            uLCD.printf(" ");
            uLCD.locate(7,4);
            uLCD.printf(" ");
            uLCD.locate(7,1);
            uLCD.printf("<");
            if(U) {
                U = 0;
                CUR = 1;
            }; 
            if(DO) {
                DO = 0;
                CUR = 2;
            };
            if(SEL) {
                SEL = 0;
                uLCD.color(WHITE);
                uLCD.locate(7,1);
                uLCD.printf("<");
                return CUR;
            }
        }
        while(CUR == 2) {
            uLCD.locate(7,2);
            uLCD.printf("<");
            uLCD.locate(7,3);
            uLCD.printf(" ");
            uLCD.locate(7,4);
            uLCD.printf(" ");
            uLCD.locate(7,1);
            uLCD.printf(" ");
            if(U) {
                U = 0;
                CUR = 1;
            }; 
            if(DO) {
                DO = 0;
                CUR = 4;
            };
            if(SEL) {
                SEL = 0;
                uLCD.color(WHITE);
                uLCD.locate(7,2);
                uLCD.printf("<");
                return CUR;
            }
        }
        while(CUR == 4) {
            uLCD.locate(7,2);
            uLCD.printf(" ");
            uLCD.locate(7,3);
            uLCD.printf("<");
            uLCD.locate(7,4);
            uLCD.printf(" ");
            uLCD.locate(7,1);
            uLCD.printf(" ");
            if(U) {
                U = 0;
                CUR = 2;
            }; 
            if(DO) {
                DO = 0;
                CUR = 8;
            };
            if(SEL) {
                SEL = 0;
                uLCD.color(WHITE);
                uLCD.locate(7,3);
                uLCD.printf("<");
                return CUR;
            }
        }
        while(CUR == 8) {
            uLCD.locate(7,2);
            uLCD.printf(" ");
            uLCD.locate(7,3);
            uLCD.printf(" ");
            uLCD.locate(7,4);
            uLCD.printf("<");
            uLCD.locate(7,1);
            uLCD.printf(" ");
            if(U) {
                U = 0;
                CUR = 4;
            }; 
            if(DO) {
                DO = 0;
                CUR = 8;
            };
            if(SEL) {
                SEL = 0;
                uLCD.color(WHITE);
                uLCD.locate(7,4);
                uLCD.printf("<");
                return CUR;
            }
        }

        
        }

}
int DAC_102() {
    TDAC.start(callback(&queue2, &EventQueue::dispatch_forever));
    int x = ULCD();
    
    if(x == 1) {      
        int g = 0;
        while (1) {
            
            while (1) {
                for (float i = 0.0f; i < 240.0f; i += 1.0f) {
                    double sam = 0;
                    if(i < 80) {
                       sam =  i / 80 * 9 / 10;
                       ThisThread::sleep_for(1ms);  
                    }
                    else  if (i > 160){
                       sam = (240 - i) / 80 * 9 / 10;
                       ThisThread::sleep_for(1ms);  
                    }
                    else {
                        sam = 0.9;
                        ThisThread::sleep_for(1ms);  
                    }
                    aout = sam;
                    if (g%3 == 0)
                    ADCdata[g/3] = ain;
                    g++;
                               
                }
                if (g == 721) {
                    ADC_102();
                    return 0;
                }
            }
        }
    }
        if(x == 2) {

        
        while (1) {

            int g = 0;
            while (1) {
                for (float i = 0.0f; i < 240.0f; i += 1.0f) {
                    double sam = 0;
                    if(i < 40) {
                       sam =  i / 40 * 9 / 10;
                       ThisThread::sleep_for(1ms);  
                    }
                    else  if (i > 200){
                       sam = (240 - i) / 40 * 9 / 10;
                       ThisThread::sleep_for(1ms);  
                    }
                    else {
                        sam = 0.9;
                        ThisThread::sleep_for(1ms);  
                    }
                    aout = sam;
                    if (g%3 == 0)
                    ADCdata[g/3] = ain;
                    g++;
                               
                }
                if (g == 720) {
                    ADC_102();
                    return 0;
                }
            }
        }
        }
        if(x == 4) {
  
        
        while (1) {
        
            int g = 0;
            while (1) {
                for (float i = 0.0f; i < 240.0f; i += 1.0f) {
                    double sam = 0;
                    if(i < 20) {
                       sam =  i / 20 * 9 / 10;
                       ThisThread::sleep_for(1ms);  
                    }
                    else  if (i > 220){
                       sam = (240 - i) / 20 * 9 / 10;
                       ThisThread::sleep_for(1ms);  
                    }
                    else {
                        sam = 0.9;
                        ThisThread::sleep_for(1ms);  
                    }
                    aout = sam;
                    if (g%3 == 0)
                    ADCdata[g/3] = ain;
                    g++;
                               
                }
                if (g == 720) {
                    ADC_102();
                    return 0;
                }
            }
        }
        }
        if(x == 8) {
     
        int g = 0;
        while (1) {
 
            int g = 0;
            while (1) {
                for (float i = 0.0f; i < 240.0f; i += 1.0f) {
                    double sam = 0;
                    if(i < 10) {
                       sam =  i / 10 * 9 / 10;
                       ThisThread::sleep_for(1ms);  
                    }
                    else  if (i > 230){
                       sam = (240 - i) / 10 * 9 / 10;
                       ThisThread::sleep_for(1ms);  
                    }
                    else {
                        sam = 0.9;
                        ThisThread::sleep_for(1ms);  
                    }
                    aout = sam;
                    if (g%3 == 0)
                    ADCdata[g/3] = ain;
                    g++;
                               
                }
                if (g == 720) {
                    ADC_102();
                    return 0;
                }
            }
        }
        }

}
int main()
{
    DAC_102();
    return 0;
}