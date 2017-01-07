#include <Encoder.h>

#define _L        0.125f    // Wheel distance from body origin [m]
#define _R        0.035f    // Wheel radius [m]

#define _C60    (0.500000000f)   // cos(60°) 
#define _C30    (0.866025404f)   // cos(30°)
#define _2PI     (6.283185307f)
#define _TICKS_REV (1632.67f)
#define _TOLERANCE  5

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
        uint8_t _speed = angle > 0? -3:3;
        
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
        uint8_t _speed = distance > 0? -1:1;
        
        wheel1 = (int)((-_C30/_R)*distance*(_TICKS_REV/_2PI));
        wheel2 = (int)((_C30/_R)*distance*(_TICKS_REV/_2PI));
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (0,_speed,0);
        while ( abs(wheel1-enc1.read()) > _TOLERANCE || abs(wheel2-enc2.read()) > _TOLERANCE );
        Stop();
        
    }


void moveLateral_wait(float distance) {
        int wheel1, wheel2, wheel3;
        uint8_t _speed = distance > 0? 1:-1;
        
        wheel1 = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel2 = (int)((_C60/_R)*distance*(_TICKS_REV/_2PI));
        wheel3 = (int)((-1/_R)*distance*(_TICKS_REV/_2PI));
        
        enc1.write(0);
        enc2.write(0);
        enc3.write(0);

        Go (_speed,0,0);
        while (abs(wheel1-enc1.read()) > _TOLERANCE || abs(wheel2-enc2.read()) > _TOLERANCE || abs(wheel3-enc3.read()) > _TOLERANCE);
        Stop();
    
    }


//===================== NON-BLOCKING METHODS ==========================

int wheel1_ticks = 0, wheel2_ticks = 0, wheel3_ticks = 0;
