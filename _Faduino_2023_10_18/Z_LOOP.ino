void loop() {

  // Serial.println(faderMin[0]);
  // Serial.println(faderMax[0]);

#ifdef ATMEGA32U4

  // it will read MIDI incoming messages if using ATMEGA32U4
  MIDIread();

#endif

#ifdef TEENSY

  // usbMIDI.read() needs to be called rapidly from loop().  When
  // each MIDI messages arrives, it return true.  The message must
  // be fully processed before usbMIDI.read() is called again.
  if (usbMIDI.read()) {
    processMIDI();
  }

#endif

#ifdef USING_BUTTONS

  // Get the current time
  unsigned long buttonsCurrentMillis = millis();

  // Check if it's time to run the function
  if (buttonsCurrentMillis - buttonsPreviousMillis >= buttonsInterval) {
    // Save the last time the function was run
    buttonsPreviousMillis = buttonsCurrentMillis;
    // Call your function here
    buttons();
  }

#endif

#ifdef USING_POTENTIOMETERS
  potentiometers();
#endif

#ifdef USING_ENCODER
  encoders();
  isEncoderMoving();

#endif

/////////////////////////////////////////////
// MOTORIZED FADERS
#ifdef USING_MOTORIZED_FADERS

  for (int i = 0; i < N_M_FADERS; i++) {

    touchLine[i] = capSense[i].capacitiveSensor(capSenseSpeed);
    checkTouch(i, touchLine[i]);

    int reading = analogRead(POT_ARDUINO_PIN[i]);
    responsivePot[i].update(reading);
    potCState[i] = responsivePot[i].getValue();

    //int val = abs(actualPos - potCState[i]);

    updateFader(i, faderPos[i]);

    //     if (val != prevMtrVal || recevingMidi == true) {
    //       updateFader(i, faderPos[i]);

    // #ifdef DEBUG
    //       Serial.print("i: ");
    //       Serial.print(i);
    //       Serial.print(", potCState: ");
    //       Serial.print(potCState[i]);
    //       Serial.print(", actualPos: ");
    //       Serial.print(actualPos);
    //       Serial.print(", val: ");
    //       Serial.println(val);
    // #endif

    //       prevMtrVal = val;
    //     }
  }

#endif  // USING_MOTORIZED_FADERS
}
