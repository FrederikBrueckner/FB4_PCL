const int mikrofon = A0; // Variable für Mikrofon Eingang
const int grenze = 600;
const int led = 8;
const int dauer = 500;

void setup() {
Serial.begin(9600);
pinMode(led, OUTPUT);
}

void loop() {
int lautstaerke = analogRead(mikrofon);
int wert = lautstaerke;
Serial.println(wert);
if(wert>grenze){
  Serial.println("Laut!");
  digitalWrite(led, HIGH);
  delay(dauer);
  }
  else
  digitalWrite(led, LOW);
}
