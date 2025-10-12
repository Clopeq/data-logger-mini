
#include "Loadcell.h"


Loadcell::Loadcell(uint8_t set_channel) {
    channel = set_channel;
    a = 1;
    b = 0;
}

void Loadcell::set_a(double a_new) {
    a = a_new;
}

void Loadcell::set_b(double b_new) {
    b = b_new;
}

double Loadcell::tare() {
    b = -a * ADC_read(channel);
    return b;
}

void Loadcell::calibrate(double actual_reading, double return_coeffs[2]) {
    double raw_measurement = ADC_read(channel);
    a = actual_reading/(raw_measurement + b);
    b = a * b;

    return_coeffs[0] = a;
    return_coeffs[1] = b;
}

double Loadcell::read() {
    return a * ADC_read(channel) + b;
}