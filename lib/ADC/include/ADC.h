#pragma once

#include <cstdint>

class ADC {
public:
    ADC();                     // Constructor: initialize SPI
    ~ADC();                    // Destructor: close SPI
    uint8_t read_register(uint8_t reg_addr); // Read single register
private:
    int spi_fd;                // File descriptor for /dev/spidev0.0
    void spi_transfer(uint8_t* tx, uint8_t* rx, size_t len);
};
