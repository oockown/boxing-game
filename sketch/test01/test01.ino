#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>
#include <DFRobotDFPlayerMini.h>

#define DISPLAYS_WIDE 1
#define DISPLAYS_HIGH 1

#define SENSOR_1      2 
#define SENSOR_2      3 
#define START_BUTTON  4 
#define LED_BUTTON    5 
#define ACTUATOR      6 

SoftDMD dmd(DISPLAYS_WIDE,DISPLAYS_HIGH);
DMD_TextBox box(dmd, 0, 0, 32, 16);
DFRobotDFPlayerMini myDFPlayer;

void setup() {

  Serial3.begin(9600);
  delay(1000);
  myDFPlayer.begin(Serial3);
  dmd.setBrightness(50);
  dmd.selectFont(Arial14);
  dmd.begin();
  delay(500);
  myDFPlayer.play(4);  
  dmd.drawString(0, 0, F("Abcd"));
}

void loop() {
  delay(3000);
  myDFPlayer.play(2);  
  dmd.drawString(0, 0, F(".. 2 "));
  delay(3000);
  myDFPlayer.play(3);  
  dmd.drawString(0, 0, F("...3 "));
  delay(3000);
  myDFPlayer.play(1);  
  dmd.drawString(0, 0, F(". 1"));
  delay(3000);
  myDFPlayer.play(4);  
  dmd.drawString(0, 0, F("....4"));
}
