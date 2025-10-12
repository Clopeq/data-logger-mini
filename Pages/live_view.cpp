
#include "live_view.h"



void live_view() {
    printf("TEST_ADC1\r\n");
    
    #define ChannelNumber 5
    signed int ChannelList[ChannelNumber] = {0, 1, 2, 3, 4};    // The channel must be less than 10
        
    //UDOUBLE Value[ChannelNumber] = {0};
    while(1) {

        for(int i=0; i<ChannelNumber; i++) {
            printf("IN%d is %lf \n", ChannelList[i], ADC_read(ChannelList[i]));
        }
        for(int i=0; i<ChannelNumber; i++) {
            printf("\33[1A");   // Move the cursor up
        }
    }
}