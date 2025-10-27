#include <iostream>
#include <bitset>
#include "ADC.h"
#include "sleep.h"

using namespace std;

int main() {
    
    cout << "Hello, World!" << endl;

    ADS1263 ADC(500*1000);

    ADC.set_gain(GAIN_4);
    ADC.set_data_rate(SPS_38400);

    cout << endl;
    cout << "ADC.READ()" << endl;
    ADC.read(0);

    for(int i=0; i<=1000; i++) {
        cout << i << ": " << ADC.read(0) << endl;
        sleep(10);
    }
    
    return 0;
}