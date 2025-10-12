#ifndef LOADCELL_H_
#define LOADCELL_H_

#include "ADS1263_wrapper.h"


class Loadcell {
    public:
        Loadcell(uint8_t ch);
        void set_a(double a_new);
        void set_b(double b_new);
        double tare();
        void calibrate(double actual_reading, double return_coeffs[2]);
        double read();
    
    private:
        uint8_t channel;
        double a;
        double b;

};

#endif