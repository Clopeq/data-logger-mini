#ifndef LOADCELL_H_
#define LOADCELL_H_

#include "ADS1263_wrapper.h"
#include "../nlohmann/json.hpp"

/* TODO
    store and load data to a file outside somwhere where it will not be updated by git pull
*/

class Loadcell {
    public:
        Loadcell(short int ch);
        void set_a(double a_new);
        void set_b(double b_new);
        double tare();
        void calibrate(double actual_reading, double return_coeffs[2]);
        double read();
    
    private:
        short int channel;
        double a;
        double b;
};

#endif