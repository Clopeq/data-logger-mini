#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <time.h>
#include <ADC.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

// #if defined(__has_include)
// #  if __has_include(<wiringPi.h>)
// #    include <wiringPi.h>
// #  else
// // wiringPi header not available for IntelliSense/host build — provide minimal stubs
// // so the editor doesn't flag missing include while the code still compiles on Raspberry Pi.
// inline int wiringPiSPISetup(int channel, int speed) { return -1; }
// inline int wiringPiSPIClose(int channel) { return -1; }
// #  endif
// #else
// #  include <wiringPi.h>
// #endif

#include <wiringPi.h>

//#include "Loadcell.h"

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



int main() {
    
    cout << "Hello, World!" << endl;

    const int spiChannel = 0;
    const int spiSpeedInit = 250*1000;
    int hSPI;

    if ((hSPI = wiringPiSetup(spiChannel, spiSpeedInit)) < 0) {
        // error
        cout << "Could not initialize SPI communication" << endl;
        return 0;
    }

    cout << "SPI communication established successfully" << endl;


    wiringPiClose(spiChannel);

    return 0;
}

// void  Handler(int signo)
// {
//     //System Exit
//     printf("\r\n END \r\n");
//     DEV_Module_Exit();
//     exit(0);
// }

// int main(void)
// {
//     // Exception handling:ctrl + c
//     signal(SIGINT, Handler);
    
//     printf("ADS1263 Demo \r\n");
//     DEV_Module_Init();
//     cout << "Init success!" << endl;


//     // 0 is singleChannel, 1 is diffChannel
//     ADS1263_SetMode(0);
//     cout << "Set mode 0" << endl;
    
//     // The faster the rate, the worse the stability
//     // and the need to choose a suitable digital filter(REG_MODE1)
//     if(ADS1263_init_ADC1(ADS1263_38400SPS) == 1) {
//         printf("\r\n END \r\n");
//         DEV_Module_Exit();
//         exit(0);
//     }

//     // ------------------ END INIT --------------
    
//     while(true) {
//         printf("CH-: %lf\n", ADC_read(0));
//     }

//     return 0;
// }
