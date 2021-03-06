/*
  Triskar.h - Library for controlling the Triskar robot.
  Created by Martino Migliavacca, August 2, 2013.
  Released into the public domain.
  Modification made by Julian Angel
	-variables dth1, dth2 and dth2 now are global variables
	-add of new methods to get the points
*/

#ifndef Triskar_h
#define Triskar_h

#include "Arduino.h"
#include "MC33887.h"

class Triskar
{
private:
  float dth1;
  float dth2;
  float dth3;
#define _MAX_DTH  36.0f     // Maximum wheel angular speed [rad/s]
#define _MAX_SP   255.0f   // Maximum setpoint
#define _SP_SCALE (_MAX_SP / _MAX_DTH)  
public:
  Triskar(MC33887 & m1, MC33887 & m2, MC33887 & m3);
  void run(float strafe, float forward, float angular);
  void runM(float m1, float m2, float m3);
  void stop(void);  
  MC33887 & _m1;
  MC33887 & _m2;
  MC33887 & _m3;
  float getM1();
  float getM2();
  float getM3();
  float get_SP_SCALE();
};

#endif /* Triskar_h */
