#ifdef USING_NEOPIXEL

// Define LED_BRIGHTNESS variable
const byte LED_BRIGHTNESS = 255;

// Define DIM_BRIGHTNESS variable
const byte DIM_BRIGHTNESS = LED_BRIGHTNESS / 2;

// Define individual hue variables
byte lightPurpleHue = 192;
byte lightPurple2Hue = 205;
byte redHue = 0;
byte orangeHue = 30;
byte yellowHue = 60;
byte greenHue = 130;
byte green2Hue = 115;
byte cyanHue = 160;
byte blueHue = 175;
byte purpleHue = 5;
byte magentaHue = 220;
byte whiteHue = 0; // Full brightness white

// Define a two-dimensional array of colors with full and half brightness

CHSV colorArray[24][2] = {
  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 0)
  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 1)
  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 2)
  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 3)

  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 4)
  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 5)
  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 6)
  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 7)

  { CHSV(blueHue, 255, LED_BRIGHTNESS), CHSV(blueHue, 255, DIM_BRIGHTNESS) },      // (index 8)
  { CHSV(yellowHue, 255, LED_BRIGHTNESS), CHSV(yellowHue, 255, DIM_BRIGHTNESS) },  // (index 9)
  { CHSV(redHue, 255, LED_BRIGHTNESS), CHSV(redHue, 255, DIM_BRIGHTNESS) },        // (index 10)
  { CHSV(whiteHue, 0, LED_BRIGHTNESS), CHSV(whiteHue, 0, DIM_BRIGHTNESS) },        // (index 11)

  { CHSV(green2Hue, 255, LED_BRIGHTNESS), CHSV(green2Hue, 255, DIM_BRIGHTNESS) },  // (index 12)
  { CHSV(green2Hue, 255, LED_BRIGHTNESS), CHSV(green2Hue, 255, DIM_BRIGHTNESS) },  // (index 13)
  { CHSV(greenHue, 255, LED_BRIGHTNESS), CHSV(greenHue, 255, DIM_BRIGHTNESS) },    // (index 14)
  { CHSV(greenHue, 255, LED_BRIGHTNESS), CHSV(greenHue, 255, DIM_BRIGHTNESS) },    // (index 15)

  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 16)
  { CHSV(lightPurpleHue, 255, LED_BRIGHTNESS), CHSV(lightPurpleHue, 255, DIM_BRIGHTNESS) },  // (index 17)
  { CHSV(lightPurple2Hue, 255, LED_BRIGHTNESS), CHSV(lightPurple2Hue, 255, DIM_BRIGHTNESS) },  // (index 18)
  { CHSV(lightPurple2Hue, 255, LED_BRIGHTNESS), CHSV(lightPurple2Hue, 255, DIM_BRIGHTNESS) },  // (index 19)

  { CHSV(redHue, 255, LED_BRIGHTNESS), CHSV(redHue, 255, DIM_BRIGHTNESS) },      // (index 20)
  { CHSV(yellowHue, 255, LED_BRIGHTNESS), CHSV(yellowHue, 255, DIM_BRIGHTNESS) },  // (index 21)
  { CHSV(greenHue, 255, LED_BRIGHTNESS), CHSV(greenHue, 255, DIM_BRIGHTNESS) },    // (index 22)
  { CHSV(redHue, 255, LED_BRIGHTNESS), CHSV(redHue, 255, DIM_BRIGHTNESS) }         // (index 23)
};




// Define an array to map LED indices to pins
int ledPin[] = { 0, 1, 2, 3,
                 4, 5, 6, 7,
                 10, 11, 12, 13,
                 14, 15, 16, 17,
                 18, 19, 20, 8,
                 21, 22, 23, 9 };

#endif
