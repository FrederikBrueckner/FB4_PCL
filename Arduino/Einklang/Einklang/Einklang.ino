/*
   Three slide potentiometer input device.
   by: Frederik Brückner
   date: 2018-06-26
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
*/

const int S1_freq = A0; // Pin für Slider
const int S2_freq = A1;
const int S3_freq = A2;

volatile int S1 = 0;
volatile int S2 = 0;
volatile int S3 = 0;


void setup() {
  Serial.begin(9600);  // Serielle Schnittstelle initialisieren

}

void loop() {
  S1 = analogRead(S1_freq);
  S2 = analogRead(S2_freq);
  S3 = analogRead(S3_freq);
  char buf[16];
  sprintf(buf, "%04u:%04u:%04u", S1, S2, S3);
  Serial.println(buf);

}
