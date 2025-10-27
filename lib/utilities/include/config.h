#pragma once


// GLOBAL Flags
#define DEBUG false          // If true additional messages will be printed to the command line
#define VREF 5.08           // default ADC voltage reference

// Raspberry pinout
#define RST_PIN 18          // Reset pin
#define CS_PIN 22           // Chip select, needs to be low for SPI communication
#define DRDY_PIN 17         // Data ready, low when data is ready to read from ADC, use with interrupts
#define MOSI_PIN 10         // ADS1263 SPI
#define MISO_PIN 9          // ADS1263 SPI
#define SCLK_PIN 11         // ADS1263 SPI
#define D0_PIN 6            // ADS1263 digits input signal (?)
#define D1_PIN 13           // ADS1263 digits input signal (?)
#define D2_PIN 19           // ADS1263 digits input signal (?)
#define D3_PIN 26           // ADS1263 digits input signal (?)

#define SPI_CHANNEL 0       // Raspberry pi SPI channel to which ADC is connected
#define SPI_RATE 500000     // clock speed for SPI communication, use < 1MHz for register read/write, otherwise up to 8 MHz is allowable