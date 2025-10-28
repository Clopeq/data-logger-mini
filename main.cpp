#include <iostream>
#include <bitset>
#include <string>
#include "ADC.h"
#include "sleep.h"

using namespace std;

void clearConsole() {
    cout << "\033[2J\033[1;1H"; // ANSI escape codes
}

int main() {
    

    ADS1263 ADC(500*1000);

    ADC.set_gain(GAIN_1);
    ADC.set_data_rate(SPS_400);

    PortManager CH0(A0, COMM, 0, 1);


    // for(int i=0; i<=1000; i++) {
    //     cout << i << ": " << ADC.read(CH0) << endl;
    //     sleep(10);
    // }
    
    string command;

    double new_measurement;

    while(true) {
        clearConsole();
        cout << "CMD: ";
        cin >> command;
        clearConsole();

        if(command == "EXIT") {
            cout << "EXIT!" << endl;
            return 0;
        }

        if(command == "") {
            for(int i=0; i<=10; i++) {
                cout << i << ": " << ADC.read(CH0) << endl;
                sleep(10);
            }
        }

        if(command == "CAL") {
            cout << "new measurement: ";
            cin >> new_measurement;
            CH0.calibrate(ADC.read(CH0), new_measurement);

        }

        
        if(command == "TARE") {
            cout << "new measurement: ";
            cin >> new_measurement;
            CH0.tare(ADC.read(CH0), new_measurement);

        }

    }


    return 0;
}