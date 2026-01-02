#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include <signal.h>
#include <stdlib.h>
#define RS 25
#define E 24
#define D4 23
#define D5 17
#define D6 18
#define D7 22

#define BK_LT 2
#define COL 16
#define ROW 2
#define BIT_MODE 4
int clcd;
int flag=1;
//int sig_handler(int signo)
void sigintHandler(int sig_num)
{
   flag=0;
 
}

int main()
{
    if(wiringPiSetupGpio() == -1 )
    {
      printf("Setup Failure..\n");
      return -1;
    }

     clcd = lcdInit(ROW,COL,BIT_MODE,RS,E,D4,D5,D6,D7,0,0,0,0); 
    if ( clcd )
    {
      printf("LCD setup failed\n");
      return -1;
    }

    lcdPosition(clcd,0,0);
    lcdPuts(clcd,"  P2F EMPLOYEE  ");
    char str[17] = "Arul and Nishad ";
    str[16] = '\0';
    signal(SIGINT, sigintHandler);
    
    while(flag)
    {
       char temp = str[0];
       for ( int i=0; i<15;i++)
       {
           str[i] = str[i+1];
       }
       str[15] = temp;
       delay(350);
       lcdPosition(clcd,0,1);
       lcdPuts(clcd,str);
    }

    if(!flag)
    {
    
      lcdPosition(clcd,0,0);
      lcdPuts(clcd,"       CLEAR         ");
      lcdPosition(clcd,0,1);
      lcdPuts(clcd,"       CLEAR         ");
      delay(500);
      lcdClear(clcd);
    }
    return 0;
}
