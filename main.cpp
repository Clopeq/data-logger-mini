#include <iostream>
#include <bitset>
#include <string>
#include "ADC.h"
#include "sleep.h"

using namespace std;



int main() {
    
    cout << "Hello, World!" << endl;

    ADS1263 ADC(500*1000);

    ADC.set_gain(GAIN_1);
    ADC.set_data_rate(SPS_400);

    PortManager CH0(A0, COMM, 0, 1);


    // for(int i=0; i<=1000; i++) {
    //     cout << i << ": " << ADC.read(CH0) << endl;
    //     sleep(10);
    // }
    
    string command;

    cout << "CMD: " << endl;
    cin >> command;
    cout << command << endl;


    return 0;
}