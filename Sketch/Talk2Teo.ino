#define EXECUTING   true
#define EXIT        false

typedef boolean _talk2teoIn;

enum _talk2teoState {
        sense, verifyRules, manualExecute, chooseBehavior, behaviorExecute
    };

_talk2teoState currentState = sense;
_talk2teoIn behaviorExecuting, commandReceived, commandEnded;
boolean (*behaviorToExecute)();


boolean Talk2Teo() {

        switch (currentState) {
                case sense:
                    talk2teo_sense();
                    break;

                case verifyRules:
                    talk2teo_verifyRules();
                    break;

                case manualExecute:
                    talk2teo_manualExecute();
                    break;

                case chooseBehavior:
                    talk2teo_chooseBehavior();
                    break;

                case behaviorExecute:
                    talk2teo_behaviorExecute();
                    break;
            
            }

            return EXECUTING;
    }


void talk2teo_sense() {

    refreshTeoState();
    
    if (commandReceived && !behaviorExecuting) currentState = manualExecute;
    else currentState = verifyRules;
}

void talk2teo_verifyRules() {

    not_move_when_close();      // Verify and ensure the robot does not move when the child's close.

    if (behaviorExecuting) currentState = behaviorExecute;
    else currentState = chooseBehavior;
}

void talk2teo_manualExecute() {

    
    if (commandEnded) currentState = sense;
    else currentState = manualExecute;
}

void talk2teo_chooseBehavior() {
    
    currentState = behaviorExecute;
    
    if (try_look_for_the_child())
        return;
     
        
}

void talk2teo_behaviorExecute() {
    if (behaviorToExecute())
        behaviorExecuting = false;
    behaviorExecuting = true;
    currentState = sense;
}

void setBehaviorToExecute(boolean (*behavior)()) {
        behaviorToExecute = behavior;
    }
