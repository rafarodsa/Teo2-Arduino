//Here add the functions to verify and ensure the rules that are to be always satisfied


//This avoid moving when the kid is close to Teo. (Safety rule)
void not_move_when_close() {
    
    if (isMoving() && distanceToPerson() < 100) {
            Stop();
        }
        
}
