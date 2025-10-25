#include <iostream>
#include <bitset>
#include "ADC.h"    
#include "WPI.h"    // wiringPi
#include "sleep.h"  
#include "config.h" // configuration constans and flags

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
        inline int wiringPiSPISetupMode(int channel, int speed, int mode) { return -1; }
    #endif
#else
    #include <wiringPi.h>
    #include <wiringPiSPI.h>
#endif

using namespace std;



ADS1263::ADS1263(int datarate) { // init
    // Setup GPIO
    wiringPiSPISetupMode(SPI_CHANNEL, SPI_RATE, 1);
    wiringPiSetupPinType(WPI_PIN_BCM);
    pinMode(RST_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    pinMode(DRDY_PIN, INPUT);

    digitalWrite(RST_PIN, HIGH);
    digitalWrite(CS_PIN, HIGH);
    digitalWrite(DRDY_PIN, HIGH);

    set_debug(DEBUG);

    reset();
}

ADS1263::~ADS1263() {
    close();
}

void ADS1263::close() {
    // TODO stop conversion or whatever

    wiringPiSPIClose(SPI_CHANNEL);
    cout << "ADC has been terminated!" << endl;
}

void ADS1263::reset() {
    digitalWrite(RST_PIN, HIGH);
    sleep(300);
    digitalWrite(RST_PIN, LOW);
    sleep(300);
    digitalWrite(RST_PIN, HIGH);
    sleep(300);
}

void ADS1263::set_debug(bool state) {
    debug = state;
}

unsigned char ADS1263::read_register(ADC_REG reg) {
    unsigned char buf = 0;
    unsigned char command = (unsigned char)CMD_RREG | (unsigned char)reg;
    digitalWrite(CS_PIN, LOW); // CS_PIN has to be low for SPI communication

    SPI_write(command); // CMD_RREG 0b 001r rrrr
    SPI_write(CMD_NOP);
    buf = SPI_read();

    digitalWrite(CS_PIN, HIGH); // Reset CS_PIN back to HIGH (stop SPI communication)

    if(debug) {
        cout << "COMMAND: " << bitset<8>(command) << endl;
        cout << "register: " << bitset<8>(buf) << endl;
    }

    return buf;
}


unsigned char ADS1263::write_register(ADC_REG reg, unsigned char val) {
    cout << "Rgister writing is not yet implemented, this call did nothing" << endl;
    return 0;
}

// #########################################################################################
// #################################### PRIVATE METHODS ####################################
// #########################################################################################


unsigned char ADS1263::SPI_write(unsigned char value) {
    unsigned char buf = value;
    wiringPiSPIDataRW(SPI_CHANNEL, &buf, 1);
    return buf; // received byte
}

unsigned char ADS1263::SPI_read() {
    return SPI_write(CMD_NOP);
}


