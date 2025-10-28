#include <iostream>
#include "ADC_port_manager.h"

using namespace std;

PortManager::PortManager(CHANNEL ch_positive, CHANNEL ch_negative, double tare, double calibrate) {
    positive = ch_positive;
    negative = ch_negative;
    tare_factor = tare;
    cal_factor = calibrate;
}

PortManager::~PortManager() {
    int i=0; // do nothing
}

unsigned char PortManager::set_channel(CHANNEL ch_positive, CHANNEL ch_negative) {
    /*
    DESCRIPTION:
        set the positive and negative channels for the port tied to this object. Does not affect ADC's registers
    ARGUMENTS:
        ch_positive - positive channel
        ch_negative - negative channel (COMM for single ended measurement)
    RETURN:
        always 0
    */
    //                                                      TODO: Provide checks for correctnes of input arguments
    positive = ch_positive;
    negative = ch_negative;
    return 0;
}

double PortManager::tare(double old_measurement, double new_measurement) {
    /*
    DESCRIPTION:
        Linear function used: y = a(x-b), where:
        y - meaningful value (e.g. Newtons)
        a - calibration factor
        x - raw value in volts
        b - tare factor         <- this function calculates new value for this parameter

        assume:
        > 1 - old measurement (before tare)
        > 2 - new measurement (after tare)
        
        this yields a set of linear equations:
        pre tare equation   -> y1 = a(x - b1) -> x = y1/a + b1
        post tare equation  -> y2 = a(x - b2) -> y2 = a(y1/a + b1 - b2) -> b2 = (y1-y2)/a + b1 
        where b2 is the new tare factor this function is trying to find and x is not directly knonw since the abstraction layer in ADS1263 class only returns y1. a and b1 are the old (before tare) attributes of this class (PortManager)

    ARGUMENTS:
        old_measurement - ADC.read before tare
        new_measurement - ADC.read after tare

    RETURN:
        new tare factor
    */

    tare_factor = (old_measurement-new_measurement)/cal_factor + tare_factor;
    return tare_factor;
}

double PortManager::calibrate(double old_measurement, double new_measurement) {
    /*
    DESCRIPTION:
        Linear function used: y = a(x-b), where:
        y - meaningful value (e.g. Newtons)
        a - calibration factor      <- this function calculates new value for this parameter
        x - raw value in volts
        b - tare factor

    ARGUMENTS:
        old_measurement - ADC.read before calibration
        new_measurement - ADC.read after calibration

    RETURN:
        new calibration factor

    */
    if(new_measurement == 0) {
        cout << "WARNING: PortManager::calibrate(): calibration factor cannot be 0" << endl;
        return -1;
    }

    cal_factor = new_measurement/old_measurement * cal_factor;
    return cal_factor;
}

// ####################################################################################################
// ################################### GETTERS &  SETTERS #############################################
// ####################################################################################################

CHANNEL PortManager::get_positive_channel() {
    return positive;
}

CHANNEL PortManager::get_negative_channel() {
    return negative;
}

double PortManager::get_tare_factor() {
    return tare_factor;
}

double PortManager::get_cal_factor() {
    return cal_factor;
}