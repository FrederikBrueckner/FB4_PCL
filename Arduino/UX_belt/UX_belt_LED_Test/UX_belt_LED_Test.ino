<<<<<<< HEAD
const int mikrofon = A0; // Variable für Mikrofon Eingang
const int grenze = 600;
const int led = 7;
const int dauer = 1500;
=======
/*
   UX-belt sketch to PWM drive a motor via MOSFET from microphone input
   by: Frederik Brückner
   date: 2019-01-16
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
   Recommended MOSFET: IRL540
*/

const int microphone = A6;  // mikrophone sensor input
const int threshold = 600;  // loudness threshold
const int motor = 3;        // vibration motor driver pin
const int hold = 500;       // delay timing variable
>>>>>>> bfdfeaea45ed696914004ae020083392e09a1243

void setup() {
Serial.begin(9600);
pinMode(motor, OUTPUT);
} // end setup()

void loop() {
int loudness = analogRead(microphone);  // read current loudness level
int value = loudness;
Serial.println(value);
if(value>threshold){
  for( int x = 0 ; x < 154 ; x++ ) {
    analogWrite(motor , x);
    }
    delay(hold);
    analogWrite( 6 , 0 );

  Serial.println("ON");
  }
  else
  digitalWrite(motor, LOW);
  Serial.println("OFF");
} // end loop()
