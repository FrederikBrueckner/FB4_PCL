#include <Keyboard.h>
/*
 * Multiple HY-SRF05 ultrasonic distance sensors
 * by: Frederik Brückner
 * date: 2018-12-21
 * Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID
 * Send keystrokes depending on measured distance
 */

const unsigned int sens_ping[] = {2, 4, 6, 8, 10}; // HY-SRF05 trigger pins
const unsigned int sens_pong[] = {3, 5, 7, 9, 11}; // HY-SRF05 echo pins
 
long duration, distance, sens[5];

void setup() {
  Serial.begin (9600);
  Keyboard.begin();
  for (int i=0; i <= 4; i++){ // Setup outputs and inputs (Arrays are zero indexed!)
    pinMode(sens_ping[i], OUTPUT);
    pinMode(sens_pong[i], INPUT);  
    }
} // End setup
 
void loop() {
  for (int i=0; i <= 4; i++){ // Take measurements for each sensor
    measure(sens_ping[i], sens_pong[i]);
    sens[i] = distance;
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(sens[i]);
    Serial.println(" cm");
    }
} // End loop
 
void measure(int trigPin,int echoPin) { // Perform measurement and scale to centimeter
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
} // End measure
