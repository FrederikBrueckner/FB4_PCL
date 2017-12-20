PShape ebene3;
PShape ebene2;

float r1, r2, g1, g2, b1, b2;

void setup() {
  size(600, 600);
  ebene3 = loadShape("ProcessingEbene3-01.svg");
  ebene2 = loadShape("ProcessingEbene2-01.svg");
}
void draw ()
{
  background(255);
  r1 = map(mouseX, 0, width, 202, 24);
  g1 = map(mouseX, 0, width, 115, 41);
  b1 = map(mouseX, 0, width, 19, 45);
  r2 = map(mouseY, 0, height, 24, 231);
  g2 = map(mouseY, 0, height, 41, 62);
  b2 = map(mouseY, 0, height, 45, 37);
  
  ebene3.disableStyle();  // Ignore the colors in the SVG
  fill(int(r1), int(g1), int(b1));
  noStroke ();
  shape(ebene3, 250, 250, 300, 100);
  ebene2.disableStyle();  // Ignore the colors in the SVG
  fill(int(r2), int(g2), int(b2));
  noStroke ();
  shape(ebene2, 250, 250, 300, 100);
}