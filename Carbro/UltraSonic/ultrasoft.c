#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <softPwm.h>
//#set GPIO Pins
#define GPIO_TRIGGER 23
#define GPIO_ECHO 24
#define GPIO_PWM 18         //PWM pin
//int GPIO_TRIGGER=18;
//int GPIO_ECHO=24;

long int StartTime=0;
long int StopTime=0;
double TimeElapsed=0;
double dist=0;
int threshold=10;
//	StartTime=time(NULL);
//	StopTime=time(NULL);

void distU()
{
  //Ultrasonic Trigger with 10 uSec
	digitalWrite(GPIO_TRIGGER, HIGH);
	delay(10);
	digitalWrite(GPIO_TRIGGER, LOW);

  	// save StartTime
   while(digitalRead(GPIO_ECHO) == 0)
        {StartTime = clock();	}
    // save time of arrival
    while (digitalRead(GPIO_ECHO) == 1)
        {StopTime = clock();	}

	TimeElapsed=(double) (StopTime - StartTime);

	dist = (TimeElapsed * 34300) / (2.0*1000000);
    delay(200);
//return dist;

}

int main(void)
{
    wiringPiSetupGpio();
    pinMode(GPIO_TRIGGER, OUTPUT);
    pinMode(GPIO_ECHO, INPUT);
    pinMode (GPIO_PWM, OUTPUT) ;
    softPwmCreate(GPIO_PWM,1,1000);	/* set PWM channel along with range*/
   
    while(1)
    {
        distU();
    	  if(dist<=threshold)                //
	      { softPwmWrite(GPIO_PWM, (threshold-dist)*100); }
	      else if (dist>threshold)
	      { softPwmWrite(GPIO_PWM, 0); }
  //    	if(dist>=100)
	//      {dist=100;}

      	printf("Measured Distance =%.3f\n",dist);
        
	      //delay(10);
    }
    return 0;
}

