PImage img;

void setup(){
  fullScreen();
  noFill();
  stroke(0, 255);
  strokeWeight(1);

 img = loadImage("gesicht.jpg");
};

void draw(){
  
image(img, 150 ,0);
String[] lines = loadStrings("Gaze_Track.txt");
int[][] coords = new int[lines.length][2];

for (int i = 0 ; i < lines.length; i++) {
  String[] temp = split(lines[i], ':');
  for (int k = 0; k < 2; k++){
    coords[i][k] = int(temp[k]); //<>//
    }
  }
  for (int i = 0 ; i < lines.length-1; i++) {
    line(coords[i][0], coords[i][1], coords[i+1][0], coords[i+1][1]);
  }
noLoop();
};
