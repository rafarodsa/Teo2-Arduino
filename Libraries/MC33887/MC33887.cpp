/*
  MC33887.cpp - Library for controlling the Pololu MC33887 motor driver.
  Created by Martino Migliavacca, August 2, 2013.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MC33887.h"

MC33887::MC33887(byte d2, byte in1, byte in2)
: _d2(d2), _in1(in1), _in2(in2)
{
  pinMode(_d2, OUTPUT);
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
}

void MC33887::set(int pwm) {
	/*Serial.println("-------------------------motore--------------------------");
	Serial.println("sono all'inizio di set motori, e pwm è: ");
	Serial.println(pwm);*/
  if (pwm > 255) pwm = 255;
  if (pwm < -255) pwm = -255;
  
  if (pwm >= 0) {
    digitalWrite(_in2, LOW);
    digitalWrite(_in1, HIGH);
    analogWrite(_d2, pwm);
	//Serial.println("sono nel set motori e ho in1 alto, in2 basso");
  } else {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    analogWrite(_d2, -pwm);
	//Serial.println("sono nel set motori e ho in1 basso, in2 alto");
  }

}

void MC33887::stop(void) {
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, LOW);
  analogWrite(_d2, 0);
}
