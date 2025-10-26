#include <iostream>
#include <bitset>
#include "ADC.h"

using namespace std;

int main() {
    
    cout << "Hello, World!" << endl;

    ADS1263 ADC(500*1000);

    ADC.set_gain(GAIN_1);
    ADC.set_data_rate(SPS_2d5);

    cout << endl;
    cout << "ADC.READ()" << endl;
    ADC.read(0);
    
    return 0;
}