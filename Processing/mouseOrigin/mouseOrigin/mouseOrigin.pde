/* 
 * Switch mouse origin
 * by: Frederik Brückner
 * date: 2019-06-12
 * Left click + key 'c' sets mouse pointer origin
 */


volatile int mouseDeltaX = 0;  //store mouse pointer origin
volatile int mouseDeltaY = 0;
int scaler = 2;  //scale mouse movement

public void mouseOrigin()
{
  println("Origin calibrated");
  
  if (mousePressed && mouseButton == LEFT){
    mouseDeltaX = mouseX;
    mouseDeltaY = mouseY;
  }
  
println("New X = " + mouseDeltaX);
println("New Y = " + mouseDeltaY);
return;
};

void setup(){
  size(800,600,P2D);
};

void draw(){
  clear();  //clear screen
  noCursor();  //hide mouse cursor
  rect((mouseX + mouseDeltaX)/scaler, (mouseY + mouseDeltaY)/scaler, 10, 10);  //draw rectangle, scale position 
};

void keyPressed(){
  switch(key){
  case 'c': mouseOrigin();
  break;
  };
};
