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


    cout << filesystem::current_path().string() + "/config" << endl;

    // cout << "Hello, World!" << endl;

    // ofstream f("j.json");

    // if (!f) {
    //     cerr << "Error opening file!" << endl;
    //     return 1;
    // }
    
    // json file = {
    //     {"happy", true},
    //     {"pi", 3.1415},
    // };

    // json j;

    // j["pi"] = 3.1415;
    // j["happy"] = true;
    // j["name"] = "Maja";
    // j["nothing"] = nullptr;
    // j["answer"]["everything"] = 42;
    // j["list"] = {1, 0, 2};
    // j["object"] = {{"currency", "USD"}, {"value", 42.99}};
    
    // json j2 = {
    //     {"happy", true},
    //     {"pi", 3.1415},
    //     {"answer", {
    //         {"everything", 42}
    //     }},
    //     {"object", {
    //         {"currency", "USD"},
    //         {"value", 45}
    //     }}
    // };


    // f << setw(2) << j2 << endl;


    // f.close();

    // ifstream f2("j.json");

    // if (!f2) {
    //     cerr << "Error opening file!" << endl;
    //     return 1;
    // }

    
    // json j3 = json::parse(f2);
    // cout << setw(2) << j3 << endl;

    // f2.close();

    // cout << endl << endl;

    // cout << "pi: " << j3["object"] << endl;


    // for(int i=0; i<=1000; i++) {
    //     cout << i << ": " << ADC.read(CH0) << endl;
    //     sleep(10);
    // }
    




    return 0;
}