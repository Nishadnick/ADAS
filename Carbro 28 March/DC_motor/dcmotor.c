
#include<stdio.h>
#include<wiringPi.h>
#include<time.h>

#define MOTOR_ENABLE 27
#define MOTOR_CPIN_1 12
#define MOTOR_ACPIN_1 17

int main()
{
    wiringPiSetupGpio();
    pinMode(MOTOR_ENABLE,OUTPUT);
    pinMode(MOTOR_CPIN_1,PWM_OUTPUT);
    //pinMode(MOTOR_CPIN_1,OUTPUT);
    pinMode(MOTOR_ACPIN_1,OUTPUT);
    int opt=0;
    printf("press 1 for forward or 2 for backward \n");
    scanf("%d",&opt);
    digitalWrite(MOTOR_ENABLE,HIGH);
    while(1)
    {
       if(opt==1)
       {
 
          // digitalWrite(MOTOR_CPIN_1,HIGH);
          pwmWrite(MOTOR_CPIN_1,650);
          digitalWrite(MOTOR_ACPIN_1,LOW);
          delay(1000);
       }
       else
       {
           //digitalWrite(MOTOR_CPIN_1,LOW);
           pwmWrite(MOTOR_CPIN_1,0);
           digitalWrite(MOTOR_ACPIN_1,HIGH);
           delay(1000);
       }
          
          // digitalWrite(MOTOR_CPIN_1,LOW);
           pwmWrite(MOTOR_CPIN_1,0);
           digitalWrite(MOTOR_ACPIN_1,LOW);
           delay(1000);
       //pwmWrite(MOTOR_PWM, 50);
    } 
}

