#include "sleep.h"
#include <chrono>
#include <thread>

void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void usleep(int microseconds) {
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}

void nsleep(int nanoseconds) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(nanoseconds));
}