#define BTSerial  Serial3
//#define BTDEBUG


#ifdef BTSerial
SerialCommand CommandHandler;
#else
SoftwareSerial BTSerial(14, 15); // (RX,TX)
SerialCommand CommandHandler(BTSerial);
#endif

//Initialization
void BTCommInit() {
  BTSerial.begin(9600);
  CommandHandler.addCommand("move", moveHandler);
  CommandHandler.addCommand("happy", setHappyMood);
  CommandHandler.addCommand("sad", setSadMood);
  CommandHandler.addCommand("angry", setAngryMood);
  CommandHandler.addCommand("scared", setScaredMood);
  CommandHandler.addDefaultHandler(unrecognized);
#ifdef BTDEBUG
  BTSerial.println("Init!");
#endif
}

void imalive() {
  Serial.println("Send command");
#ifdef BTDEBUG
  BTSerial.println("I'm alive!");
#endif
}

//Update call
void listenCommand() {
  int i;
  char buf[32];
  CommandHandler.readSerial();
}

// Callbacks
void moveHandler() {
  char* args;
  float params[3];
  int i, j;

#ifdef BTDEBUG
  BTSerial.print("move ");
#endif

  for (i = 0, j = 0; i < 3; i++) {
    args = CommandHandler.next();
    if (args != NULL) {
      params[i] = atof(args);
      j++;

#ifdef BTDEBUG
      BTSerial.print(args);
      BTSerial.print(" ");
#endif

    }

#ifdef BTDEBUG
    else {
      BTSerial.print(" NULL");
    }
#endif
  }

  if (j == 3) {

    Go(params[0], params[1], params[2]);
#ifdef BTDEBUG
    BTSerial.println("Moving...");
    delay(500);
    Stop();
    BTSerial.println("Stopped!");
#endif
  }

}

void unrecognized() {
#ifdef BTDEBUG
  BTSerial.println("Command not recognized");
#endif
  return;
}

void serialEvent3() {
  while (BTSerial.available() > 0)
    listenCommand();
}
