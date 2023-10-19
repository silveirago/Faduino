/////////////////////////////////////////////
// if using with ATmega32U4 (micro, pro micro, leonardo...)
#ifdef ATMEGA32U4

// - - - - - - - - - - - - - - - - - - - - -
// FUNCTIONS TO SEND MIDI OUT OF THE USB

// Arduino (pro)micro midi functions MIDIUSB Library
// Functions to SEND MIDI
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = { 0x09, static_cast<uint8_t>(0x90 | channel), pitch, velocity };
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = { 0x08, static_cast<uint8_t>(0x80 | channel), pitch, velocity };
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = { 0x0B, static_cast<uint8_t>(0xB0 | channel), control, value };
  MidiUSB.sendMIDI(event);
}

void pitchBend(byte channel, int value) {
  byte lowValue = static_cast<byte>(value & 0x7F);
  byte highValue = static_cast<byte>(value >> 7);
  midiEventPacket_t pitchBend = { 0x0E, static_cast<uint8_t>(0xE0 | channel), lowValue, highValue };
  MidiUSB.sendMIDI(pitchBend);
}

// void systemExclusive(byte* data, byte length) {
//   midiEventPacket_t message = { static_cast<uint8_t>(length > 3 ? 0x04 : length - 1), 0xF0, data[0], data[1] };
//   for (int i = 2; i < length; i++) {
//     message.byte2 = data[i];
//     MidiUSB.sendMIDI(message);
//   }
//   message.byte2 = 0xF7;
//   MidiUSB.sendMIDI(message);
// }

// - - - - - - - - - - - - - - - - - - - - -
// Functions to RECEIVE MIDI (MIDIUSB lib)
void MIDIread() {

  midiEventPacket_t rx = MidiUSB.read();

  switch (rx.header) {
    case 0:
      break;  //No pending events

    case 0x9:
      handleNoteOn(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //pitch
        rx.byte3         //velocity
      );
      break;

      // case 0x8:
      //   handleNoteOff(
      //     rx.byte1 & 0xF,  //channel
      //     rx.byte2,        //pitch
      //     rx.byte3         //velocity
      //   );
      //   break;

      // case 0xB:
      //   handleControlChange(
      //     rx.byte1 & 0xF,  //channel
      //     rx.byte2,        //cc
      //     rx.byte3         //value
      //   );
      //   break;

    case 0xE:
      handlePitchBend(
        rx.byte1 & 0xF,  //channel
        rx.byte2,        //LSB
        rx.byte3         //MSB
      );
      break;

      // case 0xC:
      //   handleProgramChange(
      //     rx.byte1 & 0xF,  //channel
      //     rx.byte2         //program number
      //   );
      //   break;

      // case 0xD:
      //   handleAftertouch(
      //     rx.byte1 & 0xF,  //channel
      //     rx.byte2         //pressure
      //   );
      //   break;

      // case 0xF:
      //   {
      //     // The first byte of a system exclusive message is always 0xF0
      //     if (rx.byte1 == 0xF0) {
      //       // We have a valid system exclusive message
      //       byte* data = rx.data;
      //       unsigned int length = rx.byte2;
      //       handleSysEx(data, length);
      //     }
      //   }
      //   break;
  }

  //  if (rx.header != 0) {
  //    Serial.print("Unhandled MIDI message: ");
  //    Serial.print(rx.byte1 & 0xF, DEC);
  //    Serial.print("-");
  //    Serial.print(rx.byte1, DEC);
  //    Serial.print("-");
  //    Serial.print(rx.byte2, DEC);
  //    Serial.print("-");
  //    Serial.println(rx.byte3, DEC);
  //  }
}

#endif

// - - - - - - - - - - - - - - - - - - - - -
// FUNCTIONS TO DO SOMETHING WITH THE MIDI INCOMING MESSAGES

void handleNoteOn(byte channel, byte number, byte value) {

  byte soloIndex = number - 8;
  byte muteIndex = number - 16;
  byte armIndex = number - 0;
  byte selectedTrackIndex = number - 24;




  if (value > 0) {  // NOTE ON

    if (number > 23 && number < 32) {  // TRACK SELECTION§

      selectedTrackVal[selectedTrackIndex] = value;

      // selects the appropriate track
      selectedTrack = selectedTrackIndex;



      faderPos[0] = map(pitchBendMidiIn[selectedTrack], 0, 127, faderMin, faderMax);
      ENCODER_CC_N[0] = V_POTS[selectedTrack];

      MESSAGE_VAL[8] = SOLOS[selectedTrack];
      MESSAGE_VAL[9] = MUTE[selectedTrack];
      MESSAGE_VAL[10] = REC_RDY[selectedTrack];

      // - - - - - - - - - - - - - - - - -
      // SOLO
      if (soloState[selectedTrack] == true) {  // SOLO
        leds[ledPin[8]] = colorArray[8][0];    // turns on the LED if SOLO is on
        FastLED.show();
      } else {
        leds[ledPin[8]] = colorArray[8][1];  // turns on the LED if SOLO is on
        FastLED.show();
      }

      // - - - - - - - - - - - - - - - - -
      // MUTE
      if (muteState[selectedTrack] == true) {  // MUTE
        leds[ledPin[9]] = colorArray[9][0];    // turns on the LED if SOLO is on
        FastLED.show();
      } else {
        leds[ledPin[9]] = colorArray[9][1];  // turns on the LED if SOLO is on
        FastLED.show();
      }

      // - - - - - - - - - - - - - - - - -
      // ARM
      if (armState[selectedTrack] == true) {   // ARM
        leds[ledPin[10]] = colorArray[10][0];  // turns on the LED if SOLO is on
        FastLED.show();
      } else {
        leds[ledPin[10]] = colorArray[10][1];  // turns on the LED if SOLO is on
        FastLED.show();
      }

      // - - - - - - - - - - - - - - - - -
      // DEBUG
#ifdef DEBUG
      // Serial.print("Track selected: ");
      // Serial.print(selectedTrackIndex);
      // Serial.print("  | Track SOLO state: ");
      // Serial.print(soloState[selectedTrack]);
      // Serial.print("  | Track MUTE: ");
      // Serial.print(muteState[selectedTrack]);
      // Serial.print("  | Track ARM: ");
      // Serial.println(armState[selectedTrack]);
#endif
    }  // track selection

    // - - - - - - - - - - - - - - - - -
    // SOLO
    if (number > 7 && number < 16) {

      soloState[soloIndex] = true;

      if (soloIndex == selectedTrack) {
        leds[ledPin[8]] = colorArray[8][0];  // turns on the LED if SOLO is on
        FastLED.show();
      }

#ifdef DEBUG
      Serial.print("Track SOLO ");
      Serial.print(soloIndex);
      Serial.print(": ");
      Serial.println(soloState[soloIndex]);
#endif
    }

    // - - - - - - - - - - - - - - - - -
    // MUTE
    if (number > 15 && number < 24) {

      muteState[muteIndex] = true;

      if (muteIndex == selectedTrack) {
        leds[ledPin[9]] = colorArray[9][0];  // turns on the LED if SOLO is on
        FastLED.show();
      }

#ifdef DEBUG
      Serial.print("Track MUTE ");
      Serial.print(muteIndex);
      Serial.print(": ");
      Serial.println(muteState[muteIndex]);
#endif
    }

    // - - - - - - - - - - - - - - - - -
    // ARM
    if (number >= 0 && number < 8) {

      armState[armIndex] = true;

      if (armIndex == selectedTrack) {
        leds[ledPin[10]] = colorArray[10][0];  // turns on the LED if SOLO is on
        FastLED.show();
      }

#ifdef DEBUG
      Serial.print("Track ARM ");
      Serial.print(armIndex);
      Serial.print(": ");
      Serial.println(armState[armIndex]);
#endif
    }

    // - - - - - - - - - - - - - - - - -
    // OTHER
    switch (number) {
      case LOOP_InOut:  // LOOP
        leds[ledPin[20]] = colorArray[20][0];
        FastLED.show();
        //Serial.println("LOOP on");
        break;

      case 93:  // STOP
        leds[ledPin[22]] = colorArray[22][1];
        leds[ledPin[23]] = colorArray[23][1];
        FastLED.show();
        //Serial.println("STOP on");
        break;

      case 94:  // PLAY
        leds[ledPin[22]] = colorArray[22][0];
        FastLED.show();
        //Serial.println("PLAY on");
        break;

      case 95:  // REC
        leds[ledPin[23]] = colorArray[23][0];
        FastLED.show();
        //Serial.println("REC on");
        break;

      case 70:  //SHIFT
        leds[ledPin[11]] = colorArray[11][0];
        FastLED.show();
        //Serial.println("SHIFT on");
        break;
    }
  } else {

    if (number > 23 && number < 32) {  // TRACK SELECTION§

      selectedTrackVal[selectedTrackIndex] = value;
    }
    // - - - - - - - - - - - - - - - - -
    // NOTE OFF

    // - - - - - - - - - - - - - - - - -
    // SOLO
    if (number > 7 && number < 16) {

      soloState[soloIndex] = false;

      if (soloIndex == selectedTrack) {
        leds[ledPin[8]] = colorArray[8][1];  // turns on the LED if SOLO is on
        FastLED.show();
      }

#ifdef DEBUG
      Serial.print("Track SOLO ");
      Serial.print(soloIndex);
      Serial.print(": ");
      Serial.println(soloState[soloIndex]);
#endif
    }

    // - - - - - - - - - - - - - - - - -
    // MUTE
    if (number > 15 && number < 24) {

      muteState[muteIndex] = false;

      if (muteIndex == selectedTrack) {
        leds[ledPin[9]] = colorArray[9][1];  // turns on the LED if SOLO is on
        FastLED.show();
      }

#ifdef DEBUG
      Serial.print("Track MUTE ");
      Serial.print(muteIndex);
      Serial.print(": ");
      Serial.println(muteState[muteIndex]);
#endif
    }

    // - - - - - - - - - - - - - - - - -
    // ARM
    if (number >= 0 && number < 8) {

      armState[armIndex] = false;

      if (armIndex == selectedTrack) {
        leds[ledPin[10]] = colorArray[10][1];  // turns on the LED if SOLO is on
        FastLED.show();
      }

#ifdef DEBUG
      Serial.print("Track ARM ");
      Serial.print(armIndex);
      Serial.print(": ");
      Serial.println(armState[armIndex]);
#endif
    }

    // - - - - - - - - - - - - - - - - -
    // OTHER
    switch (number) {
      case LOOP_InOut:  // LOOP
        leds[ledPin[20]] = colorArray[20][1];
        FastLED.show();
        //Serial.println("LOOP off");
        break;

        // case 93:  // STOP
        //   leds[ledPin[22]] = colorArray[22][1];
        //   FastLED.show();
        //   Serial.println("STOP off");
        //   break;

        // case 94:  // PLAY
        //   // leds[ledPin[22]] = colorArray[22][1];
        //   // FastLED.show();
        //   break;

      case 95:  // REC
        leds[ledPin[23]] = colorArray[23][1];
        FastLED.show();
        //Serial.println("REC off");
        break;

      case 70:  //SHIFT
        leds[ledPin[11]] = colorArray[11][1];
        FastLED.show();
        //Serial.println("SHIFT off");
        break;
    }
  }
// END OF OTHERS

// - - - - - - - - - - - - - - - - -
// DEBUG
#ifdef DEBUG

  Serial.print("MIDI In - ");

  Serial.print("NN - ");
  Serial.print(" Channel: ");
  Serial.print(channel);

  Serial.print("  | Number: ");
  Serial.print(number);

  Serial.print("  | Value: ");
  Serial.println(value);

  // Serial.print("selectedTrackVal ");
  // Serial.print(selectedTrackIndex);
  // Serial.print(": ");
  // Serial.println(value);

#endif  // DEBUG
}

// - - - - - - - - - - - - - - - - - - - - -

void handleNoteOff(byte channel, byte number, byte value) {
}

// - - - - - - - - - - - - - - - - - - - - -

void handleControlChange(byte channel, byte number, byte value) {
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

void handlePitchBend(byte channel, byte MSB, byte LSB) {

  int faderPBval = (LSB << 7) | MSB;

  pitchBendMidiIn[channel] = LSB;

  //recevingMidi = true;


  if (channel == selectedTrack) {  // update fader position
    // byte midiValue = LSB;
    // midiValue = clipValue(midiValue, 0, 127);

    faderPos[0] = map(faderPBval, 0, 16383, faderMin, faderMax);
    //actualPos = faderPos[0];

#ifdef DEBUG
    Serial.print("faderPos motor: ");
    Serial.println(faderPos[channel]);
#endif
  }

#ifdef DEBUG

  Serial.print("MIDI In - ");

  Serial.print("Pitch Bend |");
  Serial.print(" Channel: ");
  Serial.print(channel);

  Serial.print("  | MSB: ");
  Serial.print(MSB);

  Serial.print("  | LSB: ");
  Serial.print(LSB);
  Serial.print("  | faderPBval:");
  Serial.println(faderPBval);

#endif  // DEBUG
}

// void handleProgramChange(byte channel, byte program) {
//   // Do something with the program change message
// }

// void handleAftertouch(byte channel, byte pressure) {
//   // Do something with the aftertouch message
// }

void handleSysEx(byte* data, unsigned int length) {
  // Do something with the system exclusive message
}

////////////////////////////////////////////
