/*
 * Demo code for a simple input device.
 * by: Frederik Brückner
 * date: 2018-03-12
 * license: MIT License - Feel free to use this code for any purpose.
 * No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
 */

const int sensorPin = A0; // select the input pin for the potentiometer
const int swPin = 5;  // select the input pin for the switch
int sensorValue = 0;  // variable to store the value coming from the sensor
boolean swState = false;

void setup() {
  Serial.begin(9600);
  pinMode(swPin, INPUT_PULLUP); // configure switch input pin
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);  // sensor values: 0-1023
  swState = !digitalRead(swPin);  // true or false
  char buf[64];  // message of up to 63 chars plus zero character
  sprintf(buf, "%04u:%01u", sensorValue, swState); // "gest:%02u touch:%02u" , Skywriter.last_gesture, Skywriter.last_touch
  Serial.println(buf);
}
