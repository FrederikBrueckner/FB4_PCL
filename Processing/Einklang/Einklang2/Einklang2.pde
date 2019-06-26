import processing.sound.*;
import processing.serial.*;

Scene2 scn2;
Scene3 scn3;

SinOsc sine1 = new SinOsc(this);
SinOsc sine2 = new SinOsc(this);
SinOsc sine3 = new SinOsc(this);

Sound s1;
Sound s2;
Sound s3;

FFT fft1;
FFT fft2;
FFT fft3;

Serial myPort;
public int[] sRead; //serial port read input



///////////////////////////////////////////////// Fenster mit Welle Nummer 1

float S1frequenz = 440;

// Für Punkte
int diameter = 7;
float t=0;
float dt =0.1;
float amplitude = S1frequenz/31;
int weit, hoch;
float wellecontr ,welle = wellecontr = 0;
float T = 10200/S1frequenz; // wiederholungsperiode
float omega = 2*PI/T;
float abstand = 14; //abstand zwischen Bällen
float z=0; // Phasenverschiebungskonstante
float f;

// Für Welle
int xspacing = 1;   // How far apart should each horizontal location be spaced
int w;              // Width of entire wave
float theta = 0.0;  // Start angle at 0
float welleamplitude = amplitude;  // Height of wave
float period = 204000/S1frequenz;  // How many pixels before the wave repeats
float dx;  // Value for incrementing X, a function of period and xspacing
float[] yvalues;  // Using an array to store height values for the wave

float[] waveYvalues = new float[500];
float OwaveYvalues;
float waveX;
int waveCount;
int waveLength = 500;

public void settings() {
  size(314, 620);
}

void setup(){
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
// surface.setResizable(true); //Fenster variable Größe
  scn2 = new Scene2();
  scn3 = new Scene3();
  fill(255);
  rectMode(CENTER); //Bezugspunkt für alle Abbildung ist nun ihre mitte
  smooth();
  
  weit = width/2;
  hoch = height/2;
  dx = (TWO_PI / period) * xspacing;
  yvalues = new float[232/xspacing];
  
    // Turn the volume down globally.
  s1 = new Sound(this);
  s1.volume(0.2);
  
  fft1 = new FFT(this, 16384);
  sine1.play();
  fft1.input(sine1);
  sine1.freq(S1frequenz);
  
}


void draw() {
  
  background(0);
  sRead = int(split(myPort.readString(),':'));
  
  for(int i=0; i<2; i++) {
    println(sRead[i]);
    };
  
  for(int i=0; i<(width+diameter/2)/(diameter+abstand); i++) {
    f=f+S1frequenz/100000;
    for (int k=0; k < (height+diameter/2)/(diameter+abstand); k++){
      
    welle = amplitude*sin(omega*t+PI*z*0.1);
    
    z = z+1;
    if (z>(height+diameter/2)/((diameter+abstand))) 
    {z=0;}
    
    // welche kugel ist hervorgehoben = i anzahl von links und k anzahl von oben
    if (i==12 && k==14){
      fill(219,236,224);
      noStroke();
      waveYvalues[waveCount] = k*(diameter+abstand)+welle;
      
      waveX = i*(diameter+abstand);
    } else {
      fill(219,236,224);
      noStroke();

    }
    ellipse(i*(diameter+abstand), k*(diameter+abstand)+welle, diameter, diameter);
    
  }
  }
  waveCount += 1;
  if (waveCount >= waveLength){
  waveCount = 0;
  }
  
  for (int w = 0; w < waveLength; w++){
    int myWCo = waveCount-w;

    if (myWCo < 1){
      myWCo = waveCount-w+(waveLength-1);
    }
   
    stroke(46,174,124);
    strokeWeight(7);
    if(w>0 && myWCo>0){
    line(waveX-w ,waveYvalues[myWCo], waveX-(w+1), waveYvalues[myWCo-1]);
    }
  }
  
  t += dt;
   theta += 0.0001*S1frequenz;
  
}

///////////////////////////////////////////////// Fenster mit Welle Nummer 2

class Scene2 extends PApplet {
  Scene2() {
    super();
    PApplet.runSketch(new String[] {this.getClass().getSimpleName()}, this);
  }

float S2frequenz = 880;

// Für Punkte
int diameter = 7;
float t=0;
float dt =0.1;
float amplitude = S2frequenz/31;
int weit, hoch;
float wellecontr ,welle =wellecontr=0;
float T = 10200/S2frequenz; // wiederholungsperiode
float omega = 2*PI/T;
float abstand = 14; //abstand zwischen Bällen
float z=0; // Phasenverschiebungskonstante
float f;

// Für Welle
int xspacing = 1;   // How far apart should each horizontal location be spaced
int w;              // Width of entire wave
float theta = 0.0;  // Start angle at 0
float welleamplitude = amplitude;  // Height of wave
float period = 204000/S2frequenz;  // How many pixels before the wave repeats
float dx;  // Value for incrementing X, a function of period and xspacing
float[] yvalues;  // Using an array to store height values for the wave

float[] waveYvalues = new float[500];
float OwaveYvalues;
float waveX;
int waveCount;
int waveLength = 500;

void settings() {
  size(314, 620);
}

void setup(){
// surface.setResizable(true); //Fenster variable Größe
  fill(255);
  rectMode(CENTER); //Bezugspunkt für alle Abbildung ist nun ihre mitte
  smooth();
  
  weit = width/2;
  hoch = height/2;
  dx = (TWO_PI / period) * xspacing;
  yvalues = new float[232/xspacing];
  
    // Turn the volume down globally.
  s2 = new Sound(this);
  s2.volume(0.2);
  
  fft2 = new FFT(this, 16384);
  sine2.play();
  fft2.input(sine2);
  sine2.freq(S2frequenz);
  
}


void draw() {
  
  background(0);
  for(int i=0; i<(width+diameter/2)/(diameter+abstand); i++) {
    f=f+S2frequenz/100000;
    for (int k=0; k < (height+diameter/2)/(diameter+abstand); k++){
      
    welle = amplitude*sin(omega*t+PI*z*0.1);
    
    z = z+1;
    if (z>(height+diameter/2)/((diameter+abstand))) 
    {z=0;}
    
    // welche kugel ist hervorgehoben = i anzahl von links und k anzahl von oben
    if (i==12 && k==14){
      fill(251,220,217);
      noStroke();
      waveYvalues[waveCount] = k*(diameter+abstand)+welle;
      
      waveX = i*(diameter+abstand);
    } else {
      fill(251,220,217);
      noStroke();

    }
    ellipse(i*(diameter+abstand), k*(diameter+abstand)+welle, diameter, diameter);
    
  }
  }
  waveCount += 1;
  if (waveCount >= waveLength){
  waveCount = 0;
  }
  
  for (int w = 0; w < waveLength; w++){
    int myWCo = waveCount-w;

    if (myWCo < 1){
      myWCo = waveCount-w+(waveLength-1);
    }
   
    stroke(235,92,105);
    strokeWeight(7);
    if(w>0 && myWCo>0){
    line(waveX-w ,waveYvalues[myWCo], waveX-(w+1), waveYvalues[myWCo-1]);
    }
  }
  
  t += dt;
   theta += 0.0001*S2frequenz;
  
}
}
///////////////////////////////////////////////// Fenster mit Welle Nummer 3

class Scene3 extends PApplet {
  Scene3() {
    super();
    PApplet.runSketch(new String[] {this.getClass().getSimpleName()}, this);
  }

float S3frequenz = 1320;

// Für Punkte
int diameter = 7;
float t=0;
float dt =0.1;
float amplitude = S3frequenz/31;
int weit, hoch;
float wellecontr ,welle =wellecontr=0;
float T = 10200/S3frequenz; // wiederholungsperiode
float omega = 2*PI/T;
float abstand = 14; //abstand zwischen Bällen
float z=0; // Phasenverschiebungskonstante
float f;

// Für Welle
int xspacing = 1;   // How far apart should each horizontal location be spaced
int w;              // Width of entire wave
float theta = 0.0;  // Start angle at 0
float welleamplitude = amplitude;  // Height of wave
float period = 204000/S3frequenz;  // How many pixels before the wave repeats
float dx;  // Value for incrementing X, a function of period and xspacing
float[] yvalues;  // Using an array to store height values for the wave

float[] waveYvalues = new float[500];
float OwaveYvalues;
float waveX;
int waveCount;
int waveLength = 500;

void settings() {
  size(314, 620);
}

void setup(){
// surface.setResizable(true); //Fenster variable Größe
  fill(255);
  rectMode(CENTER); //Bezugspunkt für alle Abbildung ist nun ihre mitte
  smooth();
  
  weit = width/2;
  hoch = height/2;
  dx = (TWO_PI / period) * xspacing;
  yvalues = new float[232/xspacing];
  
    // Turn the volume down globally.
  s3 = new Sound(this);
  s3.volume(0.2);
  
  fft3 = new FFT(this, 16384);
  sine3.play();
  fft3.input(sine3);
  sine3.freq(S1frequenz);
  
}


void draw() {
  
  background(0);
  for(int i=0; i<(width+diameter/2)/(diameter+abstand); i++) {
    f=f+S3frequenz/100000;
    for (int k=0; k < (height+diameter/2)/(diameter+abstand); k++){
      
    welle = amplitude*sin(omega*t+PI*z*0.1);
    
    z = z+1;
    if (z>(height+diameter/2)/((diameter+abstand))) 
    {z=0;}
    
    // welche kugel ist hervorgehoben = i anzahl von links und k anzahl von oben
    if (i==12 && k==14){
      fill(252,238,211);
      noStroke();
      waveYvalues[waveCount] = k*(diameter+abstand)+welle;
      
      waveX = i*(diameter+abstand);
    } else {
      fill(252,238,211);
      noStroke();

    }
    ellipse(i*(diameter+abstand), k*(diameter+abstand)+welle, diameter, diameter);
    
  }
  }
  waveCount += 1;
  if (waveCount >= waveLength){
  waveCount = 0;
  }
  
  for (int w = 0; w < waveLength; w++){
    int myWCo = waveCount-w;

    if (myWCo < 1){
      myWCo = waveCount-w+(waveLength-1);
    }
   
    stroke(240,188,50);
    strokeWeight(7);
    if(w>0 && myWCo>0){
    line(waveX-w ,waveYvalues[myWCo], waveX-(w+1), waveYvalues[myWCo-1]);
    }
  }
  
  t += dt;
   theta += 0.0001*S3frequenz;
  
}
}
