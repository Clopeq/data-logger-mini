#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <bitset>
#include <unistd.h>



// move the below preprocessor macro to wiringPi.h library

#if defined(__has_include)
    #if __has_include(<wiringPi.h>)
        #include <wiringPi.h>
        #include <wiringPiSPI.h>
    #else
        // wiringPi header not available for IntelliSense/host build — provide minimal stubs
        // so the editor doesn't flag missing include while the code still compiles on Raspberry Pi.

        enum WPIPinType {
            WPI_PIN_BCM,
            WPI_PIN_WPI,
            WPI_PIN_PHYS
        };

        enum WPIPinMode {
            OUTPUT,
            INPUT,
        };

        enum WPIPinValue {
            HIGH = 1,
            LOW = 0
        };

        inline int wiringPiSPISetup(int channel, int speed) { return -1; }
        inline int wiringPiSPIClose(int channel) { return -1; }
        inline int wiringPiSPIClose(int channel) { return -1; }
        inline int wiringPiSPIDataRW (int channel, unsigned char *data, int len) { return -1; }
        inline int wiringPiSetupPinType(enum WPIPinType pinType) { return -1; }
        inline void pinMode(int pin, enum WPIPinMode mode);
        inline void digitalWrite(int pin, int value);
    #endif
#else
    #include <wiringPi.h>
    #include <wiringPiSPI.h>
#endif

// define pinout (BCM numbering)
// TODO: move it to ADC library

const int RST_PIN = 18;
const int CS_PIN = 22;
const int DRDY_PIN = 17;
const int SPI_CHANNEL = 0;
const int SPI_RATE = 250 * 1000;

void setupGPIO() {
    wiringPiSetupPinType(WPI_PIN_BCM);
    pinMode(RST_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    pinMode(DRDY_PIN, INPUT);

    digitalWrite(RST_PIN, HIGH);
    digitalWrite(CS_PIN, HIGH);
    digitalWrite(DRDY_PIN, HIGH);
}

typedef enum
{
    CMD_RESET   = 0x06, // Reset the ADC, 0000 011x (06h or 07h)
    CMD_START1  = 0x08, // Start ADC1 conversions, 0000 100x (08h or 09h)
    CMD_STOP1   = 0x0A, // Stop ADC1 conversions, 0000 101x (0Ah or 0Bh)
    CMD_START2  = 0x0C, // Start ADC2 conversions, 0000 110x (0Ch or 0Dh)
    CMD_STOP2   = 0x0E, // Stop ADC2 conversions, 0000 111x (0Eh or 0Fh)
    CMD_RDATA1  = 0x12, // Read ADC1 data, 0001 001x (12h or 13h)
    CMD_RDATA2  = 0x14, // Read ADC2 data, 0001 010x (14h or 15h)
    CMD_SYOCAL1 = 0x16, // ADC1 system offset calibration, 0001 0110 (16h)
    CMD_SYGCAL1 = 0x17, // ADC1 system gain calibration, 0001 0111 (17h)
    CMD_SFOCAL1 = 0x19, // ADC1 self offset calibration, 0001 1001 (19h)
    CMD_SYOCAL2 = 0x1B, // ADC2 system offset calibration, 0001 1011 (1Bh)
    CMD_SYGCAL2 = 0x1C, // ADC2 system gain calibration, 0001 1100 (1Ch)
    CMD_SFOCAL2 = 0x1E, // ADC2 self offset calibration, 0001 1110 (1Eh)
    CMD_RREG    = 0x20, // Read registers 001r rrrr (20h+000r rrrr)
    CMD_RREG2   = 0x00, // number of registers to read minus 1, 000n nnnn
    CMD_WREG    = 0x40, // Write registers 010r rrrr (40h+000r rrrr)
    CMD_WREG2   = 0x00, // number of registers to write minus 1, 000n nnnn
} ADC_CMD;

typedef enum
{
    /*Register address, followed by reset the default values */
    REG_ID  = 0,    // xxh
    REG_POWER,      // 11h
    REG_INTERFACE,  // 05h
    REG_MODE0,      // 00h
    REG_MODE1,      // 80h
    REG_MODE2,      // 04h
    REG_INPMUX,     // 01h
    REG_OFCAL0,     // 00h
    REG_OFCAL1,     // 00h
    REG_OFCAL2,     // 00h
    REG_FSCAL0,     // 00h
    REG_FSCAL1,     // 00h
    REG_FSCAL2,     // 40h
    REG_IDACMUX,    // BBh
    REG_IDACMAG,    // 00h
    REG_REFMUX,     // 00h
    REG_TDACP,      // 00h
    REG_TDACN,      // 00h
    REG_GPIOCON,    // 00h
    REG_GPIODIR,    // 00h
    REG_GPIODAT,    // 00h
    REG_ADC2CFG,    // 00h
    REG_ADC2MUX,    // 01h
    REG_ADC2OFC0,   // 00h
    REG_ADC2OFC1,   // 00h
    REG_ADC2FSC0,   // 00h
    REG_ADC2FSC1,   // 40h
} ADC_REG;



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


void ADC_reset() {
    digitalWrite(RST_PIN, HIGH);
    sleep(0.3);
    digitalWrite(RST_PIN, LOW);
    sleep(0.3);
    digitalWrite(RST_PIN, HIGH);
    sleep(0.3);
}



unsigned char SPI_write(unsigned char value) {
    unsigned char temp = 0;
    wiringPiSPIDataRW(SPI_CHANNEL, &value, 1);
    temp = value;

    return temp;
}

unsigned char SPI_read() {
    return SPI_write(0x00);
}

unsigned char ADC_read_register(unsigned char reg) {
    unsigned char temp = 0;
    digitalWrite(CS_PIN, 0);
    SPI_write(CMD_RREG | reg); // CMD_RREG 0b 001r rrrr
    cout << "COMMAND: " << bitset<8>(CMD_RREG | reg) << endl;
    SPI_write(1); // no op byte (opcode 2)
    // delay 1ms (?)
    temp = SPI_read();
    cout << "Read byte: " << temp << endl;
    digitalWrite(CS_PIN, 1);
    return temp;
}

unsigned char ADC_init(int rate) {
    ADC_reset();
    unsigned char ID = (ADC_read_register(REG_ID));

    cout << "ID: " << ID << endl;

    return 0;
}


int main() {
    
    cout << "Hello, World!" << endl;

    setupGPIO();

    wiringPiSPISetup(SPI_CHANNEL, SPI_RATE);

    ADC_init(0);

    wiringPiSPIClose(SPI_CHANNEL);

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
