#include <wiringPi.h>
#include <stdio.h>

int main (void)
{
   printf ("Raspberry Pi wiringPi test program\n");
   wiringPiSetupGpio();
   pinMode(18, OUTPUT);
  // pinMode (18, PWM_OUTPUT) ;
//   pwmSetMode (PWM_MODE_MS);
//   pwmSetRange (2000);
//   pwmSetClock (192);
   while(1)
   {
   digitalWrite(18,HIGH);
//      pwmWrite(18,650);
      delay(100);
  //    pwmWrite(18,200);
//    digitalWrite(18,LOW);
   }
   return 0;
}
