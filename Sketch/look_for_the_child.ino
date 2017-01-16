/*
    This file contains the methods related to the 'Look for the
    child' automatic behavior.
*/



enum lookForTheChildStates {
    Init, MoveLeft, MoveRight, CheckMovement, Finish
};
    
lookForTheChildStates state, past_state;
long int _timestamp;
//Returns true if the conditions are set to execute behavior.
boolean try_look_for_the_child() {
        InteractionRegion current = getCurrentRegion();
        InteractionRegion past = getPastRegion();
        
        if (past < Social && current >= Social) {
            setBehaviorToExecute(execute_look_for_the_child);
            state = Init;
            return true;    
        }

        if (past >= Social && current < Social) {
            setBehaviorToExecute(execute_child_returns);
            state = Init;
            return true;
        }
        
        return false;
    }

// Returns true when is done executing the behavior
boolean execute_look_for_the_child() {
    
    switch (state) {
        
        case Init:
            setSadMood();
            drawFace();
            state = MoveLeft;
            break;
            
        case MoveLeft:
            if (!positionCommanded()) {
                rotate(60,2);
                state = CheckMovement;
                past_state = MoveLeft;
            }
            break;
            
        case MoveRight:
            if (!positionCommanded()) {
                rotate(-120,2);
                speak("Dove sei?");
                state = CheckMovement;
                past_state = MoveRight;
            }
            break;

        case CheckMovement:
            refreshPositionControl();
            if (!positionCommanded()) {
                    if (past_state == MoveLeft)
                        state = MoveRight;
                     else {  
                        state = Finish;
                        _timestamp = millis();
                     }
                }
             break;
         case Finish:
            if (!isMoving() && !isTeoSpeaking())
                return true;
            break;
    }

    return false;
}


// 

boolean execute_child_returns () {
       Serial.println("ChildReturns");
        switch (state) {
            
            case Init:
                setHappyMood();
                state = MoveLeft;
                break;
                
            case MoveLeft:
                if (!positionCommanded()) {
                    rotate(60,3);
                    speak("gioca");
                    state = CheckMovement;
                    past_state = MoveLeft;
                }
                break;
                
            case CheckMovement:
                refreshPositionControl();
                if (!positionCommanded()) {
                         state = Finish;
                 }
                 break;
             case Finish:
                if (!isMoving() && !isTeoSpeaking())
                    return true;
                break;
        }

        return false;        
    }
