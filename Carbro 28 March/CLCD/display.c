#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>

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

int main()
{
    if(wiringPiSetupGpio() == -1 )
    {
      printf("Setup Failure..\n");
      return -1;
    }

    int clcd = lcdInit(ROW,COL,BIT_MODE,RS,E,D4,D5,D6,D7,0,0,0,0); 
    if ( clcd )
    {
      printf("LCD setup failed\n");
      return -1;
    }

    lcdPosition(clcd,0,0);
    lcdPuts(clcd,"  P2F EMPLOYEE  ");

    lcdPosition(clcd,0,1);
    lcdPuts(clcd," Arul & Nishad ");

    getchar();
    lcdClear(clcd);
    return 0;
}
