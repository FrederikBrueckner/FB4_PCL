void setup(){

  noFill();
  stroke(0, 255);
  strokeWeight(2);

};

void draw(){
  

String[] lines = loadStrings("Gaze_Track.txt"); //<>//
int[][] coords = new int[lines.length][2];

for (int i = 0 ; i < lines.length; i++) {
  String[] temp = split(lines[i], ':');
  for (int k = 0; k < 2; k++){
    coords[i][k] = int(temp[k]); //<>//
    }
  }
  
  
noLoop(); //<>//
};
