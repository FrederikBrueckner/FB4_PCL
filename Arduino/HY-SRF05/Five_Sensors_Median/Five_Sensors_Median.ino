#include <NewPing.h>
#include <Keyboard.h>

/*
 * Five HY-SRF05 ultrasonic distance sensors
 * Utilises »New Ping« library with median filter
 * by: Frederik Brückner
 * date: 2018-01-11
 * Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID
 * Send keystrokes to activate "zones" depending on measured distance
 */

#define SONAR_NUM 5      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

unsigned int sensDist[SONAR_NUM]; // Store ping distance in cm per sensor
const int near = 50; // Triggering distance 50cm 
const int far = 150; // Triggering distance 150cm
char lastZone = ' '; // Outer zone A, far zone B, near zone C 
char activeZone ='A';// Zone to change to
volatile int minDist = 999;

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(2, 3, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(4, 5, MAX_DISTANCE), 
  NewPing(6, 7, MAX_DISTANCE),
  NewPing(8, 9, MAX_DISTANCE), 
  NewPing(14, 15, MAX_DISTANCE)
};

void setup() {
Keyboard.begin();
} // End setup

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    sensDist[i]=sonar[i].ping_median()/US_ROUNDTRIP_CM;
  }
    minDistance();
} // End loop

void minDistance() {
  int minD = 5000;
  for (int i = 0; i< SONAR_NUM; i++){
    if (sensDist[i] < minD && sensDist[i] !=0){
      minD = sensDist[i];
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
} // End minDistance

