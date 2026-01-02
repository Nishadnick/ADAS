#include<stdio.h>
#include<wiringPi.h>
#define STEER 18

void display()
{
  printf("Enter choise\n");
  printf("s for straight\n");
  printf("l for left\n");
  printf("r for right\n");
}

int main(void)
{
    wiringPiSetupGpio();
//    pinMode(18,OUTPUT);
    pinMode(STEER, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);
    pwmSetClock(192);
//    int angle=150;
    char choise='s';
    
    while(1)
    {
        display();
        if(choise=='s')
        {printf("Straight\n");
        pwmWrite(STEER, 45);
        printf("go ahead??\n");
       // getchar();
        }
        else if(choise=='l')
        {printf("Left\n");
        pwmWrite(STEER, 45);}
        else if(choise=='r')
        {printf("Right\n");
        pwmWrite(STEER, 245);}
        getchar();
        scanf("%c",&choise);
    }
    return 0;
}
