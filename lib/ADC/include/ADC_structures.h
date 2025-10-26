#pragma once


// REG_MODE2 [BYPASS][3 bits GAIN][4 bits DRATE]
typedef enum
{
    GAIN_1   = 0b000,  // 0
    GAIN_2   = 0b001,  // 1
    GAIN_4   = 0b010,  // 2
    GAIN_8   = 0b011,  // 3
    GAIN_16  = 0b100,  // 4
    GAIN_32  = 0b101,  // 5
    GAIN_64  = 0b110,  // 6 - ADC2 ONLY!
    GAIN_128 = 0b111,  // 7 - ADC2 ONLY!
} ADC_GAIN;

typedef enum
{
    SPS_2d5   = 0b0000,  // 0
    SPS_5     = 0b0001,  // 1
    SPS_10    = 0b0010,  // 2
    SPS_16d6  = 0b0011,  // 3
    SPS_20    = 0b0100,  // 4
    SPS_50    = 0b0101,  // 5
    SPS_60    = 0b0110,  // 6
    SPS_100   = 0b0111,  // 7
    SPS_400   = 0b1000,  // 8
    SPS_1200  = 0b1001,  // 9
    SPS_2400  = 0b1010,  // 10
    SPS_4800  = 0b1011,  // 11
    SPS_7200  = 0b1100,  // 12
    SPS_14400 = 0b1101,  // 13
    SPS_19200 = 0b1110,  // 14
    SPS_38400 = 0b1111   // 15
} ADC_DRATE;

typedef enum { // REG_ADC2CFG structure [2 bits DATARATE][3 bits REF2][3 bits GAIN]
    SPS2_10  = 0b00,    // 0
    SPS2_100 = 0b01,    // 1
    SPS2_400 = 0b10,    // 2
    SPS2_800 = 0b11,    // 3
} ADC2_DRATE;

// List of all ADC commands
typedef enum
{
    CMD_NOP    = 0x00, // dummy byte, 0000 0000 (00h)
    CMD_RESET   = 0x06, // Reset the ADC, 0000 011x (06h or 07h)
    CMD_START1  = 0x08, // Start ADC1 conversions, 0000 100x (08h or 09h)
    CMD_STOP1   = 0x0A, // Stop ADC1 conversions, 0000 101x (0Ah or 0Bh)
    CMD_START2  = 0x0C, // Start ADC2 conversions, 0000 110x (0Ch or 0Dh)
    CMD_STOP2   = 0x0E, // Stop ADC2 conversions, 0000 111x (0Eh or 0Fh)
    CMD_RDATA1  = 0x12, // Read ADC1 data, 0001 001x (12h or 13h)
    CMD_RDATA2  = 0x14, // Read ADC2 data, 0001 010x (14h or 15h)
    CMD_SYOCAL1 = 0x16, // ADC1 system offset calibration, 0001 0110 (16h)
    CMD_SYGCAL1 = 0x17, // ADC1 system gain calibration, 0001 0111 (17h)
    CMD_SFOCAL1 = 0x19, // ADC1 self offset calibration, 0001 1001 (19h)
    CMD_SYOCAL2 = 0x1B, // ADC2 system offset calibration, 0001 1011 (1Bh)
    CMD_SYGCAL2 = 0x1C, // ADC2 system gain calibration, 0001 1100 (1Ch)
    CMD_SFOCAL2 = 0x1E, // ADC2 self offset calibration, 0001 1110 (1Eh)
    CMD_RREG    = 0x20, // Read registers 001r rrrr (20h+000r rrrr)
    CMD_WREG    = 0x40, // Write registers 010r rrrr (40h+000r rrrr)
} ADC_CMD;


// list of all ADC registers
typedef enum
{
    REG_ID         = 0x00,  // Device ID (xxh)
    REG_POWER      = 0x01,  // Power (11h)
    REG_INTERFACE  = 0x02,  // Interface (05h)
    REG_MODE0      = 0x03,  // Mode0 (00h)
    REG_MODE1      = 0x04,  // Mode1 (80h)
    REG_MODE2      = 0x05,  // Mode2 (04h)
    REG_INPMUX     = 0x06,  // Input Multiplexer (01h)
    REG_OFCAL0     = 0x07,  // Offset Calibration 0 (00h)
    REG_OFCAL1     = 0x08,  // Offset Calibration 1 (00h)
    REG_OFCAL2     = 0x09,  // Offset Calibration 2 (00h)
    REG_FSCAL0     = 0x0A,  // Full-Scale Calibration 0 (00h)
    REG_FSCAL1     = 0x0B,  // Full-Scale Calibration 1 (00h)
    REG_FSCAL2     = 0x0C,  // Full-Scale Calibration 2 (40h)
    REG_IDACMUX    = 0x0D,  // IDAC Multiplexer (BBh)
    REG_IDACMAG    = 0x0E,  // IDAC Magnitude (00h)
    REG_REFMUX     = 0x0F,  // Reference Multiplexer (00h)
    REG_TDACP      = 0x10,  // Test DAC Positive (00h)
    REG_TDACN      = 0x11,  // Test DAC Negative (00h)
    REG_GPIOCON    = 0x12,  // GPIO Configuration (00h)
    REG_GPIODIR    = 0x13,  // GPIO Direction (00h)
    REG_GPIODAT    = 0x14,  // GPIO Data (00h)
    REG_ADC2CFG    = 0x15,  // ADC2 Configuration (00h)
    REG_ADC2MUX    = 0x16,  // ADC2 Input Multiplexer (01h)
    REG_ADC2OFC0   = 0x17,  // ADC2 Offset Calibration 0 (00h)
    REG_ADC2OFC1   = 0x18,  // ADC2 Offset Calibration 1 (00h)
    REG_ADC2FSC0   = 0x19,  // ADC2 Full-Scale Calibration 0 (00h)
    REG_ADC2FSC1   = 0x1A   // ADC2 Full-Scale Calibration 1 (40h)
} ADC_REG;

typedef enum {  // REG_MODE0 bit 6
    CONTINOUS = 0,
    PULSE = 1
} ADC_RUNMODE;

typedef enum
{
    DELAY_0s    = 0,
    DELAY_8d7us,
    DELAY_17us,
    DELAY_35us,
    DELAY_169us,
    DELAY_139us,
    DELAY_278us,
    DELAY_555us,
    DELAY_1d1ms,
    DELAY_2d2ms,
    DELAY_4d4ms,
    DELAY_8d8ms,
}ADC_DELAY;



typedef enum
{
    DAC_4V5        = 0b01001,      //4.5V
    DAC_3V5        = 0b01000,
    DAC_3V0          = 0b00111,
    DAC_2V75       = 0b00110,
    DAC_2V625      = 0b00101,
    DAC_2V5625     = 0b00100,
    DAC_2V53125    = 0b00011,
    DAC_2V515625   = 0b00010,
    DAC_2V5078125  = 0b00001,
    DAC_2V5        = 0b00000,
    DAC_2V4921875  = 0b10001,
    DAC_2V484375   = 0b10010,
    DAC_2V46875    = 0b10011,
    DAC_2V4375     = 0b10100,
    DAC_2V375      = 0b10101,
    DAC_2V25       = 0b10110,
    DAC_2V0          = 0b10111,
    DAC_1V5        = 0b11000,
    DAC_0V5        = 0b11001,
}DAC_VOLT;