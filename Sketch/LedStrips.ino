Adafruit_NeoPixel topStrip = Adafruit_NeoPixel(TOPSTRIP_LENGHT, TOPSTRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bottomStrip = Adafruit_NeoPixel(BOTTOMSTRIP_LENGHT, BOTTOMSTRIP_PIN, NEO_GRB + NEO_KHZ800);

boolean isTeoBreathingOut = false;


void topStripInit(){
  topStrip.begin();
  topStrip.setBrightness(10);
}

void bottomStripInit(){
  bottomStrip.begin();
  bottomStrip.setBrightness(10);
}

//Turn every third RGB led on
void drawFixedStrips() {

  switch (moodState) {
    case happy:
      for (int i = 0; i < bottomStrip.numPixels(); i = i + 3) {
        bottomStrip.setPixelColor(i, bottomStrip.Color(GREEN));

      }
      for (int i = 0; i < topStrip.numPixels(); i = i + 3) {
        topStrip.setPixelColor(i, topStrip.Color(GREEN));
      }
      break;

    case sad:
      for (int i = 0; i < bottomStrip.numPixels(); i = i + 3) {
        bottomStrip.setPixelColor(i, bottomStrip.Color(PURPLE));

      }
      for (int i = 0; i < topStrip.numPixels(); i = i + 3) {
        topStrip.setPixelColor(i, topStrip.Color(PURPLE));
      }
      break;

    case angry:
      for (int i = 0; i < bottomStrip.numPixels(); i = i + 3) {
        bottomStrip.setPixelColor(i, bottomStrip.Color(RED));

      }
      for (int i = 0; i < topStrip.numPixels(); i = i + 3) {
        topStrip.setPixelColor(i, topStrip.Color(RED));
      }
      break;

    case scared:
      for (int i = 0; i < bottomStrip.numPixels(); i = i + 3) {
        bottomStrip.setPixelColor(i, bottomStrip.Color(BLUE));

      }
      for (int i = 0; i < topStrip.numPixels(); i = i + 3) {
        topStrip.setPixelColor(i, topStrip.Color(BLUE));
      }
      break;

    default:
      for (int i = 0; i < bottomStrip.numPixels(); i = i + 3) {
        bottomStrip.setPixelColor(i, bottomStrip.Color(YELLOW));

      }
      for (int i = 0; i < topStrip.numPixels(); i = i + 3) {
        topStrip.setPixelColor(i, topStrip.Color(YELLOW));
      }
  }

  bottomStrip.show();
  topStrip.show();
}

//Turn every third RGB led on in a way that it seems Teo is breathing
//Obs: you must not use setBrightness method as animation. Use colorPercentage of setPixelColor method
void drawBreathingStrips() {
  int red, green, blue = 0;

  switch (moodState) {
    case happy:
      //GREEN
      red = 0;
      green = 1;
      blue = 0;
      break;

    case sad:
      //PURPLE
      red = 1;
      green = 0;
      blue = 1;
      break;

    case angry:
      //RED
      red = 1;
      green = 0;
      blue = 0;
      break;

    case scared:
      //BLUE
      red = 0;
      green = 0;
      blue = 1;
      break;

    default:
      //YELLOW
      red = 1;
      green = 1;
      blue = 0;
  }


  if (isTeoBreathingOut == true) {
    for (int colorPercentage = 0; colorPercentage <= 255; colorPercentage = colorPercentage + 2) {
      for (int i = 0; i < bottomStrip.numPixels(); i = i + 3) {
        bottomStrip.setPixelColor(i, bottomStrip.Color(colorPercentage * red, colorPercentage * green, colorPercentage * blue));
      }
      for (int i = 0; i < topStrip.numPixels(); i = i + 3) {
        topStrip.setPixelColor(i, topStrip.Color(colorPercentage * red, colorPercentage * green, colorPercentage * blue));
      }
      bottomStrip.show();
      topStrip.show();
    }

    isTeoBreathingOut = false;

  } else {
    for (int colorPercentage = 255; colorPercentage >= 0; colorPercentage = colorPercentage - 2) {
      for (int i = 0; i < bottomStrip.numPixels(); i = i + 3) {
        bottomStrip.setPixelColor(i, bottomStrip.Color(colorPercentage * red, colorPercentage * green, colorPercentage * blue)); //turn every third pixel on
      }
      for (int i = 0; i < topStrip.numPixels(); i = i + 3) {
        topStrip.setPixelColor(i, topStrip.Color(colorPercentage * red, colorPercentage * green, colorPercentage * blue)); //turn every third pixel on
      }
      bottomStrip.show();
      topStrip.show();
    }

    isTeoBreathingOut = true;

  }
}

