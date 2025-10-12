#ifndef LOADCELL_H_
#define LOADCELL_H_

#include "ADS1263_wrapper.h"


class Loadcell {
    public:
        Loadcell(int ch);
        void set_a(double a_new);
        void set_b(double b_new);
        double tare();
        void calibrate(double actual_reading, double return_coeffs[2]);
        double read();
    
    private:
        int channel;
        double a;
        double b;

};

#endif