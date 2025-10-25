// ADC.cpp
#include "ADC.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

static int spi_fd = -1; // internal global

const float VREF = 5.08;    // ADS1263 reference voltage
const int GAIN = 1;         // PGA gain

void ADC_init() {
    spi_fd = open("/dev/spidev0.0", O_RDWR);
    unsigned char mode = SPI_MODE_1;
    unsigned int speed = 1000000;
    ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
}

void ADC_close() {
    if (spi_fd >= 0) close(spi_fd);
}

unsigned char ADC_read_register(unsigned char reg_addr) {
    unsigned char tx[3] = { static_cast<unsigned char>(0x20 | (reg_addr & 0x1F)), 0x00, 0x00 };
    unsigned char rx[3] = {0};
    struct spi_ioc_transfer tr{};
    tr.tx_buf = (unsigned long)tx;
    tr.rx_buf = (unsigned long)rx;
    tr.len = 3;
    tr.speed_hz = 1000000;
    tr.bits_per_word = 8;
    tr.delay_usecs = 0;
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
    return rx[2];
}