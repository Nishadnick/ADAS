#include <stdio.h>
#include <wiringPi.h>

#define GPIO_SERVO 13

int main()
{
    if( wiringPiSetupGpio() == -1 )
    {
      return -1;
    }
    int n;
    printf("Path 1\nPath 2\n");
    scanf("%d",&n);
    int a;
    int start = 150;
    int ptr[2][2]={{245,45},{45,245}};
    pinMode(GPIO_SERVO,PWM_OUTPUT);
    pwmSetRange(2000);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(192);
    switch(n)
    {
	    case 1:
	    {
		    printf("Path one contains 2 turns..\n.IT goes straight for 10ms takes a right turn for 90deg. the takes a left turn for 90 deg.and goes straight for 10ms and stops.\n");
		a = 0;
	    break;
	    }
	    case 2:
	    {
		    printf("Path one contains 2 turns..\n.IT goes straight for 10ms takes a right left for 90deg. the takes a left right for 90 deg.and goes straight for 10ms and stops.\n");
		a = 1;
	    break;
	    }
	    default:
	      printf("wrong input\n");
    }
    printf("Setting motor to initial position.\n");
    for(int i = 0; i<1000;i++ )
    {
      pwmWrite(GPIO_SERVO,150);
    }
		printf("Starting motor...\n");
		delay(2000);
    int arr[2];
    for(int i=0; i<2;i++)
    {
	    arr[i] = ptr[a][i];
    }
    if ( n != 0)
    {
  	for(int j=0;j<2;j++)
  	{
	     if( arr[j] > 150 )
	     {
	      	for(int i = start; i<arr[j];i++)
	      	{
		        pwmWrite(GPIO_SERVO,i);
		        delay(10);
		      }
	      	for(int i = arr[j]; i>=start;i--)
	      	{
		         pwmWrite(GPIO_SERVO,i);
		         delay(4);
	      	}
	     }
	     else
	     {
	        for(int i = start; i>=arr[j];i--)
	      	{
	 	         pwmWrite(GPIO_SERVO,i);
	 	         delay(10);
	      	}
	      	for(int i = arr[j]; i<start;i++)
	      	{
		         pwmWrite(GPIO_SERVO,i);
		         delay(4);
	       	}
	    }
	    delay(3000);
  	}
  	printf("You have reached the location..\n");
  }
  return 0;
}
