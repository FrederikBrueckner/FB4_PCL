import processing.sound.*;
import processing.serial.*;
Serial myPort;
String val = "0000:0000:0000:0000";     // data from the serial port
int[] values = {0, 0, 0, 0};

Scene scn1;
Scene scn2;
Scene scn3;


public void settings() {
  size(314, 620);
  String portName = Serial.list()[1]; // change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');
  fullScreen();
}

void setup() {
  // surface.setResizable(true); //Fenster variable Größe
  scn1 = new Scene(314, 620, 100, 100, 0, 100);
  //scn2 = new Scene(314, 620, 514, 100, 1, 500);
  //scn3 = new Scene(314, 620, 928, 100, 2, 800);
  fill(255);
  //surface.setSize(314, 620);
  //surface.setLocation(100,100);
}

public void serialEvent(Serial myPort) { // sensor input via serial port with exception handling
  try
  {
    while ( myPort.available() > 0) // do only when port is available
    {  
      if (val != null) // check for NullPointerException
      {
        val = myPort.readStringUntil('\n');         // read data and store string in val
        values = int(split(val, ':')); // split datapackage and convert to float
      }
    }
  }
  catch (Exception e) { // exception handling
    println(e);
  }
}

void draw() {
  background(50); //<>//
}

void keyPressed() {
  if (key == 's') {
    saveFrame("ScreenShot-######.png");  // save a screen to disk
  }
}


class Scene extends PApplet {
  
  float Sfrequenz;
  // Für Punkte
  int diameter;
  float t=0;
  float dt=0.1;
  float amplitude = Sfrequenz/31;
  int weit, hoch;
  float wellecontr, welle=wellecontr=0;
  float T = 10200/Sfrequenz; // wiederholungsperiode
  float omega = 2*PI/T;
  float abstand = 14; //abstand zwischen Bällen
  float z=0; // Phasenverschiebungskonstante
  float f;

  // Für Welle
  int xspacing = 1;   // How far apart should each horizontal location be spaced
  int w;              // Width of entire wave
  float theta = 0.0;  // Start angle at 0
  float welleamplitude = amplitude;  // Height of wave
  float period = 204000/Sfrequenz;  // How many pixels before the wave repeats
  float dx;  // Value for incrementing X, a function of period and xspacing
  float[] yvalues;  // Using an array to store height values for the wave

  float[] waveYvalues = new float[500];
  float OwaveYvalues;
  float waveX;
  int waveCount;
  int waveLength = 500;
  int windowX;
  int windowY;
  int posX;
  int posY;
  int ID;
  FFT fft;
  SinOsc sine = new SinOsc(this);
  Sound s;


  Scene(int X, int Y, int pX, int pY, int num, float Frequenz) {
    super();
    PApplet.runSketch(new String[] {this.getClass().getSimpleName()}, this);
    windowX = X;
    windowY = Y;
    posX = pX;
    posY = pY;
    ID = num;
    Sfrequenz = Frequenz;
  }

  void settings() {
    size(314, 620);
    fullScreen();
  }

  void setup() {
    // surface.setResizable(true); //Fenster variable Größe
    surface.setSize(windowX, windowY);
    surface.setLocation(posX, posY);
    fill(255);
    rectMode(CENTER); //Bezugspunkt für alle Abbildung ist nun ihre mitte
    smooth();

    weit = width/2;
    hoch = height/2;
    dx = (TWO_PI / period) * xspacing;
    yvalues = new float[232/xspacing];

    fft = new FFT(this, 16384);
    sine.play();
    sine.pan(0);
    fft.input(sine);
  }


  void draw() {

    Sfrequenz = map(values[ID], 0, 1024, 0, 2550);
    //  println(S1frequenz);
    // println(amplitude);

    // Turn the volume down globally.
    s = new Sound(this);
    s.volume(0.2);
    sine.freq(Sfrequenz);


    background(0);
    amplitude = Sfrequenz/31;
    T = 10200/Sfrequenz;
    period = 204000/Sfrequenz;
    for (int i=0; i<(width+diameter/2)/(diameter+abstand); i++) {
      f=f+Sfrequenz/100000;
      for (int k=0; k < (height+diameter/2)/(diameter+abstand); k++) {

        welle = amplitude*sin(omega*t+PI*z*0.1);

        z = z+1;
        if (z>(height+diameter/2)/((diameter+abstand))) 
        {
          z=0;
        }

        // welche kugel ist hervorgehoben = i anzahl von links und k anzahl von oben
        if (i==12 && k==14) {
          fill(219, 236, 224);
          noStroke();
          waveYvalues[waveCount] = k*(diameter+abstand)+welle;

          waveX = i*(diameter+abstand);
        } else {
          fill(219, 236, 224);
          noStroke();
        }
        ellipse(i*(diameter+abstand), k*(diameter+abstand)+welle, diameter, diameter);
      }
    }
    waveCount += 1;
    if (waveCount >= waveLength) {
      waveCount = 0;
    }

    for (int w = 0; w < waveLength; w++) {
      int myWCo = waveCount-w;

      if (myWCo < 1) {
        myWCo = waveCount-w+(waveLength-1);
      }

      stroke(46, 174, 124);
      strokeWeight(7);
      if (w>0 && myWCo>0) {
        line(waveX-w, waveYvalues[myWCo], waveX-(w+1), waveYvalues[myWCo-1]);
      }
    }

    t += Sfrequenz/1000;
    theta += 0.05;

    //t += dt;
    //theta += 0.0001*S1frequenz;
  }
}