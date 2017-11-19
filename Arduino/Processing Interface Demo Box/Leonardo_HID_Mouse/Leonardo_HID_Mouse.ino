#include <Mouse.h>         // Arduino mouse emulation
#include <Arduino.h>       // Arduino standard libraries
#include <TM1637Display.h> // LED segment display library by avishorp https://github.com/avishorp
#include <Rotary.h>        // rotary encoder library by Ben »Buxtronix« Buxton https://github.com/buxtronix

#define CLK 10 // TM1637 CLK PIN
#define DIO 9  // TM1637 DIO PIN 

// Create display object
TM1637Display display(CLK, DIO); 

// Rotary encoder is wired with the common to ground and the two outputs to pins 2 and 3.
Rotary rotary = Rotary(2, 3);

/* Leonardo HID Joystick Mouse Encoder and Keyboard
   by: Frederik Brückner
   date: 2018-11-18
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this
   code in your future endeavors! Reuse and share.
 
   Based on Code examples by Jim Lindblom for SparkFun Electronics
   Thumb Joystick to HID Mouse. The select button on the joystick is set up
   as the mouse left click. Rotary encoder counts up and down, reset via encoder click.
 */
 
// -----------------------------------------------------------------------------
// constants

const int               PinSW    = 7;         // used for the rotary push button switch
const int               sensitivity = 100;    // higher sensitivity value = slower mouse, should be <= 500


// -----------------------------------------------------------------------------
// global vars

volatile int            virtualPosition = 0;
int                     horzPin = A0;          // analog output of horizontal joystick pin
int                     vertPin = A1;          // analog output of vertical joystick pin
int                     selPin = 8;            // select button pin of joystick
int                     vertZero, horzZero;    // stores the initial value of each axis, usually around 512
int                     vertValue, horzValue;  // stores current analog output of each axis
int                     mouseClickFlag = 0;

// -----------------------------------------------------------------------------
// forward declarations

void rotate();
void loop();
void setup();

// -----------------------------------------------------------------------------
// interrupt service routine is executed when a HIGH to LOW transition is detected on CLK

void rotate()  {
  unsigned char result = rotary.process();
    if (result == DIR_CW) {
      virtualPosition++;
    } else if (result == DIR_CCW) {
      virtualPosition--;
      }
    
    } // rotate

// -----------------------------------------------------------------------------
// setup

void setup()
{ 
  Serial.begin(57600);
  pinMode(horzPin, INPUT);    // joystick X
  pinMode(vertPin, INPUT);    // joystick Y
  pinMode(selPin, INPUT);     // joystick click
  pinMode(PinSW, INPUT);      // rotary encoder click
  digitalWrite(selPin, HIGH); // pull button select pin high
  delay(1000);                // short delay to let outputs settle
  vertZero = analogRead(vertPin);  // get the initial values
  horzZero = analogRead(horzPin);  // joystick should be in neutral position when reading these

  attachInterrupt(0, rotate, CHANGE);
  attachInterrupt(1, rotate, CHANGE);   // interrupt 1 == pin 2, interrupt 0 == pin 3 on Arduino Leonardo

  Serial.println("Start");

  display.setBrightness(15);
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff }; // all segments on
  
  // set display segments.
  display.setSegments(data);

  } // setup

// -----------------------------------------------------------------------------
// main loop

void loop()
{
  int lastCount = 0; // rotary counter
  while (true) {
  vertValue = analogRead(vertPin) - vertZero;  // read vertical offset
  horzValue = analogRead(horzPin) - horzZero;  // read horizontal offset
  
  if (vertValue != 0)
    Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
  if (horzValue != 0)
    Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
    
  if ((digitalRead(selPin) == 0) && (!mouseClickFlag))  // if the joystick button is pressed
  {
    mouseClickFlag = 1;
    Mouse.press(MOUSE_LEFT);  // click the left button down
  }
  else if ((digitalRead(selPin))&&(mouseClickFlag)) // if the joystick button is not pressed
  {
    mouseClickFlag = 0;
    Mouse.release(MOUSE_LEFT);  // release the left button
  }
  if (!(digitalRead(PinSW))) {              // check if pushbutton is pressed
            virtualPosition = 0;            // if YES, then reset counter to ZERO
            while (!digitalRead(PinSW)) {}  // wait till switch is released
            delay(10);                      // debounce
            Serial.println("Reset");        // using the word RESET instead of COUNT here to find out a buggy encoder
            }
        if (virtualPosition != lastCount) { // show rotary counter on display
            lastCount = virtualPosition;
            Serial.print("Count = ");
            Serial.println(virtualPosition);
            if (virtualPosition > -1){      // positive numbers, include zero
              display.setSegments(0x40, 1, 4);
              display.showNumberDec(virtualPosition, true, 3, 1);
            }
            else {                          // negative numbers, show signed
              uint8_t clrs[] = {0x40};
              display.setSegments(clrs, 1, 4);
              display.showNumberDec(-virtualPosition, true, 3, 1);
            }
        }
            
  }
} // main loop
