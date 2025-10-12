#ifndef ADS1263_WRAPPER_H_
#define ADSA1263_WRAAPPER_H_

#include "ADS1263.h"

#define REF 5.08


UBYTE ADC_init(ADS1263_DRATE rate);
UBYTE ADC2_init(ADS1263_ADC2_DRATE rate);
void ADC_setmode(UBYTE Mode);
double ADC_read(char Channel);
// void ADS1263_GetAll(UBYTE *List, UDOUBLE *Value, int Number);
// void ADS1263_GetAll_ADC2(UDOUBLE *ADC_Value);
// UDOUBLE ADS1263_RTD(ADS1263_DELAY delay, ADS1263_GAIN gain, ADS1263_DRATE drate);
// void ADS1263_DAC(ADS1263_DAC_VOLT volt, UBYTE isPositive, UBYTE isClose);


#endif