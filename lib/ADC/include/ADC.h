#pragma once

#include "ADC_structures.h"
#include "ADC_port_manager.h"


unsigned char ADC_read(unsigned char channel);
void ADC_reset();
void ADC_init();
void ADC_close();


class ADS1263 {
public:
    ADS1263(int datarate);
    ~ADS1263();
    
    // general use
    double read(PortManager port);
    double read_continous(unsigned char channel);
    double read_all(unsigned char channel_list[]);
    double read_all_continous(unsigned char channel_list[]);

    // configuration (user exposed registry manipulation)
    void change_mode(ADC_RUNMODE mode);
    unsigned char set_gain(ADC_GAIN gain);
    ADC_GAIN get_gain();
    unsigned char set_data_rate(ADC_DRATE drate);
    ADC_DRATE get_data_rate();

    // utility
    unsigned char read_register(ADC_REG reg);                       // public for in field hacking
    unsigned char write_register(ADC_REG reg, unsigned char value); // public for in field hacking
    void set_debug(bool state);                                     // public for in field hacking
    void reset();                                                   // public for in field hacking
    void reload();                                                  // public for in field hacking (reload config from file)

private:
    // utilities
    unsigned char load_config();
    void close();    
    
    // SPI communication
    unsigned char SPI_write(unsigned char value);
    unsigned char SPI_read();

    // port managment
    unsigned char set_channel_positive(CHANNEL channel);
    unsigned char set_channel_negative(CHANNEL channel);
    CHANNEL get_channel_positive();
    CHANNEL get_channel_negative();

    // attributes
    long double a;
    long double b;
    int spi_rate;
    double vref;
    ADC_GAIN gain;
    ADC_DRATE drate;
    bool debug;
    CHANNEL current_channel_positive;
    CHANNEL current_channel_negative;

};


