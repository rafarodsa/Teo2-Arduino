/*
    This file contains the methods related to the 
    'Random Prompts' automatic behavior.
*/

#define N_PHRASES 5
enum randomPromptsStates {
    Start, Move1, Move2, CheckMove, Finishing
};
    
randomPromptsStates state_prompts, past_state_prompts;

const char* phrases[N_PHRASES] = {
    "Mi racconti una storia?", "Uff", "C'e qualcuno?", "Ciao", "Giochi con me?"    
};

boolean try_random_prompt() {
    uint16_t t = random(5000,10000);

    if (getInactiveTime() >= t) {
        setBehaviorToExecute(execute_random_prompt);
        state_prompts = Start;
        return true;    
    } 

    return false;
}

boolean execute_random_prompt() {

    uint8_t p = random(N_PHRASES);
    
    switch (state_prompts) {
        
        case Start:
            setHappyMood();
            state_prompts = Move1;
            break;
            
        case Move1:
            if (!positionCommanded()) {
                rotate(30,3);
                state_prompts = CheckMove;
                past_state_prompts = Move1;
            }
            break;
            
        case Move2:
            if (!positionCommanded()) {
                rotate(-30,3);
                speak(phrases[p]);
                state_prompts = CheckMove;
                past_state_prompts = Move2;
            }
            break;

        case CheckMove:
            refreshPositionControl();
            if (!positionCommanded()) {
                if (past_state_prompts == MoveLeft)
                    state_prompts = Move2;
                 else 
                    state_prompts = Finishing;
            }
             break;
         case Finishing:
            if (!isMoving() && !isTeoSpeaking())
                return true;
            break;
    }

    return false;
}
