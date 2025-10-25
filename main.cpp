#include <iostream>
#include <bitset>
#include "ADC.h"

using namespace std;

int main() {
    
    cout << "Hello, World!" << endl;

    ADS1263 ADC(500*1000);

    int ID = ADC.read_register(REG_ID);

    //cout << "ID: " << bitset<8>(ID) << endl;


    int mode2 = ADC.read_register(REG_MODE2);

    cout << endl;
    cout << "Initial MODE2: " << bitset<8>(mode2) << endl;

    
    ADC.set_data_rate(SPS_38400);

    
    mode2 = ADC.read_register(REG_MODE2);

    cout << endl;
    cout << "After change MODE2: " << bitset<4>(mode2) << endl;

    return 0;
}