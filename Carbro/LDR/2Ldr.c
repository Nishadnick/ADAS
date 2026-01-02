#include <wiringPi.h>
#include <stdio.h>

#define LDR_THRESHOLD 1000
#define LDR_PIN 8
#define LIGHT_PIN 11

int read_ldr(int pin) {
  int reading = 0;
  
  pinMode(LIGHT_PIN, OUTPUT);
  digitalWrite(pin, LOW);
  delay(100);
  pinMode(pin, INPUT);
  
  while (digitalRead(pin) == LOW) {
    reading++;
  }
  
  return reading;
}

void switch_on_light(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

void switch_off_light(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

int main(void) {
  int ldr_reading;
  wiringPiSetup();
  
  pinMode(LDR_PIN, INPUT);
  
  while (1) {
    ldr_reading = read_ldr(LDR_PIN);
    
    if (ldr_reading < LDR_THRESHOLD) {
      switch_on_light(LIGHT_PIN);
    } else {
      switch_off_light(LIGHT_PIN);
    }
    
    delay(1000);
  }
  
  return 0;
}
