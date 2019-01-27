/*
   UX-belt sketch to PWM drive 4 motors via MOSFETs from microphone inputs
   by: Frederik Brückner
   date: 2019-01-16
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
   Recommended MOSFET: IRL540
*/

const int numSense = 4; // number of connected devices
const int mic[numSense] = {A0, A2, A1, A3}; // Mic 1 A0 violet front left, Mic 2 A2 white back left, Mic 3 A1 black back right, Mic 4 A3 yellow front right
const int vibro[numSense] = {5, 6, 9, 10}; // V-motor 1 P5 front left , V-motor 2 P6 back left, V-motor 3 P9 back right, V-motor 4 P10 front right
int offset[numSense] = {};  // compensate DC offset
volatile int value[numSense] = {0, 0, 0, 0};  // variable to hold working values
const int threshold = 250;  // noise threshold (0 - 512)
const int hold = 200;     // motor keep alive delay
const int full = 128;     // max PWM for motor (0 - 255)
volatile int loudness[numSense] = {0, 0, 0, 0}; // variable holding current value

void setup() {
  Serial.begin(9600);
  delay(1000);    // wait for things to settle
  for (int i = 0; i < numSense; i++) {  // initiated array
    offset[i] = analogRead(mic[i]);
  }
  for (int i = 0; i < numSense; i++) {
    pinMode(vibro[i], OUTPUT); // set PWM pins as output
    pinMode(mic[i], INPUT); // set analog pins as input
    for (int k = 0; k <= 5; k++) {  // low pass filter analog values to save as offset
      offset[i] = offset[i] * 0.8 + analogRead(mic[i]) * 0.2;
    }
    analogWrite(vibro[i], 0); // switch outputs off
  }
} // end setup()

void loop() {
  for (int i = 0; i < numSense; i++) {
    loudness[i] = analogRead(mic[i]);  // read current loudness level
    value[i] = abs(loudness[i] - offset[i]);
    if (Serial) { // if serial port is available
      Serial.print ("Microphone ");
      Serial.print (i);
      Serial.print (" = ");
      Serial.println (value[i]);
      Serial.print ("Offset value ");
      Serial.print(i);
      Serial.print(" = ");
      Serial.println(offset[i]);
    }
  }
  int maxI = 0;
  for (int i = 0; i < numSense; i++) {  // look for biggest value in array
    if (value[i] > value[maxI]) maxI = i;
  }
  if (value[maxI] > threshold) {  // if max value is bigger than threshold
    analogWrite(vibro[maxI] , full);
    delay(hold);
  }
  for (int i = 0; i < numSense; i++) {  // switch all motors off, reset working values
    analogWrite(vibro[i] , 0);
    value[i] = 0;
  }
} // end loop()
