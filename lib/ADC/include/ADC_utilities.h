#pragma once

#include <string>
#include "ADC_structures.h"

using namespace std;

#include <string>
using namespace std;

// ---------- ADC_GAIN ----------
string ADC_GAIN_tostr(ADC_GAIN gain);
int ADC_GAIN_toint(ADC_GAIN gain);

string ADC_DRATE_tostr(ADC_DRATE rate);

string ADC2_DRATE_tostr(ADC2_DRATE rate);

string ADC_CMD_tostr(ADC_CMD cmd);

string ADC_REG_tostr(ADC_REG reg);

string ADC_RUNMODE_tostr(ADC_RUNMODE mode);

string ADC_DELAY_tostr(ADC_DELAY delay);

string DAC_VOLT_tostr(DAC_VOLT volt);

string CHANNEL_tostr(CHANNEL channel);


