#include <Rotary.h>
#include <Mouse.h>
#include <Arduino.h>
#include <TM1637Display.h> //Einbinden der Bibliothekt zum ansteuern des Displays

#define CLK 10 //PIN 2 für den CLK PIN
#define DIO 9 //PIN3 für den DIO 

//erzeugen des Display Objektes mit den Parametern für die PINs
TM1637Display display(CLK, DIO); 

// Rotary encoder is wired with the common to ground and the two
// outputs to pins 2 and 3.
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

const int               PinSW    = 7;         // Used for the rotary push button switch
const int               sensitivity = 100;    // Higher sensitivity value = slower mouse, should be <= about 500


// -----------------------------------------------------------------------------
// global vars

volatile int            virtualPosition = 0;
int                     horzPin = A0;          // Analog output of horizontal joystick pin
int                     vertPin = A1;          // Analog output of vertical joystick pin
int                     selPin = 8;            // Select button pin of joystick
int                     vertZero, horzZero;    // Stores the initial value of each axis, usually around 512
int                     vertValue, horzValue;  // Stores current analog output of each axis
int                     mouseClickFlag = 0;

// -----------------------------------------------------------------------------
// forward declarations

void rotate();
void loop();
void setup();

// -----------------------------------------------------------------------------
// Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK

void rotate()  {
  unsigned char result = rotary.process();
    if (result == DIR_CW) {
      virtualPosition++;
    } else if (result == DIR_CCW) {
      virtualPosition--;
      }
    
    } // rotate interrupt routine

// -----------------------------------------------------------------------------
// setup

void setup()
{ 
  Serial.begin(57600);
  pinMode(horzPin, INPUT);  // joystick X
  pinMode(vertPin, INPUT);  // joystick Y
  pinMode(selPin, INPUT);   // joystick click
  pinMode(PinSW, INPUT);    // rotary encoder click
  digitalWrite(selPin, HIGH);  // Pull button select pin high
  delay(1000);  // short delay to let outputs settle
  vertZero = analogRead(vertPin);  // get the initial values
  horzZero = analogRead(horzPin);  // Joystick should be in neutral position when reading these

  attachInterrupt(0, rotate, CHANGE);
  attachInterrupt(1, rotate, CHANGE);   // interrupt 1 == pin 2, interrupt 0 == pin 3 on Arduino Leonardo

  Serial.println("Start");

  display.setBrightness(15);
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  //Setzt die Anzahl der möglichen Segmente.
  display.setSegments(data);

  }

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
  if (!(digitalRead(PinSW))) {        // check if pushbutton is pressed
            virtualPosition = 0;            // if YES, then reset counter to ZERO
            while (!digitalRead(PinSW)) {}  // wait til switch is released
            delay(10);                      // debounce
            Serial.println("Reset");        // Using the word RESET instead of COUNT here to find out a buggy encoder
            }
        if (virtualPosition != lastCount) {
            lastCount = virtualPosition;
            Serial.print("Count = ");
            Serial.println(virtualPosition);
            if (virtualPosition > -1){
              display.setSegments(0x40, 1, 4);
              display.showNumberDec(virtualPosition, true, 3, 1);
            }
            else {
              uint8_t clrs[] = {0x40};
              display.setSegments(clrs, 1, 4);
              display.showNumberDec(-virtualPosition, true, 3, 1);
            }
        }
            
  }
}
