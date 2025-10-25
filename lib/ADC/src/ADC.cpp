#include <iostream>
#include <bitset>
#include "ADC.h"    
#include "WPI.h"    // wiringPi
#include "sleep.h"  
#include "config.h" // configuration constans and flags

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

void ADS1263::set_data_rate(ADC_DRATE drate) {
    write_register(REG_MODE2, (unsigned char)drate);
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
        cout << "#### read_register() ####" << endl;
        cout << "COMMAND: " << bitset<8>(command) << endl;
        cout << "register: " << bitset<8>(buf) << endl;
    }

    return buf;
}


unsigned char ADS1263::write_register(ADC_REG reg, unsigned char val) {
    unsigned char buf = 0;
    unsigned char command = (unsigned char)CMD_WREG | (unsigned char)reg;

    digitalWrite(CS_PIN,  LOW);
    SPI_write(command);
    SPI_write(CMD_NOP);
    SPI_write(val);
    digitalWrite(CS_PIN, HIGH);

    if(debug) {
        cout << "#### write_register() ####" << endl;
        cout << "command: " << bitset<8>(command) << endl;
        cout << "value: " << bitset<8>(val) << endl;
    }
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


