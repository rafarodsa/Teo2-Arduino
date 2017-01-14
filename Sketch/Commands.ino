#ifdef BTSerial
SerialCommand CommandHandler;
#else
SoftwareSerial BTSerial(RX_PIN, TX_PIN);
SerialCommand CommandHandler(BTSerial);
#endif

//Initialization
void serialCommInit() {
  Serial.begin(9600);
  Serial.println(F("Init!"));
}

void BTCommInit() {
  BTSerial.begin(9600);
  CommandHandler.addCommand("move", moveHandler);
  CommandHandler.addCommand("idle", setIdleMood);
  CommandHandler.addCommand("happy", setHappyMood);
  CommandHandler.addCommand("sad", setSadMood);
  CommandHandler.addCommand("angry", setAngryMood);
  CommandHandler.addCommand("scared", setScaredMood);

  CommandHandler.addDefaultHandler(unrecognized);
#ifdef BTDEBUG
  BTSerial.println(F("Init!");
#endif
}

void ready() {
  BTSerial.println(F("ready"));
}

//Update call
void listenCommand() {
  uint8_t i;
  char buf[32];
  CommandHandler.readSerial();
}

// Callbacks
void moveHandler() {
  char* args;
  float params[3];
  uint8_t i, j;

#ifdef BTDEBUG
  BTSerial.print8_t(F("move "));
#endif

  for (i = 0, j = 0; i < 3; i++) {
    args = CommandHandler.next();
    if (args != NULL) {
      params[i] = atof(args);
      j++;

#ifdef BTDEBUG
      BTSerial.pruint8_t(args);
      BTSerial.pruint8_t(F(" "));
#endif

    }

#ifdef BTDEBUG
    else {
      BTSerial.pruint8_t(F(" NULL"));
    }
#endif
  }

  if (j == 3) {

    Go(params[0], params[1], params[2]);
#ifdef BTDEBUG
    BTSerial.println(F("Moving..."));
    delay(500);
    Stop();
    BTSerial.println(F("Stopped!"));
#endif
  }
}

void setIdleMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to idle..."));
#endif
  moodState = idle;
}

void setHappyMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to happy..."));
#endif
  moodState = happy;
}

void setSadMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to sad..."));
#endif
  moodState = sad;
}

void setAngryMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to angry..."));
#endif
  moodState = angry;
}

void setScaredMood() {
#ifdef BTDEBUG
  BTSerial.println(F("Mood changing to scared..."));
#endif
  moodState = scared;
}

void unrecognized() {
#ifdef BTDEBUG
  BTSerial.println(F("Command not recognized"));
#endif
  return;
}

void serialEvent3() {
  while (BTSerial.available() > 0)
    listenCommand();
}
