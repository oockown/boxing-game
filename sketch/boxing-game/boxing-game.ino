/* game cycle :
 *  - start button pushed
 *  - release target, start sound, display goes zero
 *  - target being hit
 *  - count time different, punched sound, display start count and put score
 *  - if higher than HS, replace high score display, sound clapping, else sound wooing
 *  - display still high score and last score
 *  - wait for another pushed start button
 *  
 *  input :   - start button : 4
 *            - punch sensor (magnet or vibration) : 2 & 3
 *  output :  - p10 panel display : SPI
 *            - mini DF Player : Serial3
 *            - led button : 5
 *            - driver or relay for punch RELAY / releaser :  6
 */
#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <DFRobotDFPlayerMini.h>
#include <EEPROM.h>

#define DISPLAYS_WIDE 1
#define DISPLAYS_HIGH 1

#define SENSOR1      2 
#define SENSOR2      4
#define START_BUTTON  17 
#define LED_BUTTON    5 
#define RELAY      16 
#define MAXTIME   1000
#define BELL      2 
#define COUNTING  3 
#define CLAP      1 
#define WOO       4 

SoftDMD dmd(DISPLAYS_WIDE,DISPLAYS_HIGH);
DMD_TextBox box(dmd, 0, 0, 32, 16);
DFRobotDFPlayerMini myDFPlayer;

int score, highscore;
int st_game=0, st_clear=0;
unsigned long punch_millis, punch_time, cek_millis,  blip_millis;

void setup() {
  pinMode(SENSOR1,INPUT_PULLUP);
  pinMode(SENSOR2,INPUT_PULLUP);
  pinMode(START_BUTTON,INPUT_PULLUP);
  pinMode(LED_BUTTON,OUTPUT);
  pinMode(RELAY,OUTPUT);
  digitalWrite(SENSOR1, HIGH);
  digitalWrite(SENSOR2, HIGH);
  digitalWrite(START_BUTTON, HIGH);
  digitalWrite(LED_BUTTON, HIGH);
  digitalWrite(RELAY, HIGH);
  Serial3.begin(9600);
  Serial.begin(9600);
  myDFPlayer.begin(Serial3);
  dmd.setBrightness(50);
  dmd.selectFont(SystemFont5x7);
  dmd.begin();
  EEPROM.get(0, highscore);
  //if(highscore>999 || highscore<1) {
    highscore=500;
    EEPROM.put(0, highscore);
  //}
  digitalWrite(RELAY,LOW);
  delay(1000);
  myDFPlayer.play(BELL);
  display_on();
  digitalWrite(RELAY,HIGH);
  Serial.println("Fun-Boxing Start");
}

void loop() {
  if(millis()/1000 != cek_millis) {
    cek_millis = millis()/1000;
    Serial.println(st_game);
  }
  
  if(digitalRead(START_BUTTON) == LOW && st_game == 0) {
    delay(50);
    if(digitalRead(START_BUTTON) == LOW) {
      score=0;
      st_game=1;
      dmd.clearScreen();
      dmd.drawString(2, 4, F("READY"));
      delay(50);
    }
  }
  
  if(st_game == 1) {
    myDFPlayer.play(BELL); // start punch sounds
    release_punch(); // punch has to be released perfectly sensor2 in LOW state
    dmd.clearScreen();
    dmd.drawString(8, 4, F("GO!"));
    st_game=2;
  }

  if(st_game == 2 && digitalRead(SENSOR1) == HIGH) {
    punch_millis = millis();
    st_game = 3;
  }
  if(st_game == 3 && digitalRead(SENSOR1) == LOW) {
    st_game = 2;
  }
  
  if(st_game == 3 && digitalRead(SENSOR2) == LOW) {
    delay(10);
    if(digitalRead(SENSOR2) == LOW) {
      punch_time = millis() - punch_millis;
      score = MAXTIME - punch_time;
      if(score < 0) score = 0;
      score = map(score,0, MAXTIME, 0, 999);
      st_game = 4;
    }
  }

  if(st_game == 4) {
    myDFPlayer.play(COUNTING);
    display_counting();
    delay(5000);
    if(score>highscore) {
      myDFPlayer.play(CLAP);
      highscore = score;
      EEPROM.put(0, highscore);
    }
    else {
      myDFPlayer.play(WOO);
    }
    display_result();
    delay(3000);
    st_game=0;
  }
  if(st_game == 0) {
    if(digitalRead(SENSOR2)==HIGH) display_error();
    else {
      if(st_clear==0) { dmd.clearScreen(); st_clear=1; }
      display_normal();
    }
  }
}
