/* 
GazeTrack: Basic demo
-
In this demo, the user's gaze is represented
by a white circle.
-

Before you run this demo, make sure the
Tobii eye-tracker (EyeX, 4C) is connected
to the computer, and that the Tobii software 
is running and calibrated to your eyes.

Finally, make sure the 'TobiiStream.exe' is 
running and displaying gaze data. You can
download this application from:
http://hci.soc.napier.ac.uk/GazeTrack/TobiiStream.zip

by Augusto Esteves
http://hci.soc.napier.ac.uk
https://github.com/AugustoEst/gazetrack

If you enjoyed this demo, 
and would like to make a contribution to the project:
ETH: 0xED6A9bA7d99D8cb55037d9c68C60998eA17eCfC7
BTC: 3QSrrQdET35F2CdaZKSK1PnCrRc7np9mdQ
XLM: GD263F3X5D5ULX7TBXF6ULPGKEICAHJEO22ZOJABNVJSCYPEJW6JBU7G
*/

import gazetrack.*;
PImage img;

GazeTrack gazeTrack;
ArrayList<PVector> trail = new ArrayList();
PrintWriter output;

void setup() 
{
  fullScreen();
  img = loadImage("gesicht.jpg");
  
  // Gaze cursor param.
  noFill();
  stroke(50, 100);
  strokeWeight(4);
  
  gazeTrack = new GazeTrack(this);
  
  // If the TobiiStream.exe asked you to use a 
  // different socket port (e.g., 5656), use this instead:
  // gazeTrack = new GazeTrack(this, "5656");
  
  // Save Strings to file
  output = createWriter(year() + "-" + month() + "-" + day() + "_" + hour() + minute() + "_Gaze_Track.txt");
}

void draw() 
{
  background(255);
  image(img, 150 ,0);
  
  if (gazeTrack.gazePresent())
  {
    ellipse(gazeTrack.getGazeX(), gazeTrack.getGazeY(), 85, 85);
    while(trail.size()>100) trail.remove(0);
    trail.add( new PVector(gazeTrack.getGazeX(), gazeTrack.getGazeY(), 50) ); 
    fill(100);
    for(int i=0;i<trail.size();i++) ellipse(trail.get(i).x,trail.get(i).y,trail.get(i).z,trail.get(i).z--);
    fill(255,0,0);
  
    // Print the tracker's timestamp for the gaze cursor above
    output.println(int(gazeTrack.getGazeX()) + ":" + int(gazeTrack.getGazeY()));
  }
}

void keyPressed() {
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
  exit(); // Stops the program
}
