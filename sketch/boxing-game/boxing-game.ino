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
 *            - driver or relay for punch actuator / releaser :  6
 */
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
  pinMode(SENSOR1,INPUT_PULLUP);
  pinMode(SENSOR2,INPUT_PULLUP);
  pinMode(START_BUTTON,INPUT_PULLUP);
  pinMode(LED_BUTTON,OUTPUT);
  pinMode(ACTUATOR,OUTPUT);
  digitalWrite(SENSOR1, HIGH);
  digitalWrite(SENSOR2, HIGH);
  digitalWrite(START_BUTTON, HIGH);
  digitalWrite(LED_BUTTON, HIGH);
  digitalWrite(ACTUATOR, HIGH);
  Serial3.begin(9600);
  myDFPlayer.begin(Serial3);
}

void loop() {
  if(START_BUTTON == LOW && st_game == 0) {
    delay(50);
    if(START_BUTTON == LOW) {
      score=0;
      st_game=1;
      delay(50);
    }
  }
  
  if(st_game == 1) {
    release_punch(); // punch has to be released perfectly sensor2 in LOW state
    myDFPlayer.play(1); // start punch sounds
    st_game=2;
  }

  if(st_game == 2 && SENSOR2 == HIGH) {
    punch_millis = millis();
    st_game = 3;
  }
  if(st_game == 3 && SENSOR2 == LOW) {
    st_game = 2;
  }
  
  if(st_game == 3 && SENSOR1 == LOW) {
    delay(10);
    if(SENSOR1 == LOW) {
      punch_time = millis() - punch_millis;
      score = LIMIT_TIME - punch_time;
      if(score < 0) score = 0;
      score = map(score,0, MAXTIME, 0, 999);
      st_game = 4;
    }
  }

  if(st_game == 4) {
    myDFPlayer.play(COUNTING);
    display_counting();
  }
  
}
