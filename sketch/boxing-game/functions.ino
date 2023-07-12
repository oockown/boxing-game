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
      if(blip==0) {  dmd.drawString(0, 8, " "+String(highscore));
                     dmd.drawString(27, 8, " ");
                     dmd.drawString(0, 0, F("      "));     
                     dmd.drawString(4, 0, F("HIGH"));       }
      else if(blip==1) {  dmd.drawString(0, 8, ">"+String(highscore));
                     dmd.drawString(27, 8, "<");     }
      else if(blip==2) {  dmd.drawString(0, 8, " "+String(highscore));
                     dmd.drawString(27, 8, " ");
                     dmd.drawString(0, 0, F("      "));   
                     dmd.drawString(2, 0, F("SCORE"));        }
      else  { dmd.drawString(0, 8, ">"+String(highscore));
              dmd.drawString(27, 8, "<");        }
  }
}
void display_counting() {
  dmd.drawString(0, 0, String(highscore));
  dmd.drawString(0, 8, String(score));
}
void display_result() {
  dmd.drawString(0, 0, String(highscore));
  dmd.drawString(0, 8, String(score));
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
