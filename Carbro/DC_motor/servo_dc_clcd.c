#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <lcd.h>
#include <string.h>

#define GPIO_SERVO 13

#define MOTOR_ENABLE 27
#define MOTOR_CPIN 12
#define MOTOR_APIN 6

#define RS 25
#define E 24
#define D4 23
#define D5 17
#define D6 18
#define D7 22

#define ROW 2
#define COL 16
#define PIN_MODE 4

int main()
{ 
    if( wiringPiSetupGpio() == -1 )
    {
      return -1;
    }
    int clcd;
    clcd = lcdInit(ROW,COL,PIN_MODE,RS,E,D4,D5,D6,D7,0,0,0,0);
    lcdPosition(clcd,0,0);
    lcdPuts(clcd,"  MODE : DRIVE  ");
    lcdPosition(clcd,0,1);
    lcdPuts(clcd,"  CHOOSE  PATH  ");
    int n;
    printf("1.Path A\n2.Path B\n3.Path C\n4.Path D\n5.Path E\nSelect any path from above : ");
    scanf("%d",&n);
    int a;
    int start = 150;
    int ptr[5][2]={{245,45},{45,245},{45,45},{245,245},{150,150}};
    pinMode(MOTOR_ENABLE,OUTPUT);
    pinMode(MOTOR_CPIN,PWM_OUTPUT);
    pinMode(MOTOR_APIN,OUTPUT);
    pinMode(GPIO_SERVO,PWM_OUTPUT);
    pwmSetRange(2000);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(192);
    switch(n)
    {
	    case 1:
	    {
		    printf("Path A contains 2 turns..\n.IT goes straight for 10mts takes a right turn for 90deg. then goes straight, the takes a left turn for 90 deg.and goes straight for 10ms and stops.\n");
	    	a = 0;
	    	lcdPosition(clcd,0,1);
        lcdPuts(clcd,"PATH A SELECTED.");
	    break;
	    }
	    case 2:
	    {
		    printf("Path B contains 2 turns..\n.IT goes straight for 10mts takes a right turn for 90deg. then goes straight, the takes a left right for 90 deg.and goes straight for 10ms and stops.\n");
	    	a = 1;
	    	lcdPosition(clcd,0,1 );
        lcdPuts(clcd,"PATH B SELECTED.");
	    break;
	    }
	    case 3:
	    {
		    printf("Path C contains 2 turns..\n.IT goes straight for 10mts takes a  left turn for 90deg.then goes straight, the takes a again a left turn for 90 deg.and goes straight for 10ms and stops.\n");
	  	  a = 2;
	  	  lcdPosition(clcd,0,1);
        lcdPuts(clcd,"PATH C SELECTED.");
	    break;
	    }
	    case 4:
	    {
		    printf("Path D contains 2 turns..\n.IT goes straight for 10mts takes a right turn for 90deg. then goes straight, the takes again right turn for 90 deg.and goes straight for 10ms and stops.\n");
		    a = 3;
		    lcdPosition(clcd,0,1);
        lcdPuts(clcd,"PATH D SELECTED.");
	    break;
	    }
	    case 5:
	    {
		    printf("Path E goes straight for 50mts and stops.\n");
		    a = 4;
		    lcdPosition(clcd,0,1);
        lcdPuts(clcd,"PATH E SELECTED.");
	    break;
	    }
	    default:
	      printf("wrong input\n");
	      lcdPosition(clcd,0,1);
        lcdPuts(clcd,"PATH DONT EXIST.");
    }
    if ( n!=0 && n < 6 )
    {
    digitalWrite(MOTOR_ENABLE,HIGH);
    printf("Setting motors to initial position.\n");
    for(int i = 0; i<1000;i++ )
    {
      pwmWrite(GPIO_SERVO,300);
    }
    int arr[2];
    for(int i=0; i<2;i++)
    {
	    arr[i] = ptr[a][i];
    }

    delay(2000);

		printf("Starting motor...\n");
		lcdPosition(clcd,0,0);
    lcdPuts(clcd,"PATH DIRECTIONS");
    lcdPosition(clcd,0,1);
    lcdPuts(clcd,"GOES STRAIGHT...");
    for(long int i = 0;i < 3000000; i++)
	  {
	     pwmWrite(GPIO_SERVO,0);
	     digitalWrite(MOTOR_APIN,LOW);
	     pwmWrite(MOTOR_CPIN,2000);
	  }

     	for(int j=0;j<2;j++)
    	{
  	    digitalWrite(MOTOR_APIN,LOW);
	      if( arr[j] > 150 )
	      {
	        lcdPosition(clcd,0,1 );
	        if( n != 5 )
	        {
          lcdPuts(clcd,"RIGHT & STRAIGHT");
          }
          else
          {
          lcdPuts(clcd,"  GOES STRAIGHT ");
          }
	      	for(int i = start; i<arr[j];i++)
	      	{
		        pwmWrite(GPIO_SERVO,i);
		        pwmWrite(MOTOR_CPIN,700);
		        delay(10);
		      }
	      	for(int i = arr[j]; i>=start;i--)
	      	{
	      	   lcdPosition(clcd,0,1 );
		         pwmWrite(GPIO_SERVO,i);
		         pwmWrite(MOTOR_CPIN,650);
		         delay(5);
	      	}
	      }
	      else
	      {
	      	lcdPosition(clcd,0,1);
	        if( n != 5 )
	        {
          lcdPuts(clcd,"LEFT & STRAIGHT ");
          }
          else
          {
          lcdPuts(clcd,"  GOES STRAIGHT ");
          }
	        for(int i = start; i>=arr[j];i--)
	      	{
	 	         pwmWrite(GPIO_SERVO,i);
	 	         pwmWrite(MOTOR_CPIN,700);
	 	         delay(10);
	      	}
	      	for(int i = arr[j]; i<start;i++)
	      	{
	      	   lcdPosition(clcd,0,1 );
		         pwmWrite(GPIO_SERVO,i);
		         pwmWrite(MOTOR_CPIN,650);
		         delay(5);
	       	}
	      }
	      for(long int i = 0;i < 5000000; i++)
	      {
	        pwmWrite(GPIO_SERVO,0);
	        pwmWrite(MOTOR_CPIN,2000);
	      }
     }
     pwmWrite(MOTOR_CPIN,0);

     lcdPosition(clcd,0,0 );
     lcdPuts(clcd,"  MODE : STOP   ");
     lcdPosition(clcd,0,1 );
     lcdPuts(clcd," DEST ARRAIVED. ");
     printf("You have reached the location..\n");
   }
   else
   {
   lcdPosition(clcd,0,0 );
   lcdPuts(clcd,"  MODE : NONE   ");
   lcdPosition(clcd,0,1 );
   lcdPuts(clcd,"  WRONG INPUT.  ");
   printf("Wrong input choosen..\n");
   }
   return 0;
}
