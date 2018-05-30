#include <CapacitiveSensor.h>
#include <Keyboard.h>
//#include <Mouse.h>


/*
 * Simple capacitive touch board
 * Utilises »CapacitiveSensor« library by Paul Badger and Paul Stoffregen
 * by: Frederik Brückner
 * date: 2018-01-14
 * Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID
 * Send keystrokes with touch electrodes
 */

boolean debug = false;              // debug mode enable/disable
const int threshold = 500;          // sensitivity threshhold for touch detection
const int numSense = 10;            // number of sensors
const int sampleLength = 80;        // sample length in bytes
const int activePin = 3;            // pin for sensor activation
volatile long senseArray[numSense]; // sensor value array
unsigned long debounceDelay = 20;   // software debounce time
unsigned long lastTouch = 0;        // when did the last touch register

volatile boolean touched[numSense]  // keep track of touched state
{
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false
};

CapacitiveSensor CS[numSense] =     // sensor object array 1M resistor between pins 2 & sensor pin, add a wire and or foil
{
  CapacitiveSensor(activePin,5),
  CapacitiveSensor(activePin,6),
  CapacitiveSensor(activePin,7),
  CapacitiveSensor(activePin,8),
  CapacitiveSensor(activePin,9),
  CapacitiveSensor(activePin,10),
  CapacitiveSensor(activePin,16),
  CapacitiveSensor(activePin,14),
  CapacitiveSensor(activePin,15),
  CapacitiveSensor(activePin,A0)
};

char keys[numSense] =               // char array to hold key stroke values
{
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  '0'
};

void setup()
{
  if (debug){
    Serial.begin(9600);
  }
   Keyboard.begin();
   //Mouse.begin();
   lastTouch = millis();
} // end setup

void loop()                    
{
  unsigned long start = millis();
  for (int i=0; i<numSense; i++){
  senseArray[i] = CS[i].capacitiveSensor(sampleLength);
  }
  if (debug){
    Serial.print(millis() - start); // check on performance in milliseconds
    Serial.println("\t");           // tab character for debug windown spacing
    for (int i=0; i<numSense; i++){
      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print("= ");
      Serial.println(senseArray[i]);  // print sensor output
    }
    delay(10);                      // arbitrary delay to limit data to serial port 
  } // end debug
  
  for (int i=0; i<numSense; i++){
    if (senseArray[i] >= threshold && (millis() - lastTouch) > debounceDelay && !touched[i]){
      lastTouch = millis();
      Keyboard.press(keys[i]);
      touched[i] = !touched[i];
    }
    else if (senseArray[i] < threshold && touched[i]){
      Keyboard.release(keys[i]);
      touched[i] = !touched[i];
    }
  }
} // end loop


