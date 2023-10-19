#ifdef USING_BUTTONS

/////////////////////////////////////////////
// Constants and Variables
/////////////////////////////////////////////

int buttonCState[N_BUTTONS] = { HIGH };  // Stores the current button value
int buttonPState[N_BUTTONS] = { HIGH };  // Stores the previous button value

// Debounce
unsigned long lastDebounceTime[N_BUTTONS] = { 0 };  // Last time the button was toggled

// Velocity
byte velocity[N_BUTTONS] = { 127 };
byte toggleVelocity[N_BUTTONS] = { 127 };

/////////////////////////////////////////////
// Function Declarations
/////////////////////////////////////////////

void readButtonStates();
void handleButtons();

/////////////////////////////////////////////
// Function Definitions
/////////////////////////////////////////////

void buttons() {
  readButtonStates();
  handleButtons();
}

/////////////////////////////////////////////
// Read Button States
/////////////////////////////////////////////

void readButtonStates() {
  // Read pins from Arduino
  for (int i = 0; i < N_BUTTONS_ARDUINO; i++) {
    buttonCState[i] = digitalRead(BUTTON_ARDUINO_PIN[i]);
  }

#ifdef USING_MUX
  // If using MUX, read pins from every MUX
  int nButtonsPerMuxSum = N_BUTTONS_ARDUINO;  // Offset for buttonCState when using MUX

  for (int j = 0; j < N_MUX; j++) {
    for (int i = 0; i < N_BUTTONS_PER_MUX[j]; i++) {
      buttonCState[i + nButtonsPerMuxSum] = mux[j].readChannel(BUTTON_MUX_PIN[j][i]);

      // Scale values to 0 or 1
      if (buttonCState[i + nButtonsPerMuxSum] > buttonMuxThreshold) {
        buttonCState[i + nButtonsPerMuxSum] = HIGH;
      } else {
        buttonCState[i + nButtonsPerMuxSum] = LOW;
      }
    }
    nButtonsPerMuxSum += N_BUTTONS_PER_MUX[j];
  }
#endif
}

/////////////////////////////////////////////
// Handle Button Actions
/////////////////////////////////////////////

void handleButtons() {
  for (int i = 0; i < N_BUTTONS; i++) {
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (buttonPState[i] != buttonCState[i]) {
        lastDebounceTime[i] = millis();

        if (buttonCState[i] == LOW) {  // Button is pressed
          velocity[i] = 127;
        } else {
          velocity[i] = 0;  // Button is released
        }

        // Handle different button types
        if (i >= 0 && i < 8) {
          if (velocity[i] > 0) {
            // Handle control buttons (toggle)
            for (int j = 0; j < 8; j++) {
              leds[ledPin[j]] = colorArray[j][1];
              FastLED.show();
            }
            encoderSelect = i;
            leds[ledPin[i]] = CHSV(magentaHue, 255, LED_BRIGHTNESS);
            FastLED.show();

#ifdef DEBUG
            Serial.print("Button ");
            Serial.println(i);
            Serial.println("on");
            Serial.print("encoderSelect = ");
            Serial.println(encoderSelect);
#endif
          }
        }

        // Handle MIDI messages
        if (i > 8 && i < 12) {
          if (shiftButton == false) {
            // Case SHIFT is not pressed
            switch (MESSAGE_TYPE[i]) {
              case 0:  // NOTE NUMBER
                noteOn(BUTTON_MIDI_CH, MESSAGE_VAL[i - 1], velocity[i]);
                MidiUSB.flush();

#ifdef DEBUG
                Serial.print("Button: ");
                Serial.print(i);
                Serial.print("  | ch: ");
                Serial.print(BUTTON_MIDI_CH);
                Serial.print("  | nn: ");
                Serial.print(MESSAGE_VAL[i - 1]);
                Serial.print("  | velocity: ");
                Serial.println(velocity[i]);
#endif
                break;

              case 1:  // CONTROL CHANGE
                       // Handle control change message
#ifdef DEBUG
                Serial.print("Button: ");
                Serial.print(i);
                Serial.print("  | ch: ");
                Serial.print(BUTTON_MIDI_CH);
                Serial.print("  | cc: ");
                Serial.print(MESSAGE_VAL[i - 1]);
                Serial.print("  | value: ");
                Serial.println(velocity[i]);
#endif
                break;
            }
          } else {
            // Case SHIFT is pressed
            switch (i) {
              case 9:  // SOLO
                // UNSOLO all tracks
                for (int j = 0; j < 8; j++) {
                  if (soloState[j] == true) {
                    if (velocity[i] > 0) {  // only buttons is pressed
                      noteOn(BUTTON_MIDI_CH, SOLOS[j], velocity[i]);
                      noteOn(BUTTON_MIDI_CH, SOLOS[j], 0);
                      MidiUSB.flush();

                      Serial.print("SOLO: ");
                      Serial.println(j);
                    }
                  }
                }
                break;
              case 10:  // MUTE
                // Handle MUTE button
                for (int j = 0; j < 8; j++) {
                  if (muteState[j] == true) {
                    if (velocity[i] > 0) {  // only buttons is pressed
                      noteOn(BUTTON_MIDI_CH, MUTE[j], velocity[i]);
                      MidiUSB.flush();
                    }
                  }
                }
                break;
              case 11:  // ARM
                // Handle ARM button
                for (int j = 0; j < 8; j++) {
                  if (armState[j] == true) {
                    if (velocity[i] > 0) {  // only buttons is pressed
                      noteOn(BUTTON_MIDI_CH, REC_RDY[j], velocity[i]);
                      MidiUSB.flush();
                    }
                  }
                }
                break;
            }
          }
        }

        if (i > 12) {
          // Handle additional buttons
          switch (MESSAGE_TYPE[i]) {
            case 0:  // NOTE NUMBER
              noteOn(BUTTON_MIDI_CH, MESSAGE_VAL[i], velocity[i]);
              MidiUSB.flush();

              if (i == 15 || i == 16) {  // BANK CHANGE
                for (int j = 0; j < 8; j++) {
                  noteOn(BUTTON_MIDI_CH, 24 + j, selectedTrackVal[j]);
                  MidiUSB.flush();
                }
              }

#ifdef DEBUG
              Serial.print("Button: ");
              Serial.print(i);
              Serial.print("  | ch: ");
              Serial.print(BUTTON_MIDI_CH);
              Serial.print("  | nn: ");
              Serial.print(MESSAGE_VAL[i]);
              Serial.print("  | velocity: ");
              Serial.println(velocity[i]);
#endif
              break;

            case 1:  // CONTROL CHANGE
                     // Handle control change message
#ifdef DEBUG
              Serial.print("Button: ");
              Serial.print(i);
              Serial.print("  | ch: ");
              Serial.print(BUTTON_MIDI_CH);
              Serial.print("  | cc: ");
              Serial.print(MESSAGE_VAL[i]);
              Serial.print("  | value: ");
              Serial.println(velocity[i]);
#endif
              break;
          }
        }

        // Handle control buttons (momentary)
        if (((i >= 13 && i <= 20) || (i == 22)) && shiftButton == false) {
          if (velocity[i] > 0) {
            leds[ledPin[i - 1]] = colorArray[i - 1][0];
            FastLED.show();

#ifdef DEBUG
            Serial.print("Button: ");
            Serial.print(i);
            Serial.println(" - control on");
#endif
          } else {
            leds[ledPin[i - 1]] = colorArray[i - 1][1];
            FastLED.show();

#ifdef DEBUG
            Serial.print("Button: ");
            Serial.print(i);
            Serial.println(" - control off");
#endif
          }
        }


        // Handle encoder click
        if (i == 8) {
          if (velocity[i] > 0) {
            switch (encoderSelect) {
              case 0:
                noteOn(BUTTON_MIDI_CH, 32 + selectedTrack, 127);
                noteOff(BUTTON_MIDI_CH, 32 + selectedTrack, 127);
                MidiUSB.flush();
                break;
            }
          }
#ifdef DEBUG
          Serial.print("Encoder Click: ");
          Serial.println(velocity[i]);
#endif
        }

        // Handle shift button
        if (i == 12) {
          if (velocity[i] > 0) {
            shiftButton = true;
            leds[ledPin[i - 1]] = colorArray[i - 1][0];
            FastLED.show();
          } else {
            shiftButton = false;
            leds[ledPin[i - 1]] = colorArray[i - 1][1];
            FastLED.show();
          }

#ifdef DEBUG
          Serial.print("Shift Button: ");
          Serial.print(i);
          Serial.print(": ");
          Serial.println(shiftButton);
#endif
        }
        buttonPState[i] = buttonCState[i];
      }
    }
  }
}

#endif
