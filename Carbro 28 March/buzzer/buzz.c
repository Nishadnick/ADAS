
#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>

//Pin 11 on Raspberry Pi corresponds to BCM GPIO 17 and wiringPi pin 0
#define BeepPin 21
void sig_handler(int sig_num)
{

}

int main(void)
{
  if(-1 == wiringPiSetupGpio())
  {
      printf("setup wiringPi failed!");
      return 1;
  }
  //Set GPIO pin
  pinMode(BeepPin, OUTPUT);
  signal(SIGINT, sig_handler);
  //Play a sound until the user closes the app
  while(1)
  {
    digitalWrite(BeepPin, LOW);
    delay(300);
    digitalWrite(BeepPin, HIGH);
    delay(300);
  }

  return 0;
}
