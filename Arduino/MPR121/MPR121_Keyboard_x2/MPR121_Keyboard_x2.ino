#include <Wire.h>
#include <Keyboard.h>
#include <Adafruit_MPR121.h>

/*
 * Simple touch keyboard w/ MPR121
 * Utilises »MPR121« Adafruit library by Limor Fried/Ladyada
 * by: Frederik Brückner
 * date: 2019-12-11
 * Atmega 32u4 (Arduino Leonardo, Pro Micro) based HID
 * Send keystrokes with touch electrodes
 */

Adafruit_MPR121 capA = Adafruit_MPR121();
Adafruit_MPR121 capB = Adafruit_MPR121();

char keys[24] =               // char array to hold key stroke values

{
  'q',
  'w',
  'e',
  'r',
  't',
  'z',
  'u',
  'i',
  'o',
  'p',
  'a',
  's',
  'd',
  'f',
  'g',
  'h',
  'j',
  'k',
  'l',
  'y',
  'x',
  'c',
  'v',
  'b'
  
};


// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouchedA = 0;
uint16_t currtouchedA = 0;
uint16_t lasttouchedB = 0;
uint16_t currtouchedB = 0;


void setup() {
  /*Serial.begin(9600);
  
  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!capA.begin(0x5A)) {
    Serial.println("MPR121 A not found, check wiring?");
    while (1);
  }
  
  Serial.println("MPR121 A found!");
  */
capA.begin(0x5A);
capB.begin(0x5B);
Keyboard.begin();

}
  

void loop(){
input();
}

void input() {
  // Get the currently touched pads
  currtouchedA = capA.touched();
  currtouchedB = capB.touched();
   
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedA & _BV(i)) && !(lasttouchedA & _BV(i)) ) {
      //Serial.print(i); Serial.println(" on A touched");
      Keyboard.press(keys[i]);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedA & _BV(i)) && (lasttouchedA & _BV(i)) ) {
      //Serial.print(i); Serial.println(" on A released");
      Keyboard.release(keys[i]);
    }
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedB & _BV(i)) && !(lasttouchedB & _BV(i)) ) {
      //Serial.print(i); Serial.println(" on B touched");
      Keyboard.press(keys[i+12]);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouchedB & _BV(i)) && (lasttouchedB & _BV(i)) ) {
      //Serial.print(i); Serial.println(" on B released");
      Keyboard.release(keys[i+12]);
    }
  }

  // reset our state
  lasttouchedA = currtouchedA;
  lasttouchedB = currtouchedB;
  
}
