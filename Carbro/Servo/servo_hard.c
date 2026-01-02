#include <stdio.h>
#include <wiringPi.h>

#define SERVO_PIN 13
int main()
{
  if (wiringPiSetupGpio() == -1 )
  {
    printf("Setup failure\n");
    return -1;
  }

  printf("Starting motor\n");  
  pinMode(SERVO_PIN,PWM_OUTPUT);
  pwmSetRange(2000);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(192);
  pwmWrite(SERVO_PIN,0);
  delay(1000);
  while(1)
  {
    for(int i=45; i <245 ;i++)
    {
      pwmWrite(SERVO_PIN,i);
      delay(10);
    }
    for(int i=245; i>=45;i--)
    {
      pwmWrite(SERVO_PIN,i);
      delay(10);
    }
  }
  return 0;
}
