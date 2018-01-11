#include <NewPing.h>
#include <Keyboard.h>

/*
 * Multiple HY-SRF05 ultrasonic distance sensors
 * Rewrite to utilise »New Ping« library with median filter
 * by: Frederik Brückner
 * date: 2018-01-10
 * Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID
 * Send keystrokes depending on measured distance
 */

//const unsigned int sens_ping[] = {2, 4, 6, 8, 14}; // HY-SRF05 trigger pins
//const unsigned int sens_pong[] = {3, 5, 7, 9, 15}; // HY-SRF05 echo pins
const int near = 50; // Triggering distance 50cm 
const int far = 150; // Triggering distance 150cm
const int maxDist = 200; // Timeout for everything further away
char lastZone = ' '; // Outer zone A, far zone B, near zone C 
char activeZone ='A';// Zone to change to
volatile int minDist = 999;
const int numSens = 5; // Number of connected sensors
const int pingInterval = 150;
unsigned long pingTimer[numSens]; // Time between trigger and echo
unsigned int sensDist[numSens]; // Store ping distance in cm per sensor
uint8_t currentSensor = 0;  // Which sensor is active?

NewPing sonar[numSens] = {
  NewPing(2, 3, maxDist),
  NewPing(4, 5, maxDist),
  NewPing(6, 7, maxDist),
  NewPing(8, 9, maxDist),
  NewPing(14, 15, maxDist)
};

void setup() {
  Serial.begin (9600);
  Keyboard.begin();
  pingTimer[0] = millis() + 75;  // First ping start in ms
  for (uint8_t i = 1; i < numSens; i++){
    pingTimer[i] = pingTimer[i-1]+pingInterval;
  }
} // End setup
 
void loop() {
  for (uint8_t i = 0; i < numSens; i++){ // Take measurements for each sensor
    if (millis() >= pingTimer[i]){
      pingTimer[i] += pingInterval*numSens;
      if (i == 0 && currentSensor == numSens - 1){
        oneSensorCycle(); 
      }
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      sensDist[currentSensor]=0;
      sonar[currentSensor].ping_timer(echoCheck);
    }
    
  }
  
} // End loop
 
void oneSensorCycle(){
  /*for (uint8_t i = 0; i < numSens; i++){
    Serial.print(i);
    Serial.print("=");
    Serial.print(sensDist[i]);
    Serial.print("cm ");
  }
  Serial.println();*/
  minDistance();
  
} // End oneSensorCycle

void echoCheck(){
  if(sonar[currentSensor].check_timer()){
    sensDist[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
  }
} // End echoCheck

void minDistance() {
  int minD = 5000;
  int minIndex = -1;
  for (int i = 0; i< numSens; i++){
    if (sensDist[i] < minD && sensDist[i] !=0){
      minD = sensDist[i];
      minIndex = i;
    }
  }
  minDist = minD;
   if (minDist <= far && minDist > near) {
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
  Serial.println();
  Serial.print(minDist);
  Serial.println();
} // End minDistance

