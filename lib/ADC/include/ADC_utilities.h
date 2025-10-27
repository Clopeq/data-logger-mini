#pragma once

#include <string>
#include "ADC_structures.h"

using namespace std;

#include <string>
using namespace std;

// ---------- ADC_GAIN ----------
string ADC_GAIN_tostr(ADC_GAIN gain) {
    switch (gain) {
        case GAIN_1:    return "GAIN_1";
        case GAIN_2:    return "GAIN_2";
        case GAIN_4:    return "GAIN_4";
        case GAIN_8:    return "GAIN_8";
        case GAIN_16:   return "GAIN_16";
        case GAIN_32:   return "GAIN_32";
        case GAIN_64:   return "GAIN_64";
        case GAIN_128:  return "GAIN_128";
        default:        return "UNKNOWN_GAIN";
    }
}

// ---------- ADC_DRATE ----------
string ADC_DRATE_tostr(ADC_DRATE rate) {
    switch (rate) {
        case SPS_2d5:   return "SPS_2d5";
        case SPS_5:     return "SPS_5";
        case SPS_10:    return "SPS_10";
        case SPS_16d6:  return "SPS_16d6";
        case SPS_20:    return "SPS_20";
        case SPS_50:    return "SPS_50";
        case SPS_60:    return "SPS_60";
        case SPS_100:   return "SPS_100";
        case SPS_400:   return "SPS_400";
        case SPS_1200:  return "SPS_1200";
        case SPS_2400:  return "SPS_2400";
        case SPS_4800:  return "SPS_4800";
        case SPS_7200:  return "SPS_7200";
        case SPS_14400: return "SPS_14400";
        case SPS_19200: return "SPS_19200";
        case SPS_38400: return "SPS_38400";
        default:        return "UNKNOWN_DRATE";
    }
}

// ---------- ADC2_DRATE ----------
string ADC2_DRATE_tostr(ADC2_DRATE rate) {
    switch (rate) {
        case SPS2_10:   return "SPS2_10";
        case SPS2_100:  return "SPS2_100";
        case SPS2_400:  return "SPS2_400";
        case SPS2_800:  return "SPS2_800";
        default:        return "UNKNOWN_ADC2_DRATE";
    }
}

// ---------- ADC_CMD ----------
string ADC_CMD_tostr(ADC_CMD cmd) {
    switch (cmd) {
        case CMD_NOP:    return "CMD_NOP";
        case CMD_RESET:  return "CMD_RESET";
        case CMD_START1: return "CMD_START1";
        case CMD_STOP1:  return "CMD_STOP1";
        case CMD_START2: return "CMD_START2";
        case CMD_STOP2:  return "CMD_STOP2";
        case CMD_RDATA1: return "CMD_RDATA1";
        case CMD_RDATA2: return "CMD_RDATA2";
        case CMD_SYOCAL1:return "CMD_SYOCAL1";
        case CMD_SYGCAL1:return "CMD_SYGCAL1";
        case CMD_SFOCAL1:return "CMD_SFOCAL1";
        case CMD_SYOCAL2:return "CMD_SYOCAL2";
        case CMD_SYGCAL2:return "CMD_SYGCAL2";
        case CMD_SFOCAL2:return "CMD_SFOCAL2";
        case CMD_RREG:   return "CMD_RREG";
        case CMD_WREG:   return "CMD_WREG";
        default:         return "UNKNOWN_CMD";
    }
}

// ---------- ADC_REG ----------
string ADC_REG_tostr(ADC_REG reg) {
    switch (reg) {
        case REG_ID:         return "REG_ID";
        case REG_POWER:      return "REG_POWER";
        case REG_INTERFACE:  return "REG_INTERFACE";
        case REG_MODE0:      return "REG_MODE0";
        case REG_MODE1:      return "REG_MODE1";
        case REG_MODE2:      return "REG_MODE2";
        case REG_INPMUX:     return "REG_INPMUX";
        case REG_OFCAL0:     return "REG_OFCAL0";
        case REG_OFCAL1:     return "REG_OFCAL1";
        case REG_OFCAL2:     return "REG_OFCAL2";
        case REG_FSCAL0:     return "REG_FSCAL0";
        case REG_FSCAL1:     return "REG_FSCAL1";
        case REG_FSCAL2:     return "REG_FSCAL2";
        case REG_IDACMUX:    return "REG_IDACMUX";
        case REG_IDACMAG:    return "REG_IDACMAG";
        case REG_REFMUX:     return "REG_REFMUX";
        case REG_TDACP:      return "REG_TDACP";
        case REG_TDACN:      return "REG_TDACN";
        case REG_GPIOCON:    return "REG_GPIOCON";
        case REG_GPIODIR:    return "REG_GPIODIR";
        case REG_GPIODAT:    return "REG_GPIODAT";
        case REG_ADC2CFG:    return "REG_ADC2CFG";
        case REG_ADC2MUX:    return "REG_ADC2MUX";
        case REG_ADC2OFC0:   return "REG_ADC2OFC0";
        case REG_ADC2OFC1:   return "REG_ADC2OFC1";
        case REG_ADC2FSC0:   return "REG_ADC2FSC0";
        case REG_ADC2FSC1:   return "REG_ADC2FSC1";
        default:             return "UNKNOWN_REG";
    }
}

// ---------- ADC_RUNMODE ----------
string ADC_RUNMODE_tostr(ADC_RUNMODE mode) {
    switch (mode) {
        case CONTINOUS: return "CONTINOUS";
        case PULSE:     return "PULSE";
        default:        return "UNKNOWN_RUNMODE";
    }
}

// ---------- ADC_DELAY ----------
string ADC_DELAY_tostr(ADC_DELAY delay) {
    switch (delay) {
        case DELAY_0s:     return "DELAY_0s";
        case DELAY_8d7us:  return "DELAY_8d7us";
        case DELAY_17us:   return "DELAY_17us";
        case DELAY_35us:   return "DELAY_35us";
        case DELAY_169us:  return "DELAY_169us";
        case DELAY_139us:  return "DELAY_139us";
        case DELAY_278us:  return "DELAY_278us";
        case DELAY_555us:  return "DELAY_555us";
        case DELAY_1d1ms:  return "DELAY_1d1ms";
        case DELAY_2d2ms:  return "DELAY_2d2ms";
        case DELAY_4d4ms:  return "DELAY_4d4ms";
        case DELAY_8d8ms:  return "DELAY_8d8ms";
        default:           return "UNKNOWN_DELAY";
    }
}

// ---------- DAC_VOLT ----------
string DAC_VOLT_tostr(DAC_VOLT volt) {
    switch (volt) {
        case DAC_4V5:        return "DAC_4V5";
        case DAC_3V5:        return "DAC_3V5";
        case DAC_3V0:        return "DAC_3V0";
        case DAC_2V75:       return "DAC_2V75";
        case DAC_2V625:      return "DAC_2V625";
        case DAC_2V5625:     return "DAC_2V5625";
        case DAC_2V53125:    return "DAC_2V53125";
        case DAC_2V515625:   return "DAC_2V515625";
        case DAC_2V5078125:  return "DAC_2V5078125";
        case DAC_2V5:        return "DAC_2V5";
        case DAC_2V4921875:  return "DAC_2V4921875";
        case DAC_2V484375:   return "DAC_2V484375";
        case DAC_2V46875:    return "DAC_2V46875";
        case DAC_2V4375:     return "DAC_2V4375";
        case DAC_2V375:      return "DAC_2V375";
        case DAC_2V25:       return "DAC_2V25";
        case DAC_2V0:        return "DAC_2V0";
        case DAC_1V5:        return "DAC_1V5";
        case DAC_0V5:        return "DAC_0V5";
        default:             return "UNKNOWN_DAC_VOLT";
    }
}

// ---------- PORT ----------
string PORT_tostr(PORT port) {
    switch (port) {
        case A0:        return "A0";
        case A1:        return "A1";
        case A2:        return "A2";
        case A3:        return "A3";
        case A4:        return "A4";
        case A5:        return "A5";
        case A6:        return "A6";
        case A7:        return "A7";
        case A8:        return "A8";
        case A9:        return "A9";
        case COMM:      return "COMM";
        case TEMP:      return "TEMP";
        case V_ANALOG:  return "V_ANALOG";
        case V_DIGITAL: return "V_DIGITAL";
        case TDAC:      return "TDAC";
        case FLOAT:     return "FLOAT";
        default:        return "UNKNOWN_PORT";
    }
}


