/*
    This file contains the methods related to the 
    'Random Prompts' automatic behavior.
*/

#define N_PHRASES 4
enum randomPromptsStates {
    Start, Move1, Move2, CheckMove, Finishing, Wait
};
    
randomPromptsStates state_prompts, past_state_prompts;
long int _timeStamp;

const char* phrases[N_PHRASES] = {
    "ciao", "bravo", "gioca", "grande"   
};

boolean try_random_prompt() {
    uint16_t t = random(10000,20000);

    if (getInactiveTime() >= t) {
        setBehaviorToExecute(execute_random_prompt);
        state_prompts = Start;
        return true;    
    } 

    return false;
}

boolean execute_random_prompt() {

    uint8_t p = random(N_PHRASES);
//    BTSerial.println("Random Prompts");
    
    switch (state_prompts) {
        
        case Start:
            setHappyMood();
            drawFace();
            state_prompts = Move1;
            break;
            
        case Move1:
            if (!positionCommanded()) {
                rotate(30,2);
                state_prompts = CheckMove;
                past_state_prompts = Move1;
                _timeStamp = millis();
            }
            break;
        case Wait:
            if (millis()-_timeStamp > 2000) {
              state_prompts = Move2;  
            }
            break;
        case Move2:
            if (!positionCommanded()) {
                rotate(-30,2);
                speak(phrases[p]);
                state_prompts = CheckMove;
                past_state_prompts = Move2;
                
            }
            break;

        case CheckMove:
            refreshPositionControl();
            if (!positionCommanded()) {
                if (past_state_prompts == Move1)
                    state_prompts = Wait;
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
