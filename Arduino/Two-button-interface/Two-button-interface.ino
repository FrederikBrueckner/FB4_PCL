#include <Keyboard.h>

/*
   Maxims Test Interface
   Utilises two buttons and a slider
   by: Frederik Brückner
   date: 2019-01-03
   Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID
   Send keystrokes via USB
*/

static const int leftButton = 9;  // the number of the pushbutton pin
static const int rightButton =  10; // the number of the LED pin
static const int slider = A2;       // the number of the slider pin
static const int threshold = 500; // 500 millis debounce
// variables will change:
volatile int leftState = 0;          // variable for reading the pushbutton status
volatile int rightState = 0;
volatile char lastKey = '0';          // initialize last keypress var
static const char keys[11] =       // char array to hold key stroke values
{'0', '1', '2', '3', '4', '5', '6', '7', '8', 'q', 'w'};

void setup() {
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(slider, INPUT);
  Serial.begin(9600);
  Keyboard.begin();      // Initialize keyboard emulation

} // end setup()

void loop() {
  int slider_value = analogRead(slider);
  Serial.println(slider_value);

  if (slider_value <= 110 && lastKey != keys[0]) {
    lastKey = keys[0];
    Keyboard.print(lastKey);
  }
  else if (slider_value >= 118 && slider_value <= 224 && lastKey != keys[1]) {
    lastKey = keys[1];
    Keyboard.print(lastKey);
  }
  else if (slider_value >= 232 && slider_value <= 338 && lastKey != keys[2]) {
    lastKey = keys[2];
    Keyboard.print(lastKey);
  }
  else if (slider_value >= 346 && slider_value <= 452 && lastKey != keys[3]) {
    lastKey = keys[3];
    Keyboard.print(lastKey);
  }
  else if (slider_value >= 460 && slider_value <= 566 && lastKey != keys[4]) {
    lastKey = keys[4];
    Keyboard.print(lastKey);
  }
  else if (slider_value >= 574 && slider_value <= 680 && lastKey != keys[5]) {
    lastKey = keys[5];
    Keyboard.print(lastKey);
  }
  else if (slider_value >= 688 && slider_value <= 794 && lastKey != keys[6]) {
    lastKey = keys[6];
    Keyboard.print(lastKey);
  }
  else if (slider_value >= 802 && slider_value <= 908 && lastKey != keys[7]) {
    lastKey = keys[7];
    Keyboard.print(lastKey);
  }
  else if (slider_value >= 916 && lastKey != keys[8]) {
    lastKey = keys[8];
    Keyboard.print(lastKey);
  }

  // read the state of the pushbutton value:
  rightState = digitalRead(rightButton);
  leftState = digitalRead(leftButton);
  // check if the pushbutton is pressed.

  // if it is, the buttonState is HIGH:

  if (leftState == LOW) {   // key pressed?
    Keyboard.press(keys[9]);
  }

  if (leftState == HIGH) {  // left button released?
    Keyboard.release(keys[9]);
  }

  if (rightState == LOW) {   // right button pressed?
    Keyboard.press(keys[10]);
  }

  if (rightState == HIGH) { // right button released?
    Keyboard.release(keys[10]);
  }
} // end loop()
