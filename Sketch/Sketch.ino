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

#define MATRIX_PIN 4
//#define BTDEBUG
#define BTSerial  Serial3

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, MATRIX_PIN, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ZIGZAG + NEO_MATRIX_ROWS, NEO_GRB + NEO_KHZ800);

const uint16_t green = matrix.Color(0, 200, 0);
const uint16_t blue = matrix.Color(0, 0, 200);
const uint16_t yellow = matrix.Color(150, 150, 0);
const uint16_t red = matrix.Color(190, 50, 50);
const uint16_t purple = matrix.Color(186, 85, 211);

Timer timer;

enum MoodStateEnum {
  neutral, happy, sad, angry, scared
};
MoodStateEnum moodState = neutral;

//Animation states in happy mood
enum HappyAnimationStateEnum {
  happyCenter = 0,
  happyLeft = 1,
  happyRight = 2,
  happyClosed = 3
};
HappyAnimationStateEnum happyAnimationState = happyCenter;

//Animation states in sad mood
enum SadAnimationStateEnum {
  sadCenter = 0,
  sadLeft = 1,
  sadRight = 2,
  sadClosed = 3
};
SadAnimationStateEnum sadAnimationState = sadCenter;

//Animation states in angry mood
enum AngryAnimationStateEnum {
  angryCenter = 0,
  angryLeft = 1,
  angryRight = 2,
  angryClosed = 3
};
AngryAnimationStateEnum angryAnimationState = angryCenter;

//Animation states in scared mood
enum ScaredAnimationStateEnum {
  scaredCenter = 0,
  scaredLeft = 1,
  scaredRight = 2,
  scaredClosed = 3
};
ScaredAnimationStateEnum scaredAnimationState = scaredCenter;

void setNeutralMood() {
#ifdef BTDEBUG
  BTSerial.println("Mood changing to neutral...");
#endif

  moodState = neutral;
  drawFace(); //in neutral mood there are no animations
}

void setHappyMood() {
#ifdef BTDEBUG
  BTSerial.println("Mood changing to happy...");
#endif
  moodState = happy;
}

void setSadMood() {
#ifdef BTDEBUG
  BTSerial.println("Mood changing to sad...");
#endif
  moodState = sad;
}

void setAngryMood() {
#ifdef BTDEBUG
  BTSerial.println("Mood changing to angry...");
#endif
  moodState = angry;
}

void setScaredMood() {
#ifdef BTDEBUG
  BTSerial.println("Mood changing to scared...");
#endif
  moodState = scared;
}

void animateEyes() {
#ifdef BTDEBUG
  BTSerial.println("Eyes animation...");
#endif
  switch (moodState) {
    case happy:
#ifdef BTDEBUG
      BTSerial.println("Happy eyes animation...");
#endif
      happyAnimationState = (rand() % 3); //random happyCenter/happyLeft/happyRight
      drawFace();
      break;

    case sad:
#ifdef BTDEBUG
      BTSerial.println("Sad eyes animation...");
#endif
      sadAnimationState = (rand() % 3); //random sadCenter/sadLeft/sadRight
      drawFace();
      break;

    case angry:
#ifdef BTDEBUG
      BTSerial.println("Angry eyes animation...");
#endif
      angryAnimationState = (rand() % 3); //random angryCenter/angryLeft/angryRight
      drawFace();
      break;

    case scared:
#ifdef BTDEBUG
      BTSerial.println("Scared eyes animation...");
#endif
      scaredAnimationState = (rand() % 3); //random scaredCenter/scaredLeft/scaredRight
      drawFace();
      break;
  }
}

//Blinking animation
void animateEyelashes() {
#ifdef BTDEBUG
  BTSerial.println("Eyelashes animation...");
#endif
  switch (moodState) {
    case happy:
#ifdef BTDEBUG
      BTSerial.println("Happy eyelashes animation...");
#endif
      //random blink/no blink (3/0)
      if (((rand() % 2) * 3) == happyClosed) {
        HappyAnimationStateEnum lastHappyAnimationState = happyAnimationState;
        happyAnimationState = happyClosed;
        //blink
        for (int i = 0; i < 10; i++) {
          drawFace();
        }
        happyAnimationState = lastHappyAnimationState;
        drawFace();

      }
      break;

    case sad:
#ifdef BTDEBUG
      BTSerial.println("Sad eyelashes animation...");
#endif
      //random blink/no blink (3/0)
      if (((rand() % 2) * 3) == sadClosed) {
        SadAnimationStateEnum lastSadAnimationState = sadAnimationState;
        sadAnimationState = sadClosed;
        //blink
        for (int i = 0; i < 10; i++) {
          drawFace();
        }
        sadAnimationState = lastSadAnimationState;
        drawFace();
      }
      break;

    case angry:
#ifdef BTDEBUG
      BTSerial.println("Angry eyelashes animation...");
#endif
      //random blink/no blink (3/0)
      if (((rand() % 2) * 3) == angryClosed) {
        AngryAnimationStateEnum lastAngryAnimationState = angryAnimationState;
        angryAnimationState = angryClosed;
        //blink
        for (int i = 0; i < 10; i++) {
          drawFace();
        }
        angryAnimationState = lastAngryAnimationState;
        drawFace();
      }
      break;

    case scared:
#ifdef BTDEBUG
      BTSerial.println("Scared eyelashes animation...");
#endif
      //random blink/no blink (3/0)
      if (((rand() % 2) * 3) == scaredClosed) {
        ScaredAnimationStateEnum lastScaredAnimationState = scaredAnimationState;
        scaredAnimationState = scaredClosed;
        //blink
        for (int i = 0; i < 10; i++) {
          drawFace();
        }
        scaredAnimationState = lastScaredAnimationState;
        drawFace();
      }
      break;
  }
}

void setup() {
  movementInit();
  BTCommInit();
  Serial.begin(9600);
  Serial.println("Init!");

  matrix.begin();
  matrix.setBrightness(10);

  //Initialize the mood
  setNeutralMood();

  //TODO: verify if timer conflicts with peripherals
  //Every 3 seconds an animation occurs
  timer.every(3000, animateEyes);
  timer.every(4000, animateEyelashes);
  timer.every(2000, imalive);
}

void loop() {
  timer.update();
}
