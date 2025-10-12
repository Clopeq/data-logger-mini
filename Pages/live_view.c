
#include "live_view.h"



void live_view() {
    printf("TEST_ADC1\r\n");
    
    #define ChannelNumber 5
    UBYTE ChannelList[ChannelNumber] = {0, 1, 2, 3, 4};    // The channel must be less than 10
        
    //UDOUBLE Value[ChannelNumber] = {0};
    while(1) {
        //ADS1263_GetAll(ChannelList, Value, ChannelNumber);  // Get ADC1 value
        for(int i=0; i<ChannelNumber; i++) {
            printf("IN%d is %lf \n", ChannelList[i], ADC_read(ChannelList[i]));
            // if((Value[i]>>31) == 1)
            //     printf("IN%d is -%lf \r\n", ChannelList[i], REF*2 - Value[i]/2147483648.0 * REF);      //7fffffff + 1
            // else
            //     printf("IN%d is %lf \r\n", ChannelList[i], Value[i]/2147483647.0 * REF);       //7fffffff
        }
        for(int i=0; i<ChannelNumber; i++) {
            printf("\33[1A");   // Move the cursor up
        }
    }
}