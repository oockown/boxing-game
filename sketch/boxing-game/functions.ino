void display_on() {
  dmd.drawString(0, 0, F("FUN-"));
  dmd.drawString(0, 8, F("BOXER"));
  delay(2000);
  dmd.clearScreen();
}
void display_normal() {
  if(millis()/400 != blip_millis) {
      blip_millis = millis()/400;
      int blip = blip_millis%4;
      if(blip==0) {  dmd.drawString(7, 8, String(highscore));
                     dmd.drawString(0, 8, " "); dmd.drawString(27, 8, " ");
                     dmd.drawString(0, 0, F("      "));     
                     dmd.drawString(4, 0, F("HIGH"));       }
      else if(blip==1) {  dmd.drawString(7, 8, String(highscore));
                          dmd.drawString(0, 8, ">"); dmd.drawString(27, 8, "<");     }
      else if(blip==2) {  dmd.drawString(7, 8, String(highscore));
                     dmd.drawString(0, 8, " "); dmd.drawString(27, 8, " ");
                     dmd.drawString(0, 0, F("      "));   
                     dmd.drawString(2, 0, F("SCORE"));        }
      else  { dmd.drawString(7, 8, String(highscore));
              dmd.drawString(0, 8, ">"); dmd.drawString(27, 8, "<");        }
  }
}
void display_counting() {
  dmd.clearScreen();
  for (int i=0; i<score-10; i+=20 )  { dmd.drawString(7, 5, String(i)); delay(100); }
  dmd.drawString(7, 5, String(score-9)); delay(150);
  dmd.drawString(7, 5, String(score-7)); delay(200);
  dmd.drawString(7, 5, String(score-5)); delay(250);
  dmd.drawString(7, 5, String(score-3)); delay(300);
  dmd.drawString(7, 5, String(score-2)); delay(400);
  dmd.drawString(7, 5, String(score-1)); delay(500);
  dmd.drawString(7, 5, String(score)); delay(800);
}
void display_result() {
  dmd.clearScreen();
  dmd.drawString(7, 0, String(highscore));
  dmd.drawString(7, 8, String(score));
  dmd.drawString(0, 8, ">"); dmd.drawString(27, 8, "<");
  delay(200);
  for(int i=0;i<5;i++) {
  dmd.drawString(7, 0, String(highscore));
  dmd.drawString(7, 8, String("   "));
  dmd.drawString(0, 8, ">"); dmd.drawString(27, 8, "<");
  delay(500);
  dmd.drawString(7, 0, String(highscore));
  dmd.drawString(7, 8, String(score));
  dmd.drawString(0, 8, ">"); dmd.drawString(27, 8, "<");
  delay(500);
  }
  delay(1200);
  dmd.clearScreen();
  delay(100);
}
void display_error(){
  dmd.clearScreen();
  dmd.drawString(6, 4, F("ERR!"));
  st_clear=0;
}
void release_punch() {
  while(digitalRead(SENSOR1)==HIGH) digitalWrite(RELAY,LOW);
  delay(100);
  digitalWrite(RELAY,HIGH);
}
