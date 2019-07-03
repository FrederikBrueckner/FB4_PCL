/* //<>// //<>//
 *  Einklang Sketch by Laura Carl
 *  Programming by Laura, Robert and Frederik
 *  FH Aachen Fachbereich für Gestaltung
 *  Physical Computing Lab 2019
 *
 */

import processing.sound.*;
import processing.serial.*;
Serial myPort;
String val = "0000:0000:0000:0000";     // data from the serial port
int[] values = {0, 0, 0, 0};
boolean debug = false;  // debug mode
String path;  // keep track of sketch path

Scene scn1;  // Object 1 from class Scene
Scene scn2;  // Object 2 from class Scene
Scene scn3;  // Object 3 from class Scene

public void settings() {
  String portName = Serial.list()[0]; // change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);  // configure serial port
  myPort.bufferUntil('\n');
  fullScreen();
}

void setup() {
  path = sketchPath();  // path to sketch directory for saving screenshots from objects
  scn1 = new Scene(314, 620, 100, 100, 200, -1.0, 0);  // instantiate runSketch() surface objects with parameters:
  scn2 = new Scene(314, 620, 514, 100, 500, 0, 1);     // surface width, surface height, surface x-position, surface y-position, audio pan, window ID
  scn3 = new Scene(314, 620, 928, 100, 800, 1.0, 2);
}

void draw() {  // Processing will call a draw loop, no matter what
  background(0);
  surface.setVisible(false);  // hide main draw loop
}

class Scene extends PApplet {

  float Sfrequency;
  
  // Dots
  int diameter = 7;
  float t = 0;
  float dt = 0.1;
  float amplitude = Sfrequency / 31;
  int wide, tall;
  float wavecontr, wave = wavecontr = 0;
  float T = 10200 / Sfrequency; // recurring periode
  float omega = 2 * PI / T;
  float distance = 14; // distance between dots
  float z = 0; // phase shift constant
  float f;

  // Waves
  int xspacing = 1;   // How far apart should each horizontal location be spaced
  int w;              // Width of entire wave
  float theta = 0.0;  // Start angle at 0
  float waveamplitude = amplitude;  // Height of wave
  float period = 204000/Sfrequency;  // How many pixels before the wave repeats
  float dx;  // Value for incrementing X, a function of period and xspacing
  float[] yvalues;  // Using an array to store height values for the wave
  float[] waveYvalues = new float[500];
  float OwaveYvalues;
  float waveX;
  float p;
  int waveCount;
  int waveLength = 500;
  
  // Surface specific
  int windowX;  // surface size x
  int windowY;  // surface size y
  int posX;  // surface position x
  int posY;  // surface position y
  int ID;  // surface ID
  
  // Audio
  Sound s = new Sound(this);
  FFT fft = new FFT(this, 16384);
  SinOsc wfm = new SinOsc(this);
  float sineFreq;

  Scene(int X, int Y, int pX, int pY, float Frequency, float pan, int num) {
    super();
    PApplet.runSketch(new String[] {this.getClass().getSimpleName()}, this);
    windowX = X;
    windowY = Y;
    posX = pX;
    posY = pY;
    Sfrequency = Frequency;
    p = pan;
    ID = num;
  } // end Scene()

  void settings() {
    size(314, 620);
    fullScreen();
  } // end settings()

  void setup() {
    // surface.setResizable(true); // variable window size
    surface.setSize(windowX, windowY);
    surface.setLocation(posX, posY);
    fill(255);
    //rectMode(CENTER); // create rectangular shapes from center

    wide = width/2;
    tall = height/2;
    dx = (TWO_PI / period) * xspacing;
    yvalues = new float[232/xspacing];

    wfm.play();
    wfm.pan(p);
    fft.input(wfm);
  } // end setup()

  void draw() {
    Sfrequency = map(values[ID], 0, 1024, 0, 2550);

    if (debug) {
      println("Surface "+ID);
      print("Frequency "+ID+" ");
      println(Sfrequency);
      print("Amplitude "+ID+" ");
      println(amplitude);
      println();
    }

    // Turn the volume down globally.
    s.volume(0.2);
    wfm.freq(Sfrequency);

    background(0);
    amplitude = Sfrequency/31;
    T = 10200/Sfrequency;
    period = 204000/Sfrequency;
    for (int i = 0; i < (width + diameter / 2) / (diameter + distance); i++) {
      f = f + Sfrequency / 100000;
      for (int k = 0; k < (height + diameter / 2) / (diameter + distance); k++) {

        wave = amplitude * sin(omega * t + PI * z * 0.1);

        z = z + 1;
        if (z > (height + diameter / 2) / (diameter + distance)) 
        {
          z = 0;
        }

        // Which dots are being highlighted? i counting from left, k counting from top
        if (i == 12 && k == 14) {
          fill(219, 236, 224);
          noStroke();
          waveYvalues[waveCount] = k * (diameter + distance) + wave;

          waveX = i * (diameter + distance);
        } else {
          fill(219, 236, 224);
          noStroke();
        }
        ellipse(i * (diameter + distance), k * (diameter + distance) + wave, diameter, diameter);
      }
    }
    waveCount += 1;
    if (waveCount >= waveLength) {
      waveCount = 0;
    }

    for (int w = 0; w < waveLength; w++) {
      int myWCo = waveCount - w;

      if (myWCo < 1) {
        myWCo = waveCount - w + (waveLength - 1);
      }

      stroke(46, 174, 124);
      strokeWeight(7);
      if (w > 0 && myWCo > 0) {
        line(waveX - w, waveYvalues[myWCo], waveX - (w + 1), waveYvalues[myWCo - 1]);
      }
    }

    t += Sfrequency / 1000;
    theta += 0.05;

    // t += dt;
    // theta += 0.0001 * Sfrequency;
  } // end draw()

  void keyPressed() {
    if (key == 's') {
      saveFrame(path + "/Window_" + ID + "-######.png");  // save a screen to disk
    }
    if (key=='d') {
      debug = !debug;  // enable debugging output
    }
  }  // end keyPressed()
}  // end class Scene
