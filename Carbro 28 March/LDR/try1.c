#include <wiringPi.h>
#include <stdio.h>

#define PIN_TO_CIRCUIT 7

int rc_time(int pin_to_circuit) {
  int count = 0;

  //Output on the pin for
  pinMode(pin_to_circuit, OUTPUT);
  digitalWrite(pin_to_circuit, LOW);
  delay(100);

  //Change the pin back to input
  pinMode(pin_to_circuit, INPUT);

  //Count until the pin goes high
  while (digitalRead(pin_to_circuit) == LOW) {
    count++;
  }

  return count;
}

int main(void) {
  int reading;
  wiringPiSetupPhys();
  
  //Catch when script is interrupted, cleanup correctly
  while (1) {
    reading = rc_time(PIN_TO_CIRCUIT);
    printf("%d\n", reading);
    delay(500);
  }

  return 0;
}
