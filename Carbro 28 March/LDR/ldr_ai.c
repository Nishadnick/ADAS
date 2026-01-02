#include <wiringPi.h>
#include <stdio.h>

#define LDR_PIN 0   // GPIO pin to which LDR is connected
#define LED_PIN 1   // GPIO pin to which LED is connected
#define LDR_THRESHOLD 500   // threshold value for LDR reading

int main(void) {
    int ldr_value;
    wiringPiSetup();   // initialize WiringPi library

    pinMode(LED_PIN, OUTPUT);   // set LED pin as output
    pinMode(LDR_PIN, INPUT);    // set LDR pin as input

    while(1) {
        ldr_value = analogRead(LDR_PIN);   // read LDR value
        printf("%d\n",ldr_value);
        if(ldr_value > LDR_THRESHOLD) {
            digitalWrite(LED_PIN, HIGH);   // turn on LED
        } else {
            digitalWrite(LED_PIN, LOW);    // turn off LED
        }
        delay(100);   // wait for 100ms before reading LDR again
    }
    return 0;
}
