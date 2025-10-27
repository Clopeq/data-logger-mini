#include <iostream>
#include <bitset>
#include "ADC.h"    
#include "WPI.h"            // wiringPi
#include "sleep.h"  
#include "config.h"         // configuration constans and flags
#include "ADC_utilities.h"  // enum to string conversion

using namespace std;


// #################################################################################################
// ######################################### CONSTRUCTOR ###########################################
// #################################################################################################

ADS1263::ADS1263(int datarate) {
    /* 
        Constructor initializes the ADS1263 ADC:
        - setup wiringPi SPI communication
        - setup GPIO pins
        - set default flags                     (NOTE: e.g. DEBUG flag)
        - set default register values
    */

    // setup SPI communication
    wiringPiSPISetupMode(SPI_CHANNEL, SPI_RATE, 1);  // mode 1 - 
    wiringPiSetupPinType(WPI_PIN_BCM);

    
    // Setup GPIO
    pinMode(RST_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    pinMode(DRDY_PIN, INPUT);
    digitalWrite(RST_PIN, HIGH);
    digitalWrite(CS_PIN, HIGH);
    digitalWrite(DRDY_PIN, HIGH);

    // set default flags                                                (TODO: load from .json)
    set_debug(DEBUG);

    // set default registers                                            (TODO: load from .json)
    reset();            // reset ADC
    change_mode(PULSE); // default to PULSE/CONTINOUS mode

    // set up input multiplexer (channel selection)
    // INPMUX Register [4 bits MUXP][4 bits MUXN]
    unsigned char buf = read_register(REG_INPMUX);  // get currnet register value
    buf = (buf & 0b11110000) | (unsigned char)COMM; // overwrite MUXN bits to AINCOMM - setup singe-ended mesurement
    write_register(REG_INPMUX, buf);                // push to the register


    // set the default filter (default FIR filter limits the sample rate to SPS_20)
    // MDOE1 register [3 bits FILTER][SBADC][SBPOL][3 bits SBMAG]
    buf = read_register(REG_MODE1);                 // get currnet register value
    buf = (buf & 0b00011111) | 0b00000000;          // set new FILTER
    write_register(REG_MODE1, buf);                 // push to the register

    // set class atributes
    gain = get_gain();
    drate = get_data_rate();
    vref = VREF;
}

ADS1263::~ADS1263() {
    close();
}

// #################################################################################################
// ############################################ USAGE ##############################################
// #################################################################################################

double ADS1263::read(unsigned char channel) {
    change_mode(PULSE);

    digitalWrite(CS_PIN,  LOW);
    SPI_write(CMD_START1);
    digitalWrite(CS_PIN, HIGH);
    
    WPIWfiStatus wfistatus = waitForInterrupt2(DRDY_PIN, INT_EDGE_FALLING, 50, 0);      // 50 ms timeout
    //sleep(1);
    
    cout << "Data ready for readout!" << endl;
    cout << "status: " << wfistatus.statusOK << endl;
    // cout << "pinBCM: " << wfistatus.pinBCM << endl;
    // cout << "edge: " << wfistatus.edge << endl;
    // cout << "timeStamp: " << wfistatus.timeStamp_us << " us" << endl;

    
    unsigned char buf[4];
    digitalWrite(CS_PIN,  LOW);
    SPI_read();
    buf[0] = SPI_read();        // MSB
    buf[1] = SPI_read();
    buf[2] = SPI_read();
    buf[3] = SPI_read();        // LSB
    SPI_read(); 
    SPI_write(CMD_STOP1);
    digitalWrite(CS_PIN, HIGH);

    // combine 8 bytes into single two's complement string of bits
    int32_t combined_buf =  (static_cast<int32_t>(buf[0])<<24) | 
                            (static_cast<int32_t>(buf[1])<<16) |
                            (static_cast<int32_t>(buf[2])<<8) |
                            (static_cast<int32_t>(buf[3]));

    // for positive numbers: input_code/(2^31-1) * VREF/GAIN
    // for negative numbers: input_code/(2^31) * VREF/GAIN
    // Above approach should effectivly apply the scaling factor to the raw output.
    // double voltage = static_cast<double>(combined_buf/0x7FFFFF * vref/(static_cast<int>(gain)));
    return static_cast<double>(combined_buf);
}

// #################################################################################################
// ######################################### CONFIGURATION #########################################
// #################################################################################################

void ADS1263::change_mode(ADC_RUNMODE mode) {
    // REG_MODE0 structure: [REFREV][RUNMODE][2 bits CHOP][4 bits DELAY]
    unsigned char buf = read_register(REG_MODE0);           // reads current REG_MODE0
    buf &= 0b11110000;                                      // sets RUNMODE bit to 0, keeps other bits as is
    buf |= (unsigned char)mode<<6;                          // sets RUNMODE bit to the commanded value

    write_register(REG_MODE0, buf);                         // push to the register
}

unsigned char ADS1263::set_gain(ADC_GAIN new_gain) {
    if (new_gain == get_gain()) {           // the currently set gain is the same as requested -> nothing to do
        return;
    }

    // max GAIN for ADC1 is GAIN_32, GAIN_64 and GAIN_128 are only available for ADC2
    if((unsigned char)new_gain > 5) {       
        cout << "WARNING! Cannot set gain to: " << ADC_GAIN_tostr(new_gain) << " | ADC1 max gain is GAIN_32" << endl;
        cout << "WARNING! The ADC1 gain has been set to GAIN_32" << endl;
        new_gain = GAIN_32;
    }
        
    // REG_MODE2 structure: [BYPAS][3 bits GAIN][4 bits DRATE]
    unsigned char buf = read_register(REG_MODE2);               // reads current REG_MODE2
    buf = (buf & 0b10001111) | ((unsigned char)new_gain)<<4;    // replace GAIN bits

    if(debug) {
        cout << "#### SET_GAIN() ####" << endl;
        cout << "Requested gain: " << ADC_GAIN_tostr(new_gain) << endl;
        cout << "Requested register value: : " << bitset<8>(buf) << endl;
    }

    if(write_register(REG_MODE2, buf)) {                // Push to the register
        gain = new_gain;
        return 1;                                       // The register writing has been successfull
    } else {                                            // The writing to the register has failed
        unsigned char reg = read_register(REG_MODE2);   // Actual register value
        cout << "WARNING: set_gain(): The gain for ADC1 has not been set correctly" << endl;
        cout << "WARNING: Current REG_MDOE2: " << bitset<8>(reg) << " [BYPASS][3 bits GAIN][4 bits DRATE]" << endl;
        cout << "WARNING: Expected REG_MODE2: " << bitset<8>(buf) << " [BYPASS][3 bits GAIN][4 bits DRATE]" << endl;
        return 0;
    }
}

ADC_GAIN ADS1263::get_gain() {
    /*
    DESCRIPTION:
        retrieve currntly set gain from the registry
    RETURN:
        currently set gain value
    */
    unsigned char buf = read_register(REG_MODE2);
    buf = (buf & 0b01110000) >> 4;                      // get the binary of actual gain
    return (ADC_GAIN)buf;
}

unsigned char ADS1263::set_data_rate(ADC_DRATE new_drate) {
    /*  Set the data rate for ADC1 according to the ADC_DRATE enum
        The data rate sits in register REG_MODE2 in 4 least significant bits

        REG_MODE2 [BYPASS][3 bits gain][4 bits DRATE]
                                        ^^^^^^^^^^^^

        return 1 on success
        return 0 on fail
    */

    if (new_drate == get_data_rate()) {     // the currently set data rate is the same as requested -> nothing to do
        return;
    }

    unsigned char buf = read_register(REG_MODE2);           // reads current REG_MODE2
    buf = (buf & 0b11110000) | (unsigned char)new_drate;    // override DRATE bits

    if(debug) {                                             // DEBUG message
        cout << "set_data_rate" << endl;
        cout << "new_reg_value: " << bitset<8>(buf) << endl;
    }

    //
    if(write_register(REG_MODE2, buf)) {                // Push to the register
       drate = new_drate;
        return 1;                                       // The register writing has been successfull
    } else {                                            // The writing to the register has failed
        unsigned char reg = read_register(REG_MODE2);   // Actual register value
        cout << "WARNING: set_data_rate(): The data rate for ADC1 has not been set correctly" << endl;
        cout << "WARNING: Current REG_MDOE2: " << bitset<8>(reg) << " [BYPASS][3 bits GAIN][4 bits DRATE]" << endl;
        cout << "WARNING: Expected REG_MODE2: " << bitset<8>(buf) << " [BYPASS][3 bits GAIN][4 bits DRATE]" << endl;
        return 0;
    }
}

ADC_DRATE ADS1263::get_data_rate() {
    /*
    DESCRIPTION:
        retrieve currntly set data rate from the registry
    RETURN:
        currently set data rate value
    */
    unsigned char buf = read_register(REG_MODE2);
    buf = (buf & 0b00001111);                      // get the binary of actual data rate
    return (ADC_DRATE)buf;
}

// #################################################################################################
// ######################################### UTILITY ###########################################
// #################################################################################################

void ADS1263::close() {
    // Stop any continous data transfer (propably unnecessary)
    digitalWrite(CS_PIN, LOW);
    SPI_write(CMD_STOP1);
    SPI_write(CMD_STOP2);
    digitalWrite(CS_PIN, HIGH);

    // enter shutdown mode
    digitalWrite(RST_PIN, LOW);

    wiringPiSPIClose(SPI_CHANNEL);      // close the SPI channel
    cout << "MESSAGE: ADC has been shut down!" << endl;
}

void ADS1263::reset() {
    // reset the ADC, this function will also awaken the ADC from power down mode
    digitalWrite(RST_PIN, HIGH);
    sleep(10);
    digitalWrite(RST_PIN, LOW);
    sleep(1);
    digitalWrite(RST_PIN, HIGH);
    sleep(10);
}

void ADS1263::set_debug(bool state) {
    /* change the internal debug flag
        true - display additional debug messages
        false - do not display additional debug messages
    */
    debug = state;
}







unsigned char ADS1263::read_register(ADC_REG reg) {
    /* 
    DESCRIPTION:
        Reads the value of a register
        to read the register 2 opcodes has to be sent 001r rrrr byte has to be sent tyhrough the SPI
        where:
            0b 001r rrrr    - is the Read register command
            r rrrr          - is the register address
    ARGUMENTS:
        ADC_REG reg - address of the register to read
    RETURN:
        single byte - regster value
    */

    unsigned char buf = 0;

    // combine CMD_RREG with the requested registr address
    unsigned char command = (unsigned char)CMD_RREG | (unsigned char)reg;   

    digitalWrite(CS_PIN, LOW);  // CS_PIN has to be low for SPI communication
    SPI_write(command);         // CMD_RREG 001r rrrr
    SPI_write(CMD_NOP);         // empty byte -> read only one register
    buf = SPI_read();           // the response - contents of the register
    digitalWrite(CS_PIN, HIGH); // Reset CS_PIN back to HIGH (stop SPI communication)

    if(debug) {                 // DEBUG
        cout << "#### read_register() ####" << endl;
        cout << "COMMAND: " << bitset<8>(command) << endl;
        cout << "Current reg value: " << bitset<8>(buf) << endl;
    }

    return buf;
}


unsigned char ADS1263::write_register(ADC_REG reg, unsigned char val) {
    /*
    DESCRIPTION:
        overwrite single register        
        to overwrit the register 010r rrrr byte has to be sent tyhrough the SPI
        where:
            0b 010r rrrr    - is the wirte register command
            r rrrr          - is the register address
    
    ARGUMENTS:
        ADC_REF reg - register to be overwritten
        unsigned char val - what to overwritte the register with (1 byte)

    RETURN:
        return 0 on error
        return 1 on success
    */

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
        return 0;
    }

    return 1;
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


