#include <wiringPi.h>
int main (void)
{
  wiringPiSetup () ;
  pinMode (12, OUTPUT) ;
  for (;;)
  {
    digitalWrite (12, HIGH) ; delay (2000) ;
    digitalWrite (12,  LOW) ; delay (2000) ;
  }
  return 0 ;
}
