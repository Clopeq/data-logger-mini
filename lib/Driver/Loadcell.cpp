
#include "Loadcell.h"

int tare(int channel) {

    float b = ADC_read(channel);

    return b;
}