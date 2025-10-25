#include <iostream>
#include <bitset>
#include "ADC.h"

using namespace std;

int main() {
    
    cout << "Hello, World!" << endl;

    ADS1263 ADC(500*1000);

    int ID = ADC.read_register(REG_ID);

    cout << "ID: " << bitset<8>(ID) << endl;

    ADC.set_data_rate(SPS_2d5);

    return 0;
}