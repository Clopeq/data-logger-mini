
#include "ADS1263_wrapper.h"

UBYTE ADC_init(ADS1263_DRATE rate) {
    return ADS1263_init_ADC1(rate);
}

UBYTE ADC2_init(ADS1263_ADC2_DRATE rate){
    return ADS1263_init_ADC2(rate);
}
void ADC_setmode(UBYTE Mode) {
    ADS1263_SetMode(Mode);
}
double ADC_read(int Channel) {
    UDOUBLE value = ADS1263_GetChannalValue((UBYTE)Channel);
    if((value>>31) == 1)
         value = -1.0 * (REF*2.0 - value/2147483648.0 * REF);      //7fffffff + 1
    else
         value = value/2147483647.0 * REF;       //7fffffff
    return (double)value;
}