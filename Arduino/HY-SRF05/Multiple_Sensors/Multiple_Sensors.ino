#include <Keyboard.h>

/*
 * Multiple HY-SRF05 ultrasonic distance sensors
 * by: Frederik Brückner
 * date: 2018-12-21
 * Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID
 * Send keystrokes depending on measured distance
 */

const unsigned int sens_ping[] = {2, 4, 6, 8, 14}; // HY-SRF05 trigger pins
const unsigned int sens_pong[] = {3, 5, 7, 9, 15}; // HY-SRF05 echo pins
const int near = 50; // Triggering distance 50cm 
const int far = 150; // Triggering distance 150cm
char lastZone = ' '; // Outer zone A, far zone B, near zone C 
char activeZone ='A';// Zone to change to
volatile int minDist = 999;
const int numSense = 5; // Number of connected sensors

long duration; // Time between trigger and echo
volatile int distance, sens[numSense]; // Calculated distance in cm, last distance per sensor

void setup() {
  Serial.begin (9600);
  Keyboard.begin();
  for (int i=0; i < numSense; i++){ // Setup outputs and inputs (Arrays are zero indexed!)
    pinMode(sens_ping[i], OUTPUT);
    pinMode(sens_pong[i], INPUT);
  }
} // End setup
 
void loop() {
  for (int i = 0; i < numSense; i++){ // Take measurements for each sensor
    measure(sens_ping[i], sens_pong[i]);
    sens[i] = distance;
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(sens[i]);
    Serial.println(" cm");
  }
  minDistance();
  if (minDist <= far && minDist > near+10) {
    activeZone = 'B';
  }  
  else if (minDist < near) {
      activeZone = 'C';
  }
  else {
      activeZone = 'A';
  }
  if (activeZone != lastZone) {
    Keyboard.print(activeZone);
    lastZone = activeZone;
  }
  Serial.print(activeZone);
  Serial.print(minDist);
} // End loop
 
void measure(int trigPin,int echoPin) { // Perform measurement and scale to centimeter
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 30000L);  // Wait for echo, timeout after 15000 microseconds -> max. 257cm sens distance
  if (duration == 0){
    distance = 999;
  }
  else {
    distance = (duration/2) / 29.1; // Scale to cm
  }
} // End measure

void minDistance() {
  int minD = 5000;
  int minIndex = -1;
  for (int i = 0; i< numSense; i++){
    if (sens[i] < minD){
      minD = sens[i];
      minIndex = i;
    }
  }
  minDist = minD;
} // End minDistance

