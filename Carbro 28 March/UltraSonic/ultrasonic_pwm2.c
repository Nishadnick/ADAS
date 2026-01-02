#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

//#set GPIO Pins
#define GPIO_TRIGGER 14
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
	//printf("distance=%f\n",dist);
//	dist = (TimeElapsed*343);
//	delay(20);
//    return dist;

}

int main(void)
{
	int new_dist=0;
    wiringPiSetupGpio();
    pinMode(GPIO_TRIGGER, OUTPUT);
    pinMode(GPIO_ECHO, INPUT);
    pinMode (18,PWM_OUTPUT) ;
      while(1)
    {
        distU();

	//else
	//{
	//	pwmWrite();
		//digitalWrite(14,LOW);
	//}
	//if(dist>=100)
	//{dist=100;}

	new_dist=dist*10;
	if( new_dist > 1023 )
	new_dist = 1023;
	else if ( new_dist < 0 )
	new_dist = 0;
	pwmWrite (14, 1023-(new_dist));

//	printf("Measured Distance =%.3f\n",dist);
	//delay(100);
    }
    return 0;
}

