#include <ADCTouch.h>

/*
   Capacitive plate dimmer sketch to PWM drive a MOSFET for LED dimming
   by: Frederik Brückner
   date: 2020-01-08
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this code in your future endeavors! Reuse and share.
   Recommended MOSFET: IRL540
*/

int ref0; // Variable für Referenzmessung
int PWM = 5;  // Steuerpin für MOSFET
int sense;  // Variable für Messung
int threshold = 200;  // Grenzwert Berührempfindlichkeit
boolean touch = false;  // Variable Sensor berührt oder nicht?
unsigned long lastTouch;  // Variable Zeit seit letzter Berührung
unsigned long time; // Zeitmessung
unsigned long touchTime;  // Variable Berührzeit
int brightness = 0; // Variable LED Helligkeit
int x = 1;  // Variable Helligkeitsschritte
boolean flip = false; // Variable Richtungswechsel Dimmung

void setup() {
  Serial.begin(9600); // Serielle Schnittstelle öffnen
  delay(500); // Pause für MCU Pin Ausgleich
  ref0 = ADCTouch.read(A0, 500);  // Referenzmessung
  pinMode(PWM, OUTPUT); // PWM Pin als Output konfigurieren
  lastTouch = millis(); // Initialisierung letzte Berührung
  touchTime = 0;  // Initialisierung Berührzeit
}  // end setup()

void loop() {
  sense = ADCTouch.read(A0) - ref0; // Messung an Analogpin
  //Serial.println(sense);
  if (sense > threshold && !touch) {  // Erkennung Berührung
    Serial.println("Kontakt!");
    touch = true;
  }

  if (sense < threshold) {  // Erkennung keine Berührung
    touch = false;
    lastTouch = millis();
  }

  if (touchTime > 10 && touchTime < 200 && brightness == 0 && !touch) { // Einschalten
    brightness = 255;
    Serial.println("on");
    lastTouch = millis();
    touchTime = 0;
  }

  if (touchTime > 10 && touchTime < 200 && brightness > 0 && !touch) { // Ausschalten
    brightness = 0;
    Serial.println("off");
    lastTouch = millis();
    touchTime = 0;
  }

  if (brightness == 255) { // Variablenüberfluss verhindern
    x = -1;
  }

  if (brightness == 0) { // Variablenunterfluss verhindern
    x = 1;
  }

  if (touchTime >= 200 && touch) { // Dimmung
    brightness = brightness + x;
    flip = true;
  }

  if (!touch && flip) { // Dimmer Richtung wechseln
    x = -x;
    flip = false;
  }

  touchTime = millis() - lastTouch;
  Serial.println(touchTime);
  Serial.print("Brightness: ");
  Serial.println(brightness);
  Serial.println();
  analogWrite(PWM, brightness); // aktuelle Helligkeit schreiben
}  // end loop()
