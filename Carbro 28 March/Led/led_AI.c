#include <stdio.h>
	#include <stdlib.h>
	#include <wiringPi.h>

	// Pin definitions
	#define TRIG_PIN 4
	#define ECHO_PIN 5
	#define LED_PIN 1

	int main(void) {
	    // Initialize WiringPi library
	    if (wiringPiSetup() == -1) {
		fprintf(stderr, "Failed to initialize WiringPi library\n");
		return 1;
	    }

	    // Configure pins for ultrasonic sensor
	    pinMode(TRIG_PIN, OUTPUT);
	    pinMode(ECHO_PIN, INPUT);

	    // Configure pin for LED
	    pinMode(LED_PIN, PWM_OUTPUT);

	    while (1) {
		// Trigger ultrasonic sensor
		digitalWrite(TRIG_PIN, HIGH);
		delayMicroseconds(10);
		digitalWrite(TRIG_PIN, LOW);

		// Wait for echo to start
		while (digitalRead(ECHO_PIN) == LOW);

		// Measure duration of echo
		unsigned long start_time = micros();
		while (digitalRead(ECHO_PIN) == HIGH);
		unsigned long end_time = micros();
		unsigned long duration = end_time - start_time;

		// Calculate distance in cm
		float distance = duration / 58.0;

		// Adjust LED brightness based on distance
		int brightness = 255 - (int)(distance * 2.55);
		pwmWrite(LED_PIN, brightness);

		// Print distance and brightness to console
		printf("Distance: %.2f cm\n", distance);
		printf("Brightness: %d\n", brightness);

		// Wait for 500ms before next measurement
		delay(500);
	    }

	    return 0;
	}
