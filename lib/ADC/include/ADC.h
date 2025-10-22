#pragma once

class ADC {
public:
    ADC();
    ~ADC();

    // Read a register from ADS1263
    unsigned char read_register(unsigned char reg_addr);

private:
    int spi_fd;  // file descriptor for /dev/spidev0.0

    // Perform SPI transfer (3 bytes)
    void spi_transfer(unsigned char tx[3], unsigned char rx[3]);
};
