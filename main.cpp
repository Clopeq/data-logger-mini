#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <time.h>
#include "./Pages/live_view.h"
#include "ADS1263_wrapper.h"
#include <stdio.h>
#include <string.h>
#include "Loadcell.h"
#include <iostream>

using namespace std;

// ADC1 test part
#define TEST_ADC1       1
// ADC1 rate test par
#define TEST_ADC1_RATE  0
// ADC2 test part
#define TEST_ADC2       0
// RTD test part    
#define TEST_RTD        0

//#define REF         5.08        //Modify according to actual voltage
                                //external AVDD and AVSS(Default), or internal 2.5V

void  Handler(int signo)
{
    //System Exit
    printf("\r\n END \r\n");
    DEV_Module_Exit();
    exit(0);
}

int main(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    
    printf("ADS1263 Demo \r\n");
    DEV_Module_Init();

    // 0 is singleChannel, 1 is diffChannel
    ADS1263_SetMode(0);
    
    // The faster the rate, the worse the stability
    // and the need to choose a suitable digital filter(REG_MODE1)
    if(ADS1263_init_ADC1(ADS1263_38400SPS) == 1) {
        printf("\r\n END \r\n");
        DEV_Module_Exit();
        exit(0);
    }

    // ------------------ END INIT --------------
    
    short int ch = 0;
    Loadcell LC1(ch);
    printf("Pre tare: %lf\n", LC1.read());
    LC1.tare();
    printf("Post tare: %lf\n", LC1.read());

    int a;
    printf("Place a load on a loadcell\n");
    scanf("%d", &a);

    printf("pre calibrate: %lf\n", LC1.read());
    double arr[2];
    LC1.calibrate(100, arr);
    printf("post calibrate: %lf\n", LC1.read());

    scanf("%d", &a);
    

    while(true) {
        printf("%lf \n", LC1.read());
        printf("\33[1A");
    }  

    return 0;
}
