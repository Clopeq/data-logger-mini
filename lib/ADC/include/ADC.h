#pragma once

#include <cstdint>
#include <cstddef>   // size_t is std::size_t

class ADC {
public:
    ADC();                     
    ~ADC();                    

    uint8_t read_register(uint8_t reg_addr);

private:
    int spi_fd;                
    void spi_transfer(uint8_t* tx, uint8_t* rx, std::size_t len); // use std::size_t
};