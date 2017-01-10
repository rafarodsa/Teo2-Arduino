#include <Encoder.h>

#define _L        (0.175f)    // Wheel distance from body origin [m]
#define _R         0.035f    // Wheel radius [m]

#define _C60    (0.500000000f)   // cos(60°) 
#define _C30    (0.866025404f)   // cos(30°)
#define _2PI     (6.283185307f)
#define _TICKS_REV (1632.67f)
#define _TOLERANCE  20

#define WHEEL1Y_PIN 2
#define WHEEL1W_PIN 3
#define WHEEL2Y_PIN 18
#define WHEEL2W_PIN 44
#define WHEEL3Y_PIN 19
#define WHEEL3W_PIN 34

Encoder enc1(WHEEL1Y_PIN,WHEEL1W_PIN);
Encoder enc2(WHEEL2Y_PIN,WHEEL2W_PIN);
Encoder enc3(WHEEL3Y_PIN,WHEEL3W_PIN);

//================== BLOCKING METHODS ============================//

// command a rotation of angle (degrees) and wait till is done.
void rotate_wait(float angle) {
        int ticks = (int)((-_L/_R)*(angle*_TICKS_REV/360)); 
        uint8_t _speed = angle < 0? -3:3;
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go(0,0,_speed);

        while (abs(ticks - enc1.read()) > _TOLERANCE);

        Stop();
    }

//command a forward translation of distance meters
void moveForward_wait(float distance) {
        int wheel1, wheel2;
        float _speed = distance > 0? -1:1;
        
        wheel1 = (int)((_C30/_R)*distance*(_TICKS_REV/_2PI));
        wheel2 = (int)((-_C30/_R)*distance*(_TICKS_REV/_2PI));
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (0,_speed,0);
        while ( abs(wheel1-enc1.read()) > _TOLERANCE && abs(wheel2-enc2.read()) > _TOLERANCE );
        Stop();
        
    }


void moveLateral_wait(float distance) {     // positive distance is movement to the right
        int wheel1, wheel2, wheel3;
        float _speed = distance > 0? 1:-1;
        
        wheel1 = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel2 = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel3 = (int)((-1/_R)*distance*(_TICKS_REV/_2PI));
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (_speed,0,0);
        while (abs(wheel1-enc1.read()) > _TOLERANCE && abs(wheel2-enc2.read()) > _TOLERANCE && abs(wheel3-enc3.read()) > _TOLERANCE);
        Stop();
    
    }


//===================== NON-BLOCKING METHODS ==========================

int wheel1_ticks = 0, wheel2_ticks = 0, wheel3_ticks = 0;
boolean commanded = false;

void positionControlInit() {
        commanded = false;
        wheel1_ticks = 0;
        wheel2_ticks = 0;
        wheel3_ticks = 0;
    }

void refreshPositionControl() {
        boolean w1 = false, w2 = false, w3 = false;
        
        if(!commanded) return;
        
        Serial.println("Refreshing..");
        if (wheel1_ticks != 0) {
            Serial.println(abs(wheel1_ticks - enc1.read()));
            if (abs(wheel1_ticks - enc1.read()) < _TOLERANCE) {
                    wheel1_ticks = 0;
                    w1 = true;
                }  
        }
        else 
            w1 = true;

        if (wheel2_ticks != 0) {
            Serial.println(abs(wheel2_ticks - enc2.read()));
            if (abs(wheel2_ticks - enc2.read()) < _TOLERANCE) {
                    wheel1_ticks = 0;
                    w2 = true;
                }  
        }
        else 
            w2 = true;

        if (wheel3_ticks != 0) {
            Serial.println(abs(wheel3_ticks - enc3.read()));
            if (abs(wheel3_ticks - enc3.read()) < _TOLERANCE) {
                    wheel3_ticks = 0;
                    w3 = true;
                }  
        }
        else 
            w3 = true;

        if (w1 || w2 || w3) {
                
                Stop();
                commanded = false;
            }
    }


void rotate (float angle) {
        float _speed = angle < 0? -3:3;
        
        if (commanded) return;

        wheel1_ticks = (int)((-_L/_R)*(angle*_TICKS_REV/360));
        wheel2_ticks = wheel1_ticks;
        wheel3_ticks = wheel1_ticks;
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go(0,0,_speed);

        commanded = true;
    }

void moveAhead(float distance) {
        float _speed = distance > 0? -1:1;
        
        if (commanded) return;
        
        wheel1_ticks = (int)((_C30/_R)*distance*(_TICKS_REV/_2PI));
        wheel2_ticks = (int)((-_C30/_R)*distance*(_TICKS_REV/_2PI));
        wheel3_ticks = 0;
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (0,_speed,0);

        commanded = true;
    }

void moveLateral(float distance) {
    
        float _speed = distance > 0? 1:-1;
        
        if (commanded) return;
        
        wheel1_ticks = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel2_ticks = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel3_ticks = (int)((-1/_R)*distance*(_TICKS_REV/_2PI));
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (_speed,0,0);
        commanded = true;
    }


boolean positionCommanded() {
        return commanded;
    }
