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

    change_mode(CONTINOUS); // default to PULSE/CONTINOUS mode

    // set up input multiplexer (channel selection)
    // INPMUX Register [4 bits MUXP][4 bits MUXN]
    /* MUXP: 
        Positive Input Multiplexer
        Selects the positive input multiplexer.
        0000: AIN0 (default)    0001: AIN1      0010: AIN2      0011: AIN3
        0100: AIN4              0101: AIN5      0110: AIN6      0111: AIN7
        1000: AIN8              1001: AIN9      1010: AINCOM
        1011: Temperature sensor monitor positive
        1100: Analog power supply monitor positive
        1101: Digital power supply monitor positive
        1110: TDAC test signal positive
        1111: Float (open connection)
    */
    /* MUXN:
        Negative Input Multiplexer
        Selects the negative input multiplexer.
        0000: AIN0      0001: AIN1 (default)    0010: AIN2      0011: AIN3
        0100: AIN4      0101: AIN5              0110: AIN6      0111: AIN7
        1000: AIN8      1001: AIN9              1010: AINCOM
        1011: Temperature sensor monitor negative
        1100: Analog power supply monitor negative
        1101: Digital power supply monitor negative
        1110: TDAC test signal negative
        1111: Float (open connection)
    */

    unsigned char buf = read_register(REG_INPMUX);  // get currnet register value
    buf &= 0b11110000;                              // keep Positive Input Multiplexer, zero out Negative Input Multiplexer 
    buf |= 0b00001010;                              // Set MUXN to AINCOM - esentially set up to read single ended channel        
    write_register(REG_INPMUX, buf);                // push to the register


    // set the default filter (FIR filter limits the sample rate to SPS_20)
    // MDOE1 register [3 bits FILTER][SBADC][SBPOL][3 bits SBMAG]
    buf = read_register(REG_MODE1);     // get currnet register value
    buf &= 0b00011111;                  // reset FILTER to 0
    buf |= 0b00000000;                  // set new FILTER
    write_register(REG_INPMUX, buf);    // push to the register
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

    if((unsigned char)new_gain > 5) {
        unsigned char gain = 1;
        for (int i=0; i<new_gain; i++) {
            gain *= 2;
        }
        cout << "WARNING! Cannot set gain to: GAIN_" << (int)gain << " | ADC1 max gain is GAIN_32" << endl;
        cout << "WARNING! The ADC1 gain has been set to GAIN_32" << endl;

        new_gain = GAIN_32;
    }
        
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

    buf = read_register(reg);
    if(buf != val) {
        cout << "Writing to register (" << bitset<8>(reg) << ") has failed" << endl;
        cout << "Requested value: " << bitset<8>(val) << " | Actual value: " << bitset<8>(buf) << endl;
        return -1;
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
    //sleep(1);
    
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


