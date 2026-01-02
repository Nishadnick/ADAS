#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <time.h>
#define LED_PIN 18  // PWM pin for LED
#define TRIG_PIN 23  // Ultrasonic sensor trigger pin
#define ECHO_PIN 24  // Ultrasonic sensor echo pin

// Function to measure distance using ultrasonic sensor
float measure_distance() {
    // Send a 10us pulse to trigger the ultrasonic sensor
    digitalWrite(TRIG_PIN, HIGH);
    usleep(10);
    digitalWrite(TRIG_PIN, LOW);
    
    // Measure the time it takes for the echo to return
    unsigned int pulse_start, pulse_end;
    while (digitalRead(ECHO_PIN) == LOW);
    //pulse_start = micros();
    pulse_start = clock();
    while (digitalRead(ECHO_PIN) == HIGH);
    //pulse_start = micros();
    pulse_end = clock();
    
    
    // Convert the time to distance in cm
    float pulse_duration = (pulse_end - pulse_start) / 1000000.0;
    float distance = pulse_duration * 34300 / 2;
    return distance;
}

int main() {
    // Initialize wiringPi library
    wiringPiSetupGpio();              //BCM layout
    
    // Initialize LED pin as PWM output
    pinMode(LED_PIN, PWM_OUTPUT);
//    pwmSetRange(1000);
 //   pwmSetClock(500);
    pwmWrite(LED_PIN, 0);

    // Initialize ultrasonic sensor pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Loop to measure distance and adjust LED brightness
    while (1) {
        float distance = measure_distance();
        printf("distance = %f\n",distance);
        int brightness;
        if ( distance < 10.0 )
        {
             brightness = (10 - distance)*100;
        }
        else
        {
             brightness = 0;
        }

        printf("bright = %d\n",brightness);
        pwmWrite(LED_PIN, brightness);
//        usleep(100000);  // Sleep for 100ms
        delay(100);
    }
    
    // Turn off LED and clean up GPIO pins
    pwmWrite(LED_PIN, 0);
    pinMode(LED_PIN, INPUT);
    pinMode(TRIG_PIN, INPUT);
    pinMode(ECHO_PIN, INPUT);
    
    return 0;
}
