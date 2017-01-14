#include "TeoState.h"

uint16_t distance_to_person;
InteractionRegion CurrentRegion, PastRegion;
ContactType lastTouch;

// This function should be call to update the current state of the Teo through its sensors. 
// Here should be added the function calls related to each sensor.

void refreshTeoState() {
        refreshDistanceToPerson();
    }


void refreshDistanceToPerson() {
        distance_to_person = measure_distance();
        PastRegion = CurrentRegion;
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
