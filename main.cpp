#include "mbed.h"
#include <cstdio>
using namespace std::chrono;
// main() runs in its own thread in the OS
/*
functions used:
pulse_width_ms()
period_ms()
*/
AnalogOut Aout(PA_4);
float reading;
float pi = 3.14159;
float period = 1;
float offset = period/2000;
float rads;
float width= offset * (cos(rads+pi)) + offset;
int sample = 128;
int i;
float ADCdata[128];

PwmOut led (D13);
AnalogIn Ain(A0);
Thread t1;
Thread t2;

void capturing(){
    while(1){
        for(i=0;i<128;i++){
            ADCdata[i]=Ain.read();
            printf("%f\r\n",ADCdata[i]);
            //printf("%d\n",i);
            wait_us(1000);
        }   
    }
}

void generating_waveform(){
    while(1){
        for(int i =0;i<360;i=i+5){
            //printf("%f\n",width);
            rads=(pi*i)/180.0f;
            width= offset * (cos(rads)) + offset;
            led.pulsewidth(width);
            ThisThread::sleep_for(1ms);
        }
    }
}

int main()
{
    led.period_ms(period);
    t1.start(generating_waveform);
    t2.start(capturing);
    
    
    // while(1){
    //      for(int i =0;i<360;i++){
    //         rads=pi*i/180.0f;
    //         led.pulsewidth_ms(width);
    //         wait_us(2000000/360);
    //         printf("%d\n",i);
    //      }
    // }
    
    // while (true) {
    //     for(int i =0;i<360;i++){
    //         rads=pi*i/180.0f;
    //         led.pulsewidth_ms(width);
    //         printf("%d\n", i );
    //         wait_us(1000000/360);
    //     }

    //     for(int i =360;i>0;i--){
    //         rads=pi*i/180.0f;
    //         led.pulsewidth_ms(width);
    //         printf("%d\n", i );
    //         wait_us(1000000/360);
    //     }
    // }
}

