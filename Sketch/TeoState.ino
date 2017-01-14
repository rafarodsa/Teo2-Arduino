#include "TeoState.h"

uint16_t distance_to_person;
InteractionRegion CurrentRegion, PastRegion;
ContactType lastTouch;
boolean isSpeaking;

// This function should be call to update the current state of the Teo through its sensors. 
// Here should be added the function calls related to each sensor.

void refreshTeoState() {
        refreshDistanceToPerson();
    }

//==================== DISTANCE RELATED FUNCTIONS =========================
void refreshDistanceToPerson() {
        distance_to_person = measure_distance();
        PastRegion = CurrentRegion;         //TODO: Check if this is right 
        CurrentRegion = determineInteractionRegion(distance_to_person);
    }

uint16_t distanceToPerson() {
        return distance_to_person;
    }

uint8_t determineInteractionRegion(uint16_t _distance) {

        if (_distance < 45) return Intimate;
        if (_distance >= 45 && _distance < 120) return Personal;
        if (_distance >= 120 && _distance < 300) return Social;
        if (_distance >= 300 && _distance < 401) return Public;
        return Unknown;
    
    }

uint8_t getCurrentRegion() {
        return CurrentRegion;
    }

uint8_t getPastRegion() {
        return PastRegion;
    }

//======================================================================== 

//=================== VOICE CONTROL ======================================

void endOfSpeech() {
        isSpeaking = false;
    }

void setIsSpeaking(boolean x) {
        isSpeaking = true;
    }
boolean isTeoSpeaking() {
        return isSpeaking;
    }
