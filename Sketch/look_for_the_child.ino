

enum machineStates {
        Init, MoveLeft, MoveRight, CheckMovement, Finish
    };
    
machineStates state, past_state;

//Returns true if the conditions are set to execute behavior.
boolean try_look_for_the_child() {
        InteractionRegion current = getCurrentRegion();
        InteractionRegion past = getPastRegion();
        
        if (past == Social && current == Unknown) {
            setBehaviorToExecute(execute_look_for_the_child);
            state = Init;
            return true;    
        }

        if (past == Unknown && current == Social) {
            setBehaviorToExecute(execute_child_returns);
            state = Init;
        }
        
        return false;
    }

// Returns true when is done executing the behavior
boolean execute_look_for_the_child() {
        switch (state) {
            
            case Init:
                setSadMood();
                state = MoveLeft;
                break;
                
            case MoveLeft:
                if (!positionCommanded()) {
                    rotate(60,3);
                    state = CheckMovement;
                    past_state = MoveLeft;
                }
                break;
                
            case MoveRight:
                if (!positionCommanded()) {
                    rotate(-120,3);
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
                         else 
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


// 

boolean execute_child_returns () {
        switch (state) {
            
            case Init:
                setHappyMood();
                state = MoveLeft;
                break;
                
            case MoveLeft:
                if (!positionCommanded()) {
                    rotate(60,3);
                    speak("Giochi con me?");
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
