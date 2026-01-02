#include "main.h"

long int StartTime=0;
long int StopTime=0;
double TimeElapsed=0;
double dist=0;

void distU()
{
    //Ultraosnic Trigger with 10 uSec
	  digitalWrite(GPIO_TRIGGER, HIGH);
	  delay(10);
	  digitalWrite(GPIO_TRIGGER, LOW);
	  // save StartTime
    while(digitalRead(GPIO_ECHO) == 0)
        {StartTime = clock();}
    // save time of arrival
    while (digitalRead(GPIO_ECHO) == 1)
        {StopTime = clock();}
	  TimeElapsed=(double) (StopTime - StartTime);
	  dist = (TimeElapsed * 34300) / (2.0*1000000);
	  printf("distance=%f\n",dist);
	  delay(500);
}

void park_mode()
{
    pinMode(BUZZER,OUTPUT);
    digitalWrite(BUZZER,LOW);

    pinMode(MOTOR_CPIN,PWM_OUTPUT);
    pinMode(MOTOR_APIN,OUTPUT);
    pinMode(MOTOR_ENABLE,OUTPUT);
	  pinMode(GPIO_TRIGGER, OUTPUT);
    pinMode(GPIO_ECHO, INPUT);
    pinMode(GPIO_PWM_LED,PWM_OUTPUT);

    digitalWrite(MOTOR_ENABLE,HIGH);
    pwmWrite(MOTOR_CPIN,0);
    digitalWrite(MOTOR_APIN,0);

    double new_dist=0;
    char display[17]="DISTANCE : NONE ";

    int clcd;
    clcd = lcdInit(ROW,COL,PIN_MODE,RS,E,D4,D5,D6,D7,0,0,0,0);

    lcdPosition(clcd,0,0);
    lcdPuts(clcd,"  STATUS : PARK ");
    lcdPosition(clcd,0,1);
    lcdPuts(clcd,display);

    delay(2000);

    char str[12];
    str[11]='\0';

    pwmWrite(MOTOR_CPIN,650);

    while(1)
    {
        distU();
	      new_dist=dist*100;
	      if( new_dist > 1023 )
	      { new_dist = 1023; }
	      else if ( new_dist < 2.5 )
	      { new_dist = 0;}
        pwmWrite(GPIO_PWM_LED, 1023-(new_dist));
        printf("Intensity=%.3lf\n",1023-(new_dist));

        sprintf(str,"%f\n",dist);
        printf("str is  %s\n",str);

        for( int i=0;i<4;i++)
        {
          display[11+i] = str[i];
        }

	      lcdPosition(clcd,0,1);
        lcdPuts(clcd,display);

        if ( dist < 3.5 || dist >1000 )
        {
          lcdPosition(clcd,0,0);
          lcdPuts(clcd,"STATUS : STOP   ");
          lcdPosition(clcd,0,1);
          lcdPuts(clcd,"   CAR PARKED   ");

          pwmWrite(MOTOR_CPIN,0);
          pwmWrite(GPIO_PWM_LED,2000);
          digitalWrite(BUZZER,HIGH);

          break;
        }
    }
    printf("Parked SUCCESSFULLY ..\n");

    delay(2000);

    lcdPosition(clcd,0,0);
    lcdPuts(clcd,"   TURNING OFF  ");
    lcdPosition(clcd,0,1);
    lcdPuts(clcd,"     ENGINE     ");

    delay(2000);

    pwmWrite(GPIO_PWM_LED,0);
    digitalWrite(BUZZER,LOW);
    lcdClear(clcd);
    printf("Engine OFF..\n");

}
