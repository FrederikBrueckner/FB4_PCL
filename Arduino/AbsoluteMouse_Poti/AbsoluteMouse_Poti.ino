#include <AbsMouse.h>

/* 
 * Poti to mouse axis as absolute position HID
 * by: Frederik Brückner
 * date: 2018-12-10
 * Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID serving as absolute mouse position input
 * Two 5k ohm potis as input for mouse emulation, wired as voltage dividers
 * Connect potentiometer pins: 1 -> GND, 2 -> analog input, 3 -> VCC
 */

const int xAxis = A0;   // select the input pins for the potentiometers
const int yAxis = A1;
const int xRes = 1920;
const int yRes = 1080;   

void setup() {
 AbsMouse.init(xRes, yRes);        // Start mouse emulation (screen res)
}

void loop() {
 // read and scale the two axes:
  int xReading = map(analogRead(xAxis), 0, 1023, 0, xRes); // read and scale values to match screen size
  int yReading = map(analogRead(yAxis), 0, 1023, 0, yRes);
  AbsMouse.move(xReading, yReading);
}

