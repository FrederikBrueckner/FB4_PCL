#include <ADCTouch.h>

/*
   Capacitive plate dimmer sketch to PWM drive two MOSFETs for constant voltage LED strip dimming
   by: Frederik Brückner
   date: 2019-01-16
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
   Recommended MOSFET: IRL540
*/

int ref0;
int PWM = 5;  //Steuerpin für MOSFET
int sense;
int threshold = 200;
boolean touch = false;
unsigned long lastTouch;
unsigned long time;
unsigned long touchTime;
int brightness = 0;

void setup() {
  Serial.begin(9600);
  delay(500);
  ref0 = ADCTouch.read(A0, 500);
  pinMode(PWM, OUTPUT);
  lastTouch = millis();
  touchTime = 0;
}

void loop() {
  sense = ADCTouch.read(A0) - ref0;
  //Serial.println(sense);
  if (sense > threshold && !touch) {
    Serial.println("Kontakt!");
    touch = true;
  }

  if (sense < threshold) {
    touch = false;
    lastTouch = millis();
  }

  if (touchTime > 10 && touchTime < 200 && brightness == 0 && !touch){
    brightness = 255;
    Serial.println("on");
    lastTouch = millis();
    touchTime = 0;
  }
  if (touchTime > 10 && touchTime < 200 && brightness > 0 && !touch){
    brightness = 0;
    Serial.println("off");
    lastTouch = millis();
    touchTime = 0;
  }

  touchTime = millis() - lastTouch;
  Serial.println(touchTime);
  analogWrite(PWM, brightness);
}
