#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <time.h>
#include <ADC.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <bitset>
#include <unistd.h>


enum WPIPinType {
    WPI_PIN_BCM,
    WPI_PIN_WPI,
    WPI_PIN_PHYS
};

#if defined(__has_include)
    #if __has_include(<wiringPi.h>)
        #include <wiringPi.h>
        #include <wiringPiSPI.h>
    #else
        // wiringPi header not available for IntelliSense/host build — provide minimal stubs
        // so the editor doesn't flag missing include while the code still compiles on Raspberry Pi.
        inline int wiringPiSPISetup(int channel, int speed) { return -1; }
        inline int wiringPiSPIClose(int channel) { return -1; }
        inline int wiringPiSPIClose(int channel) { return -1; }
        inline int wiringPiSPIDataRW (int channel, unsigned char *data, int len) { return -1; }
        inline int wiringPiSetupPinType(enum WPIPinType pinType) { return -1; }
        inline void pinMode(int pin, int mode);
        inline void digitalWrite(int pin, int value);
    #endif
#else
    #include <wiringPi.h>
    #include <wiringPiSPI.h>
#endif


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

    wiringPiSetupPinType(WPI_PIN_BCM);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    digitalWrite(8, 1);
    digitalWrite(7, 1);



    const int spiChannel = 0;
    const int spiSpeedInit = 250*1000;
    int hSPI;

    if ((hSPI = wiringPiSPISetup(spiChannel, spiSpeedInit)) < 0) {
        // error
        cout << "Could not initialize SPI communication" << endl;
        return 0;
    } else {
        cout << "SPI communication established successfully" << endl;
    }

    sleep(0.1);

    // -------------------------------------------------------------------------------------

    cout << "TRY CS0" << endl;
    digitalWrite(8, 0);

    unsigned char spiData[20];
    int returnvalue;
    spiData[0] = 0b00000110;
    spiData[0] = 0;

    for(int i=2; i<20; i++) {
        spiData[i] = 0;
    }
    
    returnvalue = wiringPiSPIDataRW(spiChannel, spiData, 20);

    for(int i=0; i<20; i++) {
        cout << bitset<8>(spiData[i]) << endl;
    }

    cout << "RESET COMPLETE!" << endl;
    
    sleep(0.1);


    spiData[0] = 0b00100000;
    spiData[1] = 18;
    for(int i=2; i<20; i++) {
        spiData[i] = 0;
    }

    returnvalue = wiringPiSPIDataRW(spiChannel, spiData, 20);

    for(int i=0; i<20; i++) {
        cout << bitset<8>(spiData[i]) << endl;
    }


    cout << endl << "------------------------------------------------" << endl;
    cout << "TRY CS1" << endl;

        spiData[0] = 0b00000110;
    spiData[0] = 0;

    for(int i=2; i<20; i++) {
        spiData[i] = 0;
    }
    
    returnvalue = wiringPiSPIDataRW(spiChannel, spiData, 20);

    for(int i=0; i<20; i++) {
        cout << bitset<8>(spiData[i]) << endl;
    }

    cout << "RESET COMPLETE!" << endl;
    
    sleep(0.1);


    spiData[0] = 0b00100000;
    spiData[1] = 18;
    for(int i=2; i<20; i++) {
        spiData[i] = 0;
    }

    returnvalue = wiringPiSPIDataRW(spiChannel, spiData, 20);

    for(int i=0; i<20; i++) {
        cout << bitset<8>(spiData[i]) << endl;
    }

    wiringPiSPIClose(spiChannel);

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
