#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>

// set GPIO Pins
#define GPIO_TRIGGER 18
#define GPIO_ECHO 24

int main(void) {
  long StartTime, StopTime;
  double TimeElapsed, distance;

  // GPIO Mode (BOARD / BCM)
  wiringPiSetupGpio();

  // set GPIO direction (IN / OUT)
  pinMode(GPIO_TRIGGER, OUTPUT);
  pinMode(GPIO_ECHO, INPUT);

  while (1) {
    // set Trigger to HIGH
    digitalWrite(GPIO_TRIGGER, HIGH);

    // set Trigger after 0.01ms to LOW
    delayMicroseconds(10);
    digitalWrite(GPIO_TRIGGER, LOW);

    StartTime = micros();
    StopTime = micros();

    // save StartTime
    while (digitalRead(GPIO_ECHO) == LOW) {
      StartTime = micros();
    }

    // save time of arrival
    while (digitalRead(GPIO_ECHO) == HIGH) {
      StopTime = micros();
    }

    // time difference between start and arrival
    TimeElapsed = (double)(StopTime - StartTime);

    // multiply with the sonic speed (34300 cm/s)
    // and divide by 2, because there and back
    distance = (TimeElapsed * 34300) / (2 * 1000000);

    printf("Measured Distance = %.1f cm\n", distance);

    delay(1000);
  }

  return 0;
}


