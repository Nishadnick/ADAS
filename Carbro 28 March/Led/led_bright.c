#include<stdio.h>
#include<wiringPi.h>
#include<stdlib.h>

const int Led_pin = 1;
int intensity = 0;
int main(void)
{
  if ( wiringPiSetup() == -1 )
  {
	  exit(1);
  }
  pinMode(Led_pin,PWM_OUTPUT);
  int flag = 1;
  while(1)
  {
    if ( flag )
    {
      if ( intensity++ < 1024 )
      {
        pwmWrite(Led_pin,intensity);
        delay(1);
      }
      else
      {
        flag = !flag;
        delay(1);
      }
    }
    else
    {
      if ( intensity-- > 0 )
      {
        pwmWrite(Led_pin,intensity);
        delay(1);
      }
      else
      {
        flag = !flag;
        delay(1);
      }
    }
  }
  return 0;
}
