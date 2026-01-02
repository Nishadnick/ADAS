#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

#define TRIG_PIN 4
#define ECHO_PIN 5
#define LED_PIN 1

int main() {
    if (wiringPiSetup() == -1) {
        printf("WiringPi setup failed!\n");
        return 1;
    }

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, PWM_OUTPUT);

    digitalWrite(TRIG_PIN, LOW);
    delay(500);

    while (1) {
        // Send 10us pulse to trigger pin
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);

        // Measure pulse duration from echo pin
        while (digitalRead(ECHO_PIN) == LOW);
        long startTime = clock();
        while (digitalRead(ECHO_PIN) == HIGH);
        long travelTime = clock() - startTime;

        // Calculate distance in cm
        int distance = travelTime / (58);
        ;printf("distance = %d\n",distance);

        // Increase brightness of LED if distance decreases
        int brightness = (distance > 100) ? 0 : (100 - distance);
        printf("brigthness = %d\n",brightness);
        pwmWrite(LED_PIN, brightness);

        delay(100); // Wait 100ms before next measurement
    }

    return 0;
}
