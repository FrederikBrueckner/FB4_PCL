/*
   Demo code for a simple input device.
   by: Frederik Brückner
   date: 2018-03-12
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.

   Materials used: Arduino Pro Micro, 100kOhm potentiometer (slide or turn), SPST on-off switch, some wire, USB cable, suitable housing
*/

const int sensorPin = A0; // select the input pin for the potentiometer
const int swPin = 5;  // select input pin for the switch
int sensorValue = 0;  // variable to store the value coming from the potentiometer
boolean swState = false;  // variable to store switch state

void setup() {
  Serial.begin(9600); // setup serial connection, 9600 baud
  pinMode(swPin, INPUT_PULLUP); // configure switch input pin
} // end setup()

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);  // sensor values: 0-1023
  swState = !digitalRead(swPin);  // true or false
  char buf[64];  // message of up to 63 chars plus zero character
  sprintf(buf, "%04u:%01u", sensorValue, swState); // send potentiometer read value as 4 digit, send switch state as 1 digit
  Serial.println(buf);
} // end loop()
