#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

#define LED_PIN 18  // PWM pin for LED
#define TRIG_PIN 4  // Ultrasonic sensor trigger pin
#define ECHO_PIN 5  // Ultrasonic sensor echo pin

volatile bool running = true;

// Interrupt handler for Ctrl+C
void handle_sigint(int sig) {
    running = false;
}

// Function to measure distance using ultrasonic sensor
float measure_distance() {
    // Send a 10us pulse to trigger the ultrasonic sensor
    digitalWrite(TRIG_PIN, HIGH);
    usleep(10);
    digitalWrite(TRIG_PIN, LOW);
    
    // Measure the time it takes for the echo to return
    unsigned int pulse_start, pulse_end;
    while (digitalRead(ECHO_PIN) == LOW);
    pulse_start = micros();
    while (digitalRead(ECHO_PIN) == HIGH);
    pulse_end = micros();
    
    // Convert the time to distance in cm
    float pulse_duration = (pulse_end - pulse_start) / 1000000.0;
    float distance = pulse_duration * 34300 / 2;
    return distance;
}

int main() {
    // Initialize wiringPi library
    wiringPiSetupGpio();
    
    // Initialize LED pin as PWM output
    pinMode(LED_PIN, PWM_OUTPUT);
    pwmSetRange(100);
    pwmSetClock(500);
    pwmWrite(LED_PIN, 0);
    
    // Initialize ultrasonic sensor pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    
    // Register interrupt handler for Ctrl+C
    signal(SIGINT, handle_sigint);
    
    // Loop to measure distance and adjust LED brightness
    while (running) {
        float distance = measure_distance();
        int brightness = (100 - distance) * 2;  // Inverse linear relationship
        brightness = (brightness < 0) ? 0 : brightness;  // Ensure brightness is within range
        brightness = (brightness > 100) ? 100 : brightness;
        pwmWrite(LED_PIN, brightness);
        usleep(100000);  // Sleep for 100ms
    }
    
    // Turn off LED and clean up GPIO pins
    pwmWrite(LED_PIN, 0);
    pinMode(LED_PIN, INPUT);
    pinMode(TRIG_PIN, INPUT);
    pinMode(ECHO_PIN, INPUT);
    
    return 0;
}

