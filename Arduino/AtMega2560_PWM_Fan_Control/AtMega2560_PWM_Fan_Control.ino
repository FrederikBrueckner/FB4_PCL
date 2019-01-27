#include <TimerThree.h>

const int fan[3] = {2, 3, 5};
const int pot[3] = {A0, A1, A2};

void setup(void)
{
 Timer3.initialize(40);  // 40 us = 25 kHz
  Timer3.pwm(fan[0], 0);
  Timer3.pwm(fan[1], 0);
  Timer3.pwm(fan[2], 0);
  //Serial.begin(9600);
  
  /*analogWrite(fan[0],0);
  analogWrite(fan[1],0);
  analogWrite(fan[2],0);
  */
} // end setup()

void loop(void)
{
  for (int i = 0; i <= 2; i++)
  {
    Timer3.pwm(fan[i], analogRead(pot[0]));
    //analogWrite(fan[i], analogRead(pot[0]));
    delay(analogRead(pot[1]) * 5);
    Timer3.pwm(fan[i],0);
    //analogWrite(fan[i], 0);
    delay(analogRead(pot[2]) * 10);
  }
} // end loop()
