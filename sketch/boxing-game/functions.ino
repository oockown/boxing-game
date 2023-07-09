void display_on() {
  dmd.drawString(0, 0, F("FUN-"));
  dmd.drawString(0, 8, F("BOXER"));
  delay(2000);
  dmd.clearScreen();
}
void display_normal() {
  dmd.drawString(0, 0, String(highscore));
  dmd.drawString(0, 8, String(score));
}
void display_counting() {
  dmd.drawString(0, 0, String(highscore));
  dmd.drawString(0, 8, String(score));
}
void display_result() {
  dmd.drawString(0, 0, String(highscore));
  dmd.drawString(0, 8, String(score));
}
void display_start(){
  dmd.drawString(0, 4, F("Ready"));
}
void release_punch() {
  
}
