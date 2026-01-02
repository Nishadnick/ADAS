#include "main.h"

int main(void)
{
  if(wiringPiSetupGpio() == -1 )
  {
    printf("Setup Failure\n");
  }
  else
  {
     pinMode(START_STOP_BUTTON,INPUT);
     printf("START THE ENGINE..\n");
     printf("PRESS THE IGNITION BUTTON\n");
     while(1)
     {
        if(digitalRead(START_STOP_BUTTON) == LOW )
        {
          printf("Engine ON\n");
          drive_mode();
          printf("\nPARKING MODE STARTED\n");
          delay(2000);
          park_mode();
          break;
        }
     }
  }
}
