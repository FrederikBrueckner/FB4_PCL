/*
   Multi-press button sketch to PWM drive a MOSFET for constant voltage LED strip dimming
   by: Frederik Brückner
   date: 2018-12-17
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
   Recommended MOSFET: IRL540
*/


volatile int count;               // Count button presses
volatile int currentBrightness;   // Keep track of last brightness level
volatile int setLevel;            // Set new target brightness
#define BUTTON 2                  // Input button on pin 2
#define PWM 5                     // PWM pin to drive MOSFET on pin 5
const int full = 255;             // Configure brightness levels
const int mid = 127;
const int low = 60;
const int fadeSpeed = 50;       // Fade speed between brightness levels
volatile boolean state = false;   // Should the MOSFET be powered?
unsigned long time;               // Keep track of loop time
unsigned long lastFade;

void setup() {
  count = 0;                      // Initialize button press counter
  currentBrightness = 0;          // Initialize brightness to zero
  setLevel = 0;                   // Initialize target brightness
  pinMode(BUTTON, INPUT_PULLUP);  // Enable "button" as input pin, internal pull up
  pinMode(PWM, OUTPUT);           // Enable "PWM" as output pin
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPressed, FALLING); // Call interrupt routine on falling edge
  lastFade = 0;
  analogWrite(PWM, setLevel);

  // Set PWM frequency prescaler for D5 & D6
  // CAUTION! Changing timer 0 Changing the prescale factor on Timer0 will affect functions millis(), micros(), delay(),...
  TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to 8 for PWM frequency of 7812.50 Hz (8000 millis ~ 1 second)

} //end setup

void loop() {
  time = millis();
  if (state) {
    switch (count) {
      case 1: // Full on
        setLevel = full;
        break;
      case 2: // Medium on
        setLevel = mid;
        break;
      case 3: // Low on
        setLevel = low;
        break;
    }
  }
  else {
    setLevel = 0;
  }
  fade(setLevel, time);
} // end loop

void buttonPressed() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) {
    if (!state) {
      count = 1;
      state = !state;
    }
    else {
      count = 0;
      state = !state;
    }
  }
  last_interrupt_time = interrupt_time;
} // end buttonPressed

void fade(int Target, unsigned long thisTime) {   // Fade currentLevel to new value
  if (thisTime - lastFade >= fadeSpeed) {
    if (currentBrightness + 1 <= Target) {
      currentBrightness += 1;
    }
    else {
      if (currentBrightness > Target) {
        currentBrightness -= 1;
      }
    }
    analogWrite(PWM, currentBrightness);
    lastFade = thisTime;
  }
} // end fade

