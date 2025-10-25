#include <iostream>
#include <bitset>
#include "ADC.h"

using namespace std;

int main() {
    
    cout << "Hello, World!" << endl;

    ADS1263 ADC(500*1000);

    //int ID = ADC.read_register(REG_ID);

    //cout << "ID: " << bitset<8>(ID) << endl;


    cout << "Initial MODE2: " << endl;
    int mode2 = ADC.read_register(REG_MODE2);
    cout << endl;

    cout << "Set data rate" << endl;
    ADC.set_data_rate(SPS_38400);
    cout << endl;

    
    cout << "Set gain" << endl;
    ADC.set_gain(GAIN_2);
    cout << endl;

    return 0;
}