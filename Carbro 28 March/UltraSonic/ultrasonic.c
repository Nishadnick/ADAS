#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

//#set GPIO Pins
#define GPIO_TRIGGER 18
#define GPIO_ECHO 24

//wiringPiSetup(); // Initializes wiringPi using wiringPi's simlified number system.
//wiringPiSetupGpio(); // Initializes wiringPi using the Broadcom GPIO pin numbers

//int GPIO_TRIGGER=18;
//int GPIO_ECHO=24;

long int StartTime=0;
long int StopTime=0;
double TimeElapsed=0;
double dist=0;

//	StartTime=time(NULL);
//	StopTime=time(NULL);

void distU()
{

	digitalWrite(GPIO_TRIGGER, HIGH);

	delay(10);

	digitalWrite(GPIO_TRIGGER, LOW);

	

	// save StartTime
    while(digitalRead(GPIO_ECHO) == 0)
        {StartTime = clock();
//	printf("Starttime=%ld\n",StartTime);
	}

    // save time of arrival
    while (digitalRead(GPIO_ECHO) == 1)
        {StopTime = clock();
//	printf("Stoptime=%ld\n",StopTime);
		
	}

	TimeElapsed=(double) (StopTime - StartTime);

	dist = (TimeElapsed * 34300) / (2.0*1000000);
//	dist = (TimeElapsed*343);
//	delay(20);
//    return dist;

}

int main(void)
{
    wiringPiSetupGpio();
    pinMode(GPIO_TRIGGER, OUTPUT);
    pinMode(GPIO_ECHO, INPUT);
    pinMode (14, OUTPUT) ;
      while(1)
    {
        distU();

	if(dist<=10)
	{
		digitalWrite (14, HIGH);
	}
	else
	{
		digitalWrite(14,LOW);
	}
	if(dist>=100)
	{dist=100;}

	printf("Measured Distance =%.3f\n",dist);
	delay(500);
    }
    return 0;
}

