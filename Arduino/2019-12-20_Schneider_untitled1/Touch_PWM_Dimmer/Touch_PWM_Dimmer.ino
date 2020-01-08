#include <ADCTouch.h>

/*
   Capacitive plate dimmer sketch to PWM drive a MOSFET for LED dimming
   by: Frederik Brückner
   date: 2020-01-08
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
int x = 1;
boolean flip = false;

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

if (brightness == 255){
  x = -1;
}

if (brightness == 0){
  x = 1;
}

if (touchTime >= 200 && touch){
  brightness = brightness + x;
  flip = true;
}

if(!touch && flip){
  x = -x;
  flip = false;
}

  touchTime = millis() - lastTouch;
  Serial.println(touchTime);
  Serial.print("Brightness: ");
  Serial.println(brightness);
  Serial.println();
  analogWrite(PWM, brightness);
}
