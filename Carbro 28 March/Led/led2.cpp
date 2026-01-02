#include<iostream>
#include <wiringPi.h>

int main (void)
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
std::cout<<"RUNNING..........C++\n";  
for (;;)
  {
    digitalWrite (0, HIGH) ; delay (500) ;
    digitalWrite (0,  LOW) ; delay (500) ;
  }
  return 0 ;
}
