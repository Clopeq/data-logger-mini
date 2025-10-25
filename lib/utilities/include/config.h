#pragma once

#define DEBUG true          // If true additional messages will be printed to the command line

#define RST_PIN 18          // Reset pin
#define CS_PIN 22           // Chip select, needs to be low for SPI communication
#define DRDY_PIN 17         // Data ready, low when data is ready to read from ADC, use with interrupts
#define SPI_CHANNEL 0       // Raspberry pi SPI channel to which ADC is connected
#define SPI_RATE 500000     // clock speed for SPI communication, use < 1MHz for register read/write, otherwise up to 8 MHz is allowable