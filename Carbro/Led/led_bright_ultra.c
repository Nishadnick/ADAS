#include<stdio.h>
#include<wiringPi.h>
#include<stdlib.h>
#include<time.h>

void led(void);
void ultra(void);

const int Led_pin = 18;
const int Trigger = 14;
const int Echo = 24;

int flag = 1;
int intensity = 0;
long starttime;
long stoptime;


int main(void)
{
  if ( wiringPiSetupGpio() == -1 )
  {
	  exit(1);
  }
  pinMode(Led_pin,PWM_OUTPUT);
  pinMode(Trigger,OUTPUT);
  pinMode(Echo,INPUT);
  while(1)
  {
    ultra();
    led();
    delay(10);
  }
  return 0;
}
void led()
{
    pwmWrite(Led_pin,intensity);
    delay(1);
}
void ultra()
{
if(flag)
{
 digitalWrite(Trigger,HIGH);
 delay(1);
 digitalWrite(Trigger,LOW);
 
 while(digitalRead(Echo) == 0 )
 {
  starttime = clock();
 }
 while(digitalRead(Echo) == 1 )
 {
  stoptime = clock();
 }
 intensity = ((stoptime - starttime)*343000)/(2*100000);
 if ( intensity > 1024 )
 {
 intensity = 1023;
 }
 else if (intensity < 0 )
 {
 intensity = 0;
 }
 printf("intensity = %d\n",intensity);

 }
}
