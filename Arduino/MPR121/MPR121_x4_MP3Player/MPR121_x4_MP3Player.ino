/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

// You can have up to 4 on one i2c bus but one is enough for testing!
#include <Wire.h>
#include "Adafruit_MPR121.h"

Adafruit_MPR121 capA = Adafruit_MPR121();
Adafruit_MPR121 capB = Adafruit_MPR121();
Adafruit_MPR121 capC = Adafruit_MPR121();
Adafruit_MPR121 capD = Adafruit_MPR121();

// compiler error handling
#include "Compiler_Errors.h"

//touchPin item
volatile int touchPin;
volatile int lastTouch;

// mp3 includes
#include <SPI.h>
#include <SdFat.h>
#include <FreeStack.h> 
#include <SFEMP3Shield.h>

// mp3 variables
SFEMP3Shield MP3player;
byte result;
int lastPlayed = 0;

// playlist variables
const int listLength = 10;
const int garbage = 50;  //empty track
volatile int playList[listLength];
boolean record = false;
boolean play = false;
volatile int listCounter = 0;

// mp3 behaviour defines
#define REPLAY_MODE TRUE  // By default, touching an electrode repeatedly will 
                          // play the track again from the start each time.
                          //
                          // If you set this to FALSE, repeatedly touching an 
                          // electrode will stop the track if it is already 
                          // playing, or play it from the start if it is not.
                          
// touch behaviour definitions
#define firstPin 2
#define lastPin 47

// sd card instantiation
SdFat sd;


// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouchedA = 0;
uint16_t currtouchedA = 0;

uint16_t lasttouchedB = 0;
uint16_t currtouchedB = 0;

uint16_t lasttouchedC = 0;
uint16_t currtouchedC = 0;

uint16_t lasttouchedD = 0;
uint16_t currtouchedD = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!capA.begin(0x5A)) {
    Serial.println("MPR121 A not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 A found!");
  
  if (!capB.begin(0x5B)) {
    Serial.println("MPR121 B not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 B found!");

  if (!capC.begin(0x5C)) {
    Serial.println("MPR121 C not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 C found!");
  
  if (!capD.begin(0x5D)) {
    Serial.println("MPR121 D not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 D found!");

  result = MP3player.begin();
  MP3player.setVolume(10,10);
 
  if(result != 0) {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to start MP3 player");
  }
  
} // End Setup

void loop() {
  // Get the currently touched pads
  currtouchedA = capA.touched();
  currtouchedB = capB.touched();
  currtouchedC = capC.touched();
  currtouchedD = capD.touched();
  
  
  for (uint8_t i=0; i<12; i++) {  // get sensor data
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedA & _BV(i)) && !(lasttouchedA & _BV(i)) ) {
      touchPin = i;
      Serial.println(touchPin);
    }
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedB & _BV(i)) && !(lasttouchedB & _BV(i)) ) {
      touchPin = 12 + i;
      Serial.println(touchPin);
    }
    // if it *was* touched and now *isnt*, alert!
    if ((currtouchedC & _BV(i)) && !(lasttouchedC & _BV(i)) ) {
      touchPin = 24 + i;
      Serial.println(touchPin);
    }
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouchedD & _BV(i)) && !(lasttouchedD & _BV(i)) ) {
      touchPin = 36 + i;
      Serial.println(touchPin);
    }
  }  // End get sensor data

  if(touchPin == 0 || touchPin == 1){  // play/record state, pin 0 = record, pin 1 = play
    if(touchPin == 0){
      record = true;
      Serial.print("Recordmode enabled");
      listCounter = 0;
      for (int i=0; i<listLength; i++){  // initialise playList with empty tracks
        playList[i] = garbage;
      }
    }
    if(touchPin == 1){ // pin 1 = play
      record = false;
      play = true;
      Serial.print("Playmode enabled");
    }
  } // End play/record state
  
  // reset our state
  lasttouchedA = currtouchedA;
  lasttouchedB = currtouchedB;
  lasttouchedC = currtouchedC;
  lasttouchedD = currtouchedD;
  
  if(touchPin<=lastPin && touchPin>=firstPin){  // play single item
    if(MP3player.isPlaying()){
      if(lastPlayed==touchPin && !REPLAY_MODE){
        // if we're already playing the requested track, stop it
        // (but only if we're not in REPLAY_MODE)
        MP3player.stopTrack();
        Serial.print("stopping track ");
        Serial.println(touchPin-firstPin);
      } else {
        // if we're already playing a different track (or we're in
        // REPLAY_MODE), stop and play the newly requested one
        MP3player.stopTrack();
        MP3player.playTrack(touchPin-firstPin);
        Serial.print("playing track ");
        Serial.println(touchPin-firstPin);
        // don't forget to update lastPlayed - without it we don't
        // have a history
        lastPlayed = touchPin;
      }
    } else {
      // if we're playing nothing, play the requested track 
      // and update lastplayed
      MP3player.playTrack(touchPin-firstPin);
      Serial.print("playing track ");
      Serial.println(touchPin-firstPin);
      lastPlayed = touchPin;
    }
  } // End play single item

  if(record && listCounter < 10 && touchPin !=0 && touchPin !=1 && touchPin != garbage){  // record mode enabled
    playList[listCounter] = touchPin;
    touchPin = garbage;
    listCounter++;
  } // end record mode
  if(record && listCounter >= 10 && touchPin !=0 && touchPin !=1 && touchPin != garbage){
    return;
  } // catch overflow

  if(play){  // play mode enabled
    for (int i = 0; i < listLength;){
     if(!MP3player.isPlaying()){
       MP3player.playTrack(playList[i]);      
       Serial.print("playing track ");
       Serial.println(playList[i]);
       i++;
     }
    }
    touchPin = garbage;
    play = false;
  }  // end play mode
} // End loop




