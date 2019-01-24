
/*
   UX-belt sketch to PWM drive a motor via MOSFET from microphone input
   by: Frederik Brückner
   date: 2019-01-16
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
   Recommended MOSFET: IRL540
*/

const int mikro[4] = {A0, A2, A1, A3}; // Mikrofon 1 A0 Violett vorne links, Mikrofon 2 A2 Weiß hinten links, Mikrofon 3 A1 Schwarz hinten rechts, Mikrofon 4 A3 Gelb vorne rechts
const int vibro[4] = {5, 6, 9, 10}; // Vibrationsmotor 1 P5 vorne links , Vibrationsmotor 2 P6 hinten links, Vibrationsmotor 3 P9 hinten rechts, Vibrationsmotor 4 P10 vorne rechts
const int threshold = 600;  // loudness threshold
const int hold = 500;       // delay timing variable
volatile int loudness[4] = {0, 0, 0, 0};
volatile int value[4] = {0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i <= 3; i++) pinMode(vibro[i], OUTPUT); // set pins as output
} // end setup()

void loop() {
  for (int i = 0; i <= 3; i++) {
    loudness[i] = analogRead(mikro[i]);  // read current loudness level
    value[i] = loudness;
    Serial.println(value[i]);
    if (value[i] > threshold) {
      for ( int x = 0 ; x < 154 ; x++ ) {
        analogWrite(vibro[i] , x);
      }
      delay(hold);
      analogWrite(vibro[i] , LOW );

      Serial.println("ON");
    }
    else
      digitalWrite(vibro[i], LOW);
    Serial.println("OFF");
  }
} // end loop()
