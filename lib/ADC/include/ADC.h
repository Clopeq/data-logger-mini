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
    // general use
    double read(unsigned char channel);
    double read_continous(unsigned char channel);
    double read_all(unsigned char channel_list[]);
    double read_all_continous(unsigned char channel_list[]);

    // configuration
    void change_mode(ADC_RUNMODE mode);
    void set_gain(ADC_GAIN gain);
    void set_data_rate(ADC_DRATE drate);

    // utility
    unsigned char read_register(ADC_REG reg);
    unsigned char write_register(ADC_REG reg, unsigned char value);
    unsigned char set_channel(unsigned int channel);
    void set_debug(bool state);
    void reset();
    void close();

private:
    unsigned char SPI_write(unsigned char value);
    unsigned char SPI_read();

    long double a;
    long double b;
    int spi_rate;
    double ref;
    bool debug;
};
