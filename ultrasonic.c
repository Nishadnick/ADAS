#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
//#set GPIO Pins
#define GPIO_TRIGGER  18
#define GPIO_ECHO  24

int main(void)
{
    
  
//wiringPiSetup(); // Initializes wiringPi using wiringPi's simlified number system.
wiringPiSetupGpio(); // Initializes wiringPi using the Broadcom GPIO pin numbers

//12    1
//18   5
pinMode(GPIO_TRIGGER, OUTPUT);
pinMode(GPIO_ECHO, INPUT);
int StartTime=0;
int StopTime=0;
int TimeElapsed=0;
int distU()
{
	int dist=0;
	digitalWrite(GPIO_TRIGGER, HIGH);
	
	delay(50);
	
	digitalWrite(GPIO_TRIGGER, LOW);
	
	StartTime=time(NULL);
	StopTime=time(NULL);
	
	// save StartTime
    while(digitalRead(GPIO_ECHO) == 0)
        StartTime = time();
 
    // save time of arrival
    while (digitalRead(GPIO_ECHO) == 1)
        StopTime = time();
	
	TimeElapsed=StopTime - StartTime;
	
	dist = (TimeElapsed * 34300) / 2;
 
    return dist;
	
}

int main()
{
	int dist=0;
	while(1)
	{
		dist=distU();
		printf("Measured Distance =%.1d",dist);
		delay(50);
	}


}

/*
    pinMode(5, OUTPUT);

    pullUpDnControl(button, PUD_UP);

    while (1){
        if (digitalRead(button) == LOW) {
            fprintf(stderr, "Switch is pressed\n");
                printf("BUTTON PRESSED.......\n");
                //pinMode(5, INPUT);
                digitalWrite(5, HIGH);
        } else {
                digitalWrite(5, LOW);
                //pinMode(5, OUTPUT);
            fprintf(stderr, "Switch is released\n");
            }
            delay(50);
    }

    return 0;
}*/

