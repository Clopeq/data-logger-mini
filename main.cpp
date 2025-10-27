#include <iostream>
#include <bitset>
#include "ADC.h"

using namespace std;

int main() {
    
    cout << "Hello, World!" << endl;

    ADS1263 ADC(500*1000);

    ADC.set_gain(GAIN_4);
    ADC.set_data_rate(SPS_38400);

    cout << endl;
    cout << "ADC.READ()" << endl;
    ADC.read(0);

    for(int i=0; i<=6; i++) {
        cout << "CH" << i << ": " << ADC.read(0) << endl;
    }
    
    return 0;
}