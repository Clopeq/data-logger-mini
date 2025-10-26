#pragma once

#include "ADC_structures.h"


unsigned char ADC_read(unsigned char channel);
void ADC_reset();
void ADC_init();
void ADC_close();


class ADS1263 {
public:
    ADS1263(int datarate);
    ~ADS1263();
    void reset();
    void close();
    long double read();
    void set_debug(bool state);
    void set_data_rate(ADC_DRATE drate);
    void set_gain(ADC_GAIN gain);
    unsigned char read_register(ADC_REG reg);
    unsigned char write_register(ADC_REG reg, unsigned char value);
    void change_mode(ADC_RUNMODE mode);
    double read(unsigned char channel);

private:
    unsigned char SPI_write(unsigned char value);
    unsigned char SPI_read();

    long double a;
    long double b;
    int spi_rate;
    double ref;
    bool debug;
};
