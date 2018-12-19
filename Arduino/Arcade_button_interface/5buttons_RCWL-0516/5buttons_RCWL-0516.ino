#include <Keyboard.h>

/*
 * Five buttons and a cheap microwave doppler radar sensor
 * by: Frederik Brückner
 * date: 2018-07-16
 * Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID
 * Send keystrokes with buttons and a motion sensor
 */

volatile boolean flag = false; // keep track of motion detection
static const int radar = A0; // input pin for RCWL-0516
static const int numButtons = 5; // number of buttons
static const int button[numButtons] = {  // input pins for buttons
  2, 3, 4, 5, 6
};

static const char keys[numButtons + 1] = { // char array to hold keys
  '1', '2', '3', 'x', '0', 'm'
};

volatile boolean pressed[numButtons] { // keep track of button states
  false, false, false, false, false
};

static const unsigned long debounceDelay = 50; // software debounce buttons
volatile unsigned long lastPress[numButtons] = { // when did the last button press register
  0, 0, 0, 0, 0
};

void setup() {
  Keyboard.begin(); // start keyboard emulator
  pinMode(radar, INPUT); // configure radar input pin
  for (int i = 0; i < numButtons; i++) { // configure button pins
    pinMode(button[i], INPUT_PULLUP);
    lastPress[i] = millis(); // time tracking for debouncing
  }
} // end setup

void loop() {
  if (digitalRead(radar) && !flag) {  // register change of radar state
    Keyboard.print(keys[5]);
    flag = true;
  }
  if (!digitalRead(radar)) {  // reset radar state
    flag = false;
  }
  for (int i = 0; i < numButtons; i++) {  // read button states
    if (!digitalRead(button[i]) && (millis() - lastPress[i]) > debounceDelay && !pressed[i]) { // send key press from buttons
      lastPress[i] = millis(); // reset debounce timer
      Keyboard.press(keys[i]);
      pressed[i] = !pressed[i];
    }
    else if (digitalRead(button[i]) && (millis() - lastPress[i]) > debounceDelay && pressed[i]) {  // release key press from buttons
      Keyboard.release(keys[i]);
      pressed[i] = !pressed[i];
    }
  }
} //end loop

