#include <Mouse.h>
#include <Keyboard.h>

/*
 * Maxims Test Interface
 * Utilises two buttons and a slider
 * by: Frederik Brückner
 * date: 2019-01-03
 * Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID
 * Send keystrokes via USB
 */

const int leftButton = 10;  // the number of the pushbutton pin
const int rightButton =  9; // the number of the LED pin
const int slider = 4;       // the number of the slider pin

// variables will change:
int leftState = 0;          // variable for reading the pushbutton status
int rightState = 0;

char lastKey = '0';          // initialize last keypress var

char keys[9] =       // char array to hold key stroke values
{
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8'
};

void setup() {
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  Keyboard.begin();   // Initialize keyboard emulation
  //Mouse.begin();      // Initialize mouse emulation
  Serial.begin(9600);
} // end setup()

void loop() {
  int slider_value = analogRead(slider);

    if (slider_value <= 110 && lastKey != keys[0]){
      lastKey = keys[0];
      Keyboard.print(lastKey);
    }
    else if (slider_value >= 118 && slider_value <= 224 && lastKey != keys[1]){
      lastKey = keys[1];
      Keyboard.print(lastKey);
    }
    else if (slider_value >= 232 && slider_value <= 338 && lastKey != keys[2]){
      lastKey = keys[2];
      Keyboard.print(lastKey);
    }
    else if (slider_value >= 346 && slider_value <= 452 && lastKey != keys[3]){
      lastKey = keys[3];
      Keyboard.print(lastKey);
    }
    else if (slider_value >= 460 && slider_value <= 566 && lastKey != keys[4]){
      lastKey = keys[4];
      Keyboard.print(lastKey);
    }
    else if (slider_value >= 574 && slider_value <= 680 && lastKey != keys[5]){
      lastKey = keys[5];
      Keyboard.print(lastKey);
    }
    else if (slider_value >= 688 && slider_value <= 794 && lastKey != keys[6]){
      lastKey = keys[6];
      Keyboard.print(lastKey);
    }
    else if (slider_value >= 802 && slider_value <= 908 && lastKey != keys[7]){
      lastKey = keys[7];
      Keyboard.print(lastKey);
    }
    else if (slider_value >= 916 && lastKey != keys[8]){
      lastKey = keys[8];
      Keyboard.print(lastKey);
    }

  // read the state of the pushbutton value:
  rightState = digitalRead(rightButton);
  leftState = digitalRead(leftButton);
  // check if the pushbutton is pressed.

  // if it is, the buttonState is HIGH:

  if (leftState == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
      Serial.println("LeftPress");
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
      Serial.println("LeftRelease");
    }
  }

 if (rightState == LOW) {
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
      Serial.println("RightPress");
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
      Serial.println("RightRelease");
    }
  }
} // end loop()
