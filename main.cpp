#include "mbed.h"
#include "SHT21.h"

Serial pc (USBTX, USBRX);

SHT21 sht21(p9, p10);

int main() {
    while(1) {
        double temp;
        double rh;
        temp = sht21.getTemp();
        rh = sht21.getHumid();
        
        pc.printf("temp:\t%f\n", temp);
        pc.printf("rh:\t%f\n", rh);
        
    }
}
