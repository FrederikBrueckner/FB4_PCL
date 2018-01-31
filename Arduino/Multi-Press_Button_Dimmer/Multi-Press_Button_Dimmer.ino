/*
   Multi-press button sketch to PWM drive a MOSFET for constant voltage LED strip dimming
   by: Frederik Brückner
   date: 2018-12-22
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
   Recommended MOSFET: IRL540
*/

volatile int count = 0;				// Count button presses, initialize to zero
volatile int currentBrightness = 0;	// Keep track of last brightness level, initialize to zero
volatile int setLevel = 0;			// Set new target brightness, initialize to zero
const int BUTTON = 2;				// Input button on pin 2
const int PWM = 5;					// PWM pin to drive MOSFET on pin 5
const int full = 255;				// Configure brightness levels
const int mid = 80;
const int low = 10;
const int fadeSpeed = 25;			// Fade speed between brightness levels
const int timeOut = 8000;			// Time frame for multi-click detection
const int longClick = 8000;			// Hold button down for long click
volatile boolean state = false;		// Should the MOSFET be powered?
unsigned long time;					// Keep track of loop time
unsigned long lastFade;				// Keep track of fading time

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);		// Enable "button" as input pin, internal pull up
  pinMode(PWM, OUTPUT);				// Enable "PWM" as output pin
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPressed, FALLING);	// Call interrupt routine on falling edge
  lastFade = 0;						// Initialize to zero
  analogWrite(PWM, setLevel);		// Set PWM output to zero

  // Set PWM frequency prescaler for D5 & D6
  // CAUTION! Changing timer 0 by changing the prescale factor on Timer0 will affect functions millis(), micros(), delay(),...
  TCCR0B = TCCR0B & B11111000 | B00000010;		// set timer 0 divisor to 8 for PWM frequency of 7812.50 Hz (8000 millis ~ 1 second)
} //end setup

void loop() {
  time = millis();	// Global time keeping
  switch (count) {	// Finite state machine to set brightness target levels
    case 0:			// Off
      setLevel = 0;
      break;
    case 1:			// Low on
      setLevel = low;
      break;
    case 2:			// Medium on
      setLevel = mid;
      break;
    case 3:			// Full on
      setLevel = full;
      break;
  }
  fade(setLevel, time);
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

void fade(int Target, unsigned long thisTime) {	// Fade currentLevel to new value
  if (thisTime - lastFade >= fadeSpeed) {
    if (currentBrightness + 1 <= Target) {
      currentBrightness += 1;					// Increment currentBrightness
    }
    else if (currentBrightness > Target) {
        currentBrightness -= 1;					// Decrement currentBrightness
    }
    analogWrite(PWM, currentBrightness);			// Set new brightness level
    lastFade = thisTime;							// Reset fade delay
  }
} // end fade

