#include "ADC.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <cstring>
#include <stdexcept>
#include <cstddef>

ADC::ADC() {
    const char* device = "/dev/spidev0.0";
    spi_fd = open(device, O_RDWR);
    if (spi_fd < 0)
        throw std::runtime_error("Failed to open SPI device");

    uint8_t mode = SPI_MODE_1;
    uint32_t speed = 1000000; // 1 MHz
    if (ioctl(spi_fd, SPI_IOC_WR_MODE, &mode) < 0)
        throw std::runtime_error("Can't set SPI mode");
    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
        throw std::runtime_error("Can't set SPI speed");
}

ADC::~ADC() {
    if (spi_fd >= 0)
        close(spi_fd);
}

void ADC::spi_transfer(uint8_t* tx, uint8_t* rx, std::size_t len) {
    struct spi_ioc_transfer tr{};
    tr.tx_buf = (unsigned long)tx;
    tr.rx_buf = (unsigned long)rx;
    tr.len = len;
    tr.speed_hz = 1000000;
    tr.bits_per_word = 8;
    tr.delay_usecs = 0;

    if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr) < 1)
        throw std::runtime_error("SPI transfer failed");
}

uint8_t ADC::read_register(uint8_t reg_addr) {
    // Build command: RREG = 0x20 | (reg & 0x1F), read 1 register
    uint8_t tx[] = { static_cast<uint8_t>(0x20 | (reg_addr & 0x1F)), 0x00, 0x00 };
    uint8_t rx[sizeof(tx)] = {0};
    spi_transfer(tx, rx, sizeof(tx));
    return rx[2]; // Third byte contains the register value
}
