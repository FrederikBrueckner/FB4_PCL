#include <ADCTouch.h>

/*
   Capacitive plate dimmer sketch to PWM drive two MOSFETs for constant voltage LED strip dimming
   by: Frederik Brückner
   date: 2019-01-16
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
   Recommended MOSFET: IRL540
*/

volatile int count = 0;				    // Count button presses, initialize to zero
volatile int currentBrightness1 = 0;	// Keep track of last brightness level, initialize to zero
volatile int currentBrightness2 = 0;
volatile int setLevel1 = 0;			  // Set new target brightness, initialize to zero
volatile int setLevel2 = 0;
int ref0;
boolean BUTTON;     				      // Input button on pin 2
const int PWM1 = 6;					      // PWM pin to drive MOSFET on pin 5
const int PWM2 = 5;               // PWM pin to drive MOSFET on pin 6
const int full = 255;				      // Configure brightness levels
const int mid = 140;
const int low = 60;
const int fadeSpeed = 25;			    // Fade speed between brightness levels
const int threshold = 500;        // sensitivity threshhold for touch detection
long sense;                       // sensor value array
unsigned long debounceDelay = 20; // software debounce time
unsigned long lastTouch = 0;      // when did the last touch register
volatile boolean state = false;		// Should the MOSFET be powered?
unsigned long time;					      // Keep track of loop time
unsigned long lastFade;				    // Keep track of fading time

void setup() {
  Serial.begin(9600);
  ref0 = ADCTouch.read(A0, 800);    //create reference values to 
  pinMode(PWM1, OUTPUT);				// Enable "PWM" as output pin
  pinMode(PWM2, OUTPUT);        // Enable "PWM" as output pin
  lastFade = 0;						// Initialize to zero
  analogWrite(PWM1, setLevel1);		// Set PWM1 output to zero
  analogWrite(PWM2, setLevel2);    // Set PWM2 output to zero
  // Set PWM frequency prescaler for D5 & D6
  // CAUTION! Changing timer 0 by changing the prescale factor on Timer0 will affect functions millis(), micros(), delay(),...
  TCCR0B = TCCR0B & B11111000 | B00000010;		// set timer 0 divisor to 8 for PWM frequency of 7812.50 Hz (8000 millis ~ 1 second)
  lastTouch = millis();
} //end setup

void loop() {
  sense = ADCTouch.read(A0);
  Serial.println(sense);
  if (sense < threshold && (millis() - lastTouch) > debounceDelay){
      lastTouch = millis();
      buttonPressed();
    }
  
  time = millis();	// Global time keeping
  switch (count) {	// Finite state machine to set brightness target levels
    case 0:			// Off
      setLevel1 = 0;
      setLevel2 = 0;
      break;
    case 1:			// Low on
      setLevel1 = full;
      setLevel2 = full;
      break;
    case 2:			// Medium on
      setLevel1 = low;
      setLevel2 = mid;
      break;
    case 3:			// Full on
      setLevel1 = 0;
      setLevel2 = low;
      break;
  }
  fade(setLevel1, setLevel2, time);
} // end loop

void buttonPressed() {
  static unsigned long lastInterrupt = 0;		// Time since last interrupt occurred
  unsigned long interruptTime = millis();		// Time when interrupt occurred
  // If interrupts come faster than 200ms, assume it's a bounce and ignore --> PWM prescaler fix x8
  if (interruptTime - lastInterrupt > 1600) {	// Count three button presses and roll over
    if (count >= 0 && count <3) {
      lastInterrupt = interruptTime;				// Reset debounce timer
      count++;
    }
    else if (count == 3) {						// If count exceeds 3, roll over to zero
      lastInterrupt = interruptTime;				// Reset debounce timer
      count = 0;
    }
  }
} // end buttonPressed

void fade(int Target1, int Target2, unsigned long thisTime) {  // Fade currentLevel to new value
  if (thisTime - lastFade >= fadeSpeed) {
    if (currentBrightness1 + 1 <= Target1) {
      currentBrightness1 += 1;          // Increment currentBrightness
    }
    else if (currentBrightness1 > Target1) {
        currentBrightness1 -= 1;        // Decrement currentBrightness
    }
    if (currentBrightness2 + 1 <= Target2) {
      currentBrightness2 += 1;          // Increment currentBrightness
    } 
    else if (currentBrightness2 > Target2) {
        currentBrightness2 -= 1;        // Decrement currentBrightness
    }
    analogWrite(PWM1, currentBrightness1);      // Set new brightness level
    analogWrite(PWM2, currentBrightness2);
    lastFade = thisTime;                // Reset fade delay
  }
} // end fade

