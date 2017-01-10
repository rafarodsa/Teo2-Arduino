#include <SoftwareSerial.h>
#include <SerialCommand.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <MC33887.h>
#include <Triskar.h>
#include "Eyelashes.h"
#include "Eyes.h"
#include "Mouths.h"
#include "Timer.h"

#include <SoftwareSerial.h>
#include <SerialCommand.h>

//#define BTDEBUG
#define BTSerial  Serial3

//PIN
#define RX_PIN 14
#define TX_PIN 15
#define BOTTOMSTRIP_PIN 5
#define TOPSTRIP_PIN 6
#define MATRIX_PIN 4

//RGB colours
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255
#define YELLOW 255, 255, 0
#define PURPLE 255, 0, 255

//Numbers of RGB leds
#define MATRIX_COLUMNS 16
#define MATRIX_ROWS 16
#define TOPSTRIP_LENGHT 14
#define BOTTOMSTRIP_LENGHT 31

Timer timer;

enum MoodStateEnum {
  idle, happy, sad, angry, scared
};
MoodStateEnum moodState = idle;



void setup() {
  movementInit();
  BTCommInit();
  serialCommInit();

  matrixInit();

  topStripInit();
  bottomStripInit();

  timer.every(3000, animateEyes);
  timer.every(4000, animateEyelashes);
  timer.every(4000, animateIdleStrips);
  timer.every(4000, animateHappyStrips);
  timer.every(1000, animateSadStrips);
  timer.every(500, animateAngryStrips);
  timer.every(500, animateScaredStrips);
  timer.every(2000, ready);

  positionControlInit();
}

void loop() {
  timer.update();
  while (positionCommanded()) {
    refreshPositionControl();
  }
  delay(2000);
  rotate(360);

}
