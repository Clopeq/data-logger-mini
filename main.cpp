#include <iostream>
#include "Driver/ADS1263.h"

// ADC1 test part
#define TEST_ADC1       1
// ADC1 rate test par
#define TEST_ADC1_RATE  0
// ADC2 test part
#define TEST_ADC2       0
// RTD test part    
#define TEST_RTD        0

#define REF         5.08        //Modify according to actual voltage
                                //external AVDD and AVSS(Default), or internal 2.5V

using namespace std;

int main(void)
{
    UDOUBLE ADC[10];
    UWORD i;
    double RES, TEMP;
    
    printf("ADS1263 Demo \r\n");\

    // 0 is singleChannel, 1 is diffChannel
    ADS1263_SetMode(0);
    
    // The faster the rate, the worse the stability
    // and the need to choose a suitable digital filter(REG_MODE1)
    if(ADS1263_init_ADC1(ADS1263_400SPS) == 1) {
        printf("\r\n END \r\n");
        exit(0);
    }
    
    /* Test DAC */
    // ADS1263_DAC(ADS1263_DAC_VLOT_3, Positive_A6, Open);      
    // ADS1263_DAC(ADS1263_DAC_VLOT_2, Negative_A7, Open);
    
    if(TEST_ADC1) {
        printf("TEST_ADC1\r\n");
        
        #define ChannelNumber 5
        UBYTE ChannelList[ChannelNumber] = {0, 1, 2, 3, 4};    // The channel must be less than 10
            
        UDOUBLE Value[ChannelNumber] = {0};
        while(1) {
            ADS1263_GetAll(ChannelList, Value, ChannelNumber);  // Get ADC1 value
            for(i=0; i<ChannelNumber; i++) {
                if((Value[i]>>31) == 1)
                    printf("IN%d is -%lf \r\n", ChannelList[i], REF*2 - Value[i]/2147483648.0 * REF);      //7fffffff + 1
                else
                    printf("IN%d is %lf \r\n", ChannelList[i], Value[i]/2147483647.0 * REF);       //7fffffff
            }
            for(i=0; i<ChannelNumber; i++) {
                printf("\33[1A");   // Move the cursor up
            }
        }
    }

    return 0;
}

