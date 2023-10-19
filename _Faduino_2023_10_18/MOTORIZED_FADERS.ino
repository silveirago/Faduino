#ifdef USING_MOTORIZED_FADERS

int faderVar;
int faderStartPos[N_M_FADERS] = {};
int faderMidiValue[N_M_FADERS] = {};
unsigned long previousMillis = 0;    // Store the last time the function was called
const unsigned long interval = 200;  // The interval in milliseconds
//long actualPos = 0;
//int prevMtrVal = 0;

boolean wasTouched[N_M_FADERS] = { true };

//int prevMtrVal, actualPos;


/////////////////////////////////////////////
// Functions

void calibrateFader(byte i) {

  int reading;

  //Send fader to the top and read max pos_ition
  digitalWrite(motorUpPin[i], HIGH);
  delay(500);
  digitalWrite(motorUpPin[i], LOW);

  reading = analogRead(POT_ARDUINO_PIN[i]);
  responsivePot[i].update(reading);
  potCState[i] = responsivePot[i].getValue();

  delay(500);

  faderMax = potCState[i];

  Serial.print("potCState Max: ");
  Serial.println(potCState[i]);

  //Send fader to the bottom and read max pos_ition
  digitalWrite(motorDownPin[i], HIGH);
  delay(500);
  digitalWrite(motorDownPin[i], LOW);

  reading = analogRead(POT_ARDUINO_PIN[i]);
  responsivePot[i].update(reading);
  potCState[i] = responsivePot[i].getValue();

  Serial.print("potCState Min: ");
  Serial.println(potCState[i]);

  delay(500);

  faderMin = potCState[i];

#ifdef DEBUG
  Serial.print("Fader: ");
  Serial.print(i);
  Serial.print(" | min: ");
  Serial.print(faderMin);
  Serial.print(" | max: ");
  Serial.println(faderMax);
  Serial.println();
#endif

  delay(1000);
}


void checkTouch(byte i, long in_) {
  boolean isTouchTemp = (in_ > capSensitivity) ? true : false;
  isTouched[i] = isTouchTemp;

  // Check for touch state change
  if (isTouched[i] != wasTouched[i]) {
    if (isTouched[i]) {
      // Finger is touched
      // Add your code to send "1" one time here

#ifdef ATMEGA32U4
      noteOn(BUTTON_MIDI_CH, FADER_TOUCH_1, 127);  // channel, note, velocity - sends fader touch
      MidiUSB.flush();
#endif

    } else {

#ifdef ATMEGA32U4
      noteOn(BUTTON_MIDI_CH, FADER_TOUCH_1, 0);  // channel, note, velocity
      MidiUSB.flush();
#endif
    }
    wasTouched[i] = isTouched[i];

#ifdef DEBUG
    Serial.print("isTouched ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(isTouched[i]);
#endif
  }
}


// changes the position of the motorized fader
void updateFader(byte i, int pos_) {

  int reading = analogRead(POT_ARDUINO_PIN[i]);
  responsivePot[i].update(reading);
  potCState[i] = responsivePot[i].getValue();

  // Calculate the error (difference between desired and current position)
  float error = pos_ - potCState[i];

  // Calculate motor speed based on the error
  float speed = map(abs(error), faderMin, faderMax, faderSpeedMin, faderSpeedMax);  // Map error to speed range
  // Serial.println(abs(error));

  // Ensure the motor speed doesn't drop below the minimum speed
  speed = max(speed, faderSpeedMin);

  // Check if the fader is touched
  if (isTouched[i]) {
    // Stop the motor and do not move it if touched
    digitalWrite(motorUpPin[i], LOW);
    digitalWrite(motorDownPin[i], LOW);
    analogWrite(faderSpeedPin[i], 0);
  } else {


    if (faderPos[i] != faderPPos[i]) {

      faderPPos[i] = faderPos[i];
    }

    // Determine the motor direction
    if (error > 0) {
      digitalWrite(motorUpPin[i], HIGH);
      digitalWrite(motorDownPin[i], LOW);

    } else if (error < 0) {
      digitalWrite(motorUpPin[i], LOW);
      digitalWrite(motorDownPin[i], HIGH);

    } else {
      digitalWrite(motorUpPin[i], LOW);
      digitalWrite(motorDownPin[i], LOW);
      speed = 0;  // Stop the motor if error is zero
    }

    // Set the motor speed
    analogWrite(faderSpeedPin[i], speed);

    // Check if the fader is at the desired position
    if (abs(error) <= motorStopPoint) {
      // Stop the motor
      analogWrite(faderSpeedPin[i], 0);
    }
  }
}




#endif  // USING_MOTORIZED_FADERS
