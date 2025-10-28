#pragma once

#include "ADC_structures.h"
#include <string>

using namespace std;

class PortManager {
public:                                 // ch_negative = COMM for single ended measurement
    PortManager(CHANNEL ch_positive, CHANNEL ch_negative, double tare = 0, double calibrate = 1);
    ~PortManager();
    unsigned char set_channel(CHANNEL ch_positive, CHANNEL ch_negative = COMM);
    double tare(double current_measurement, double tare_value = 0);
    double calibrate(double old_measurement, double new_measurement = 1); // actual_measurement = 1 -> measure voltage
    CHANNEL get_positive_channel();
    CHANNEL get_negative_channel();
    double get_tare_factor();
    double get_cal_factor();


private:
    CHANNEL positive;
    CHANNEL negative;
    double tare_factor;
    double cal_factor;
    string unit;
    string name;
};