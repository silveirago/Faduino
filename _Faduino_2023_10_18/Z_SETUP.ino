void setup() {

  // Baud Rate
  // use if using with ATmega328 (uno, mega, nano...)
  // 31250 for MIDI class compliant | 115200 for Hairless MIDI

#ifdef ATMEGA32U4

#ifdef DEBUG
  // while (!Serial) {
  //   Serial.println("waiting...");
  // }
  Serial.println();

  Serial.begin(115200);
  Serial.println("Debug mode");
  Serial.println();
#endif

#endif  //ATMEGA32U4

  //delay(100);

#ifdef USING_NEOPIXEL

  ////////////////////////////////////
  //FAST LED
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  //FastLED.setBrightness(BRIGHTNESS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[ledPin[i]] = colorArray[i][1];
  }
  FastLED.show();

  leds[ledPin[encoderSelect]] = CHSV(magentaHue, 255, LED_BRIGHTNESS);
  FastLED.show();

  //////////////////////////////////////

#endif

  //////////////////////////////////////
  // Buttons
#ifdef USING_BUTTONS

  // Initialize buttons with pull up resistors
  for (int i = 0; i < N_BUTTONS_ARDUINO; i++) {
    pinMode(BUTTON_ARDUINO_PIN[i], INPUT_PULLUP);
  }

#endif  //USING_BUTTONS


  //////////////////////////////////////
  // Potentiometer

#ifdef USING_POTENTIOMETERS

  for (int i = 0; i < N_POTS; i++) {
    responsivePot[i] = ResponsiveAnalogRead(0, true, snapMultiplier);
    responsivePot[i].setAnalogResolution(potMax + 1);  // sets the resolution
  }


#endif

  /////////////////////////////////////////////
  // Multiplexers

#ifdef USING_MUX

  // Initialize the multiplexers
  for (int i = 0; i < N_MUX; i++) {
    mux[i].begin();
  }
  //* Set each X pin as input_pullup (avoid floating behavior)
  pinMode(x1, INPUT_PULLUP);
  pinMode(x2, INPUT_PULLUP);

#endif


  /////////////////////////////////////////////
  // Encoders
#ifdef USING_ENCODER

  for (int i = 0; i < N_ENCODERS; i++) {  // if you want to start with a certain value use presets
    encoder[i].write(preset[0][i]);
  }

  for (int z = 0; z < N_ENCODER_MIDI_CHANNELS; z++) {
    for (int i = 0; i < N_ENCODERS; i++) {
      lastEncoderValue[z][i] = preset[z][i];
      encoderValue[z][i] = preset[z][i];
    }
  }

#endif

  /////////////////////////////////////////////
  // MOTORIZED FADERS
#ifdef USING_MOTORIZED_FADERS

  for (int i = 0; i < N_M_FADERS; i++) {
    pinMode(motorUpPin[i], OUTPUT);
    pinMode(motorDownPin[i], OUTPUT);
    pinMode(faderSpeedPin[i], OUTPUT);
    analogWrite(faderSpeedPin[i], 255);

    //capSense[i] = CapacitiveSensor(touchSendPin[i], touchReceivePin[i]);

    calibrateFader(i);
  }

#ifdef DEBUG
  Serial.println("Faders Calibrated");
  Serial.println();
#endif

#endif  // USING_MOTORIZED_FADERS
}
