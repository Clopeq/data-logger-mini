#include <iostream>
#include <bitset>
#include <string>
#include <fstream>
#include <filesystem>
#include "config.h"
#include "json.h"
//#include "ADC.h"
//#include "sleep.h"

using namespace std;
using json = nlohmann::json;

void clearConsole() {
    cout << "\033[2J\033[1;1H"; // ANSI escape codes
}

// void ADC_test() {
    
//     ADS1263 ADC(500*1000);

//     ADC.set_gain(GAIN_1);
//     ADC.set_data_rate(SPS_400);

//     PortManager CH0(A0, COMM, 0, 1);
    
//     string command;

//     double new_measurement;

//     clearConsole();
//     while(true) {
//         cout << "CMD: ";
//         cin >> command;
//         clearConsole();

//         if(command == "EXIT") {
//             cout << "EXIT!" << endl;
//             return;
//         } else if(command == "M") {
//             for(int i=0; i<=10; i++) {
//                 cout << i << ": " << ADC.read(CH0) << endl;
//                 sleep(10);
//             }
//         } else if(command == "CAL") {
//             cout << "Current measurement: " << ADC.read(CH0) << endl;
//             cout << "Current cal_factor: " << CH0.get_cal_factor() << endl;
//             cout << "new measurement: ";
//             cin >> new_measurement;
//             CH0.calibrate(ADC.read(CH0), new_measurement);
//             cout << "new measurement: " << ADC.read(CH0) << endl;
//             cout << "new cal_factor: " << CH0.get_cal_factor() << endl;


//         } else if(command == "TARE") {
//             cout << "Current measurement: " << ADC.read(CH0) << endl;
//             cout << "Current tare_factor: " << CH0.get_tare_factor() << endl;
//             cout << "new measurement: ";
//             cin >> new_measurement;
//             CH0.tare(ADC.read(CH0), new_measurement);
//             cout << "new measurement: " << ADC.read(CH0) << endl;
//             cout << "new tare_factor: " << CH0.get_tare_factor() << endl;

//         } else {
//             cout << "Unknown command" << endl;
//         }

//     }
// }

int main() {


    cout << get_config_dir() << endl;



    return 0;
}