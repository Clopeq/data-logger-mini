#include "ADC.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

ADC::ADC() {
    spi_fd = open("/dev/spidev0.0", O_RDWR);
    if (spi_fd < 0) return;  // fail silently (or you can print error)

    unsigned char mode = SPI_MODE_1;
    unsigned int speed = 1000000; // 1 MHz

    ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
}

ADC::~ADC() {
    if (spi_fd >= 0)
        close(spi_fd);
}

void ADC::spi_transfer(unsigned char tx[3], unsigned char rx[3]) {
    struct spi_ioc_transfer tr = {};
    tr.tx_buf = (unsigned long)tx;
    tr.rx_buf = (unsigned long)rx;
    tr.len = 3;
    tr.speed_hz = 1000000;
    tr.bits_per_word = 8;
    tr.delay_usecs = 0;

    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
}

unsigned char ADC::read_register(unsigned char reg_addr) {
    unsigned char tx[3] = { static_cast<unsigned char>(0x20 | (reg_addr & 0x1F)), 0x00, 0x00 };
    unsigned char rx[3] = {0};

    spi_transfer(tx, rx);

    return rx[2];  // third byte contains the register value
}
