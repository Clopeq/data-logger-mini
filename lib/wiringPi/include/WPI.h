#pragma once

#include <iostream>

using namespace std;

#if defined(__has_include)
    #if __has_include(<wiringPi.h>)
        #include <wiringPi.h>
        #include <wiringPiSPI.h>
    #else
        // wiringPi header not available for IntelliSense/host build — provide minimal stubs
        // so the editor doesn't flag missing include while the code still compiles on Raspberry Pi.

        enum WPIPinType {
            WPI_PIN_BCM,
            WPI_PIN_WPI,
            WPI_PIN_PHYS
        };

        enum WPIPinMode {
            OUTPUT,
            INPUT,
        };

        enum WPIPinValue {
            HIGH = 1,
            LOW = 0
        };

        struct WPIWfiStatus {
            int statusOK;               // -1: error (return of 'poll' command), 0: timeout, 1: irq processed, next data values are valid if needed
            unsigned int pinBCM;        // gpio as BCM pin
            int edge;                   // INT_EDGE_FALLING or INT_EDGE_RISING
            long long int timeStamp_us; // time stamp in microseconds
        };

        enum {
            INT_EDGE_RISING,
            INT_EDGE_FALLING,
            INT_EDGE_BOTH
        } INT_MDOE;

        inline int wiringPiSPISetup(int channel, int speed) { return -1; }
        inline int wiringPiSPIClose(int channel) { return -1; }
        inline int wiringPiSPIClose(int channel) { return -1; }
        inline int wiringPiSPIDataRW (int channel, unsigned char *data, int len) { return -1; }
        inline int wiringPiSetupPinType(enum WPIPinType pinType) { return -1; }
        inline void pinMode(int pin, enum WPIPinMode mode);
        inline void digitalWrite(int pin, int value);
        inline int wiringPiSPISetupMode(int channel, int speed, int mode) { return -1; }
        inline int digitalRead(int pin) { return -1; }
        inline struct WPIWfiStatus waitForInterrupt2(int pin, int edgeMode, int ms, unsigned long debounce_period_us)  { return {-1, 0, -1, -1}; }
    #endif
#else
    #include <wiringPi.h>
    #include <wiringPiSPI.h>
#endif