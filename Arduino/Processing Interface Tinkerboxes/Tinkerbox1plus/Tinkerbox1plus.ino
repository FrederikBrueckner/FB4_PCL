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
const int selUp = 14;
const int selDown = 15;
int sensorValue = 0;  // variable to store the value coming from the potentiometer
boolean swState = false;  // variable to store switch state
boolean up = false;
boolean down = false;

void setup() {
  Serial.begin(9600); // setup serial connection, 9600 baud
  pinMode(swPin, INPUT_PULLUP); // configure switch input pin
  pinMode(selUp, INPUT_PULLUP);
  pinMode (selDown, INPUT_PULLUP);
} // end setup()

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);  // sensor values: 0-1023
  swState = digitalRead(swPin);  // true or false
  up = !digitalRead(selUp);
  down = !digitalRead(selDown);
  char buf[16];  // message of up to 15 chars plus zero character
  sprintf(buf, "%04u:%01u:%01u:%01u", sensorValue, swState, up, down); // send potentiometer read value as 4 digit, send switch state as 1 digit
  Serial.println(buf);
} // end loop()
