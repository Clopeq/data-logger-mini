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

    change_mode(PULSE); // default to PULSE mode
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
    sleep(10);
    digitalWrite(RST_PIN, LOW);
    sleep(1);
    digitalWrite(RST_PIN, HIGH);
    sleep(10);
}

void ADS1263::set_debug(bool state) {
    debug = state;
}

void ADS1263::set_data_rate(ADC_DRATE new_drate) {
    
    // REG_MODE2 structure: [BYPAS][3 bits GAIN][4 bits DRATE]
    unsigned char buf = read_register(REG_MODE2);       // reads current REG_MODE2
    buf &= 0b11110000;                                    // sets DRATE bits to 0, keeps GAIN bits as is
    buf |= (unsigned char)new_drate;                    // sets DRATE bits to the commanded value

    if(debug) {
        cout << "set_data_rate" << endl;
        cout << "new_reg_value: " << bitset<8>(buf) << endl;
    }

    write_register(REG_MODE2, buf);                     // push to the register
}

void ADS1263::set_gain(ADC_GAIN new_gain) {
        
    // REG_MODE2 structure: [BYPAS][3 bits GAIN][4 bits DRATE]
    unsigned char buf = read_register(REG_MODE2);       // reads current REG_MODE2
    buf &= 0b10001111;                                    // sets GAIN bits to 0, keeps DRATE bits as is
    buf |= ((unsigned char)new_gain)<<4;                // sets GAIN bits to the commanded value

    if(debug) {
        cout << "set_gain" << endl;
        cout << "new_reg_value: " << bitset<8>(buf) << endl;
    }

    write_register(REG_MODE2, buf);                     // push to the register
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

void ADS1263::change_mode(ADC_RUNMODE mode) {
    // REG_MODE0 structure: [REFREV][RUNMODE][2 bits CHOP][4 bits DELAY]
    unsigned char buf = read_register(REG_MODE2);           // reads current REG_MODE0
    buf &= 0b11110000;                                      // sets RUNMODE bit to 0, keeps other bits as is
    buf |= (unsigned char)mode<<6;                          // sets RUNMODE bit to the commanded value

    write_register(REG_MODE0, buf);                         // push to the register
}

double ADS1263::read(unsigned char channel) {
    change_mode(PULSE);

    digitalWrite(CS_PIN,  LOW);
    SPI_write(CMD_START1);
    digitalWrite(CS_PIN, HIGH);

    cout << "digitalRead(DRDY): " << digitalRead(DRDY_PIN) << endl;
    
    WPIWfiStatus wfistatus = waitForInterrupt2(DRDY_PIN, INT_EDGE_FALLING, 5000, 0);
    sleep(1);
    
    cout << "Data ready for readout!" << endl;
    cout << "status: " << wfistatus.statusOK << endl;
    // cout << "pinBCM: " << wfistatus.pinBCM << endl;
    // cout << "edge: " << wfistatus.edge << endl;
    // cout << "timeStamp: " << wfistatus.timeStamp_us << " us" << endl;
    cout << "digitalRead(DRDY): " << digitalRead(DRDY_PIN) << endl << endl;

    digitalWrite(CS_PIN,  LOW);
    for(int i=0; i<6; i++) {
        cout << "byte" << i << " :" << bitset<8>(SPI_read()) << endl;
    }
    SPI_write(CMD_STOP1);
    digitalWrite(CS_PIN, HIGH);
    
    cout << "digitalRead(DRDY): " << digitalRead(DRDY_PIN) << endl;
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


