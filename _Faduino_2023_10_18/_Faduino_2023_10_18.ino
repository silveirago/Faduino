/*
  Created by Gustavo Silveira, 2023.

  Website: http://www.musiconerd.com
  YouTube: http://www.youtube.com/musiconerd
  Facebook: http://facebook.com/musiconerdmusiconerd
  Instagram: http://instagram.com/musiconerd/
  Personal Website: http://www.gustavosilveira.net
  Email: gustavosilveira@musiconerd.com

  If you are using this for anything other than personal use, please remember to give credit.

  PS: Modify the values indicated by comments like " //* "

*/

/////////////////////////////////////////////
// Choose Your Board
// Define your board by choosing one of the options below:
// "ATMEGA328" for ATmega328 (e.g., Uno, Mega, Nano...)
// "ATMEGA32U4" for ATmega32U4 (e.g., Micro, Pro Micro, Leonardo...)
// "TEENSY" for Teensy board
// "BLEMIDI" for BLE MIDI (ESP32)
// "DEBUG" for debugging with the serial monitor

#define ATMEGA32U4 1  //* Put the microcontroller you are using, like in the lines above, followed by "1," e.g., "ATMEGA328 1," "DEBUG 1," etc.
//#define DEBUG 1

/////////////////////////////////////////////
// Using Buttons
#define USING_BUTTONS 1  //* Uncomment if using buttons, comment if not

/////////////////////////////////////////////
// Using Potentiometers
#define USING_POTENTIOMETERS 1  //* Uncomment if using potentiometers, comment if not

// Using High-Resolution Faders
//#define USING_HIGH_RES_FADERS 1  //* Uncomment if using high-res faders (any fader can be high-res), comment if not

// Using Motorized Faders
#define USING_MOTORIZED_FADERS 1  //* Uncomment if using motorized faders, comment if not

/////////////////////////////////////////////
// Using a Multiplexer
#define USING_MUX 1  //* Uncomment if using a multiplexer, comment if not

/////////////////////////////////////////////
// Using Encoders
#define USING_ENCODER 1  //* Uncomment if using encoders, comment if not

// Using High-Resolution Encoders
//#define USING_HIGH_RES_ENC 1  //* Uncomment if using high-res encoders, comment if not

/////////////////////////////////////////////
// Using Neopixels (Addressable Strips)
#define USING_NEOPIXEL 1  //* Uncomment if using Neopixels, comment if not

// Using the Mackie Protocol
#define USING_MACKIE 1

/////////////////////////////////////////////
// LIBRARIES
// -- Define the MIDI library -- //

//////////////////////////////////////
// If using FastLED
#ifdef USING_NEOPIXEL

#include "FastLED.h"  // by Daniel Garcia - http://fastled.io

FASTLED_USING_NAMESPACE

#define DATA_PIN 6
//#define CLK_PIN   4
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS 24

CRGB leds[NUM_LEDS];

#define BRIGHTNESS 255  // 0-255
#define FRAMES_PER_SECOND 120

#endif
//////////////////////////////////////

// If using with ATmega32U4 - Micro, Pro Micro, Leonardo...
#ifdef ATMEGA32U4
#include <MIDIUSB.h>

#include "usb_rename.h"

USBRename dummy = USBRename("Faduino", "Nerd Musician", "0001");

#endif  // ATMEGA32U4

//////////////////////
// Add this lib if using a cd4067 multiplexer
#ifdef USING_MUX
#include <Multiplexer4067.h>  // Multiplexer CD4067 library >> https://github.com/sumotoy/Multiplexer4067
#endif

//////////////////////
// Encoder
#ifdef USING_ENCODER
// Download the Encoder lib from Paul Stoffregen in the Downloads Manager (it comes with Teensy)
#include <Encoder.h>  // simplifies reading the encoder
#endif

///////////////////////////////////////////
// MULTIPLEXERS
#ifdef USING_MUX

#define N_MUX 2  //* number of multiplexers
//* Define the pins s0, s1, s2, s3, and x
#define s0 4
#define s1 5
#define s2 15
#define s3 14

#define x1 A1  // analog pin for the first mux
#define x2 A2  // analog pin for the second mux
//#define x3 A2 // analog pin for the third mux

// Add more #define and x numbers if necessary

// *** IMPORTANT: If you want to add more than one mux! ***
// In the Configuration tab, line 123, add another "pinMode(x2, INPUT_PULLUP);" if you want to add a second mux,
// and "pinMode(x3, INPUT_PULLUP);" for a third mux, and so on...

// Initialize the multiplexer
Multiplexer4067 mux[N_MUX] = {
  Multiplexer4067(s0, s1, s2, s3, x1),  // The SIG pin where the multiplexer is connected
  Multiplexer4067(s0, s1, s2, s3, x2),  // The SIG pin where the multiplexer is connected
  //  Multiplexer4067(s0, s1, s2, s3, x3) // The SIG pin where the multiplexer is connected
  // ...
};
#endif

#ifdef USING_POTENTIOMETERS
// Include the ResponsiveAnalogRead library
#include <ResponsiveAnalogRead.h>  // https://github.com/dxinteractive/ResponsiveAnalogRead
#endif

#ifdef USING_MOTORIZED_FADERS
#include <CapacitiveSensor.h>  // Adds touch capabilities for the motorized fader
#endif

#ifdef USING_MACKIE
#include "MACKIE.h"
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Types of MIDI messages to send - DO NOT TOUCH
byte NN = 0;  // Note number or MACKIE
byte CC = 1;  // Control change
byte T = 2;   // Toggle
byte PC = 3;  // Program Change
byte PB = 4;  // Pitch Bend
byte PA = 5;  // Pitch Bend

/////////////////////////////////////////////
// BUTTONS
#ifdef USING_BUTTONS

const byte N_BUTTONS = 25;                      //* total number of buttons. Number of buttons on the Arduino + number of buttons on multiplexer 1 + number of buttons on multiplexer 2... (DO NOT include octave and MIDI channel buttons here)
const byte N_BUTTONS_ARDUINO = 0;               //* number of buttons connected directly to the Arduino
const byte BUTTON_ARDUINO_PIN[N_BUTTONS] = {};  //* pins for each button connected directly to the Arduino

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#ifdef USING_MUX                                   // Fill in if using a multiplexer, otherwise leave it empty
const byte N_BUTTONS_PER_MUX[N_MUX] = { 13, 12 };  //* number of buttons on each mux (in order)
const byte BUTTON_MUX_PIN[N_MUX][16] = {
  //* pins for each button on each mux in the desired order

  { 4, 5, 6, 7, 0, 1, 2, 3, 8, 9, 10, 11, 12 },  // 1 | 8 is the encoder button pin
  { 4, 5, 6, 7, 3, 2, 1, 12, 13, 14, 15, 11 },   // 2

  // ...
};

int buttonMuxThreshold = 500;

#endif  //USING_MUX

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// What type of message do you want to send?
// Note Number - Control Change - Toggle - Program Change

// NN: Note number or MACKIE
// CC: Control change
// T: Toggle
// PC: Program Change
// PA: Polyphonic Aftertouch

//* Specify the type of message you want to send, in the same order you declared the button pins
// "NN" for note number | "CC" for control change | "T" for note number but in toggle mode | "PC" for program change
byte MESSAGE_TYPE[N_BUTTONS] = {
  NN, NN, NN, NN,
  NN, NN, NN, NN,

  NN,

  NN, NN, NN, NN,
  NN, NN, NN, NN,
  NN, NN, NN, NN,
  NN, NN, NN, NN
};

// Specify the message number you want to send, in the correct order, whether it's a note number or not
byte MESSAGE_VAL[N_BUTTONS] = {
  127,
  ASSIGN_PAN,
  127,
  SCRUB,

  127,
  CLICK,
  127,
  MARKER,

  127,

  SOLOS[0],
  MUTE[0],
  REC_RDY[0],
  SHIFT,

  LEFT,
  RIGHT,
  BANK_LEFT,
  BANK_RIGHT,

  75,
  AUTOMATION_TOUCH,
  AUTOMATION_WRITE,
  AUTOMATION_READ_OFF,

  LOOP_InOut,
  STOP,
  PLAY,
  RECORD,
};

byte selectedTrackVal[8] = { 0 };  // stores which tracks are selected
boolean soloState[8] = { false };
boolean muteState[8] = { false };
boolean armState[8] = { false };
int currentBank = 0;

byte encoderSelect = 0;
boolean shiftButton = true;

// | pan    | scroll  | Channel | link
// | Master | Click | Section | Marker

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Debounce
unsigned long debounceDelay = 50;  //* the debounce time; increase if the output flickers

unsigned long buttonsPreviousMillis = 0;
const unsigned long buttonsInterval = 40;  // Time in milliseconds

#endif  // USING_BUTTONS

/////////////////////////////////////////////
// POTENTIOMETERS

#ifdef USING_POTENTIOMETERS

const byte N_POTS = 1;  //* total number of pots (slide & rotary). Number of pots on the Arduino + number of pots on multiplexer 1 + number of pots on multiplexer 2...

const byte N_POTS_ARDUINO = 1;  //* number of pots connected directly to the Arduino
// If using the Arduino, specify as "A1, A2"
// If using ESP32, only specify the GPIO number as "11, 10"
const byte POT_ARDUINO_PIN[N_POTS_ARDUINO] = { A0 };  //* pins for each pot connected directly to the Arduino (don't use "A" if you are using ESP32, only the number)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#ifdef USING_MUX
const byte N_POTS_PER_MUX[N_MUX] = { 0, 0 };  //* number of pots on each mux (in order)
const byte POT_MUX_PIN[N_MUX][16] = {
  //* pins for each pot on each mux in the desired order
  {},  //* pins of the first mux
  {},
  // ...
};
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define USING_CUSTOM_CC_N 1  //* comment if not using CUSTOM CC NUMBERS, uncomment if using it.
#ifdef USING_CUSTOM_CC_N

// What type of message do you want to send?
// Control Change - Pitch Bend

// CC: Control change
// PB: Pitch Bend

//* Specify the message type for each pot, in the same order you declared the pot pins
// "CC" for Control Change | "PB" for Pitch Bend
byte MESSAGE_TYPE_POT[N_POTS] = { PB };

byte POT_CC_N[N_POTS] = { VOLUME_1 };  // Add the CC NUMBER or MACKIE of each pot you want

#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

const int TIMEOUT = 300;      //* Amount of time the potentiometer will be read after it exceeds the varThreshold
const byte varThreshold = 8;  //* Threshold for the potentiometer signal variation - Increase if using ESP32
// For varThreshold, I usually use "8" for normal Arduino and "30" for ESP32

// Specify the minimum and maximum readings in the potCState
// Put a slightly higher value in potMin and a slightly lower value in potMax
// IMPORTANT:
// Regular Arduinos have 10-bit resolution: 0 - 1023
// ESP32 boards have 12-bit resolution: 0 - 4095
const int potMin = 10;
const unsigned int potMax = 1012;

#endif  // USING_POTENTIOMETERS

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/////////////////////////////////////////////
// ENCODERS

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// CALIBRATION
byte encoderMinVal = 0;  //* encoder minimum value

#ifdef USING_HIGH_RES_ENC
const unsigned int encoderMaxVal = 16383;  //* encoder max value HIGH RES 14-bit
#else
const byte encoderMaxVal = 127;  //* encoder max value NORMAL MIDI 7-bit
#endif

//#endif

// Encoder Sensitivity
// Choose a (float) number greater than 0 (e.g., 0.2) and 4.
// "1" will give you 4 readings per click, with increments of 4, like 4, 8, 12...
// "4" will give you 1 reading per click, like 1, 2, 3, 4...
// so "4" will provide the most precise reading
float encSensitivity = 4;  //* adjust the encoder sensitivity here

const byte N_ENCODER_MIDI_CHANNELS = 16;  // number of ENCODER_MIDI_CHs (DO NOT CHANGE)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// PINS

#ifdef USING_ENCODER

const byte N_ENCODERS = 1;                   //* number of encoders
const byte N_ENCODER_PINS = N_ENCODERS * 2;  // number of pins used by the encoders

// Encoder encoder[N_ENCODERS] = { { 10, 16 } };  // the two pins of each encoder -  Use pins with Interrupts!
Encoder encoder[N_ENCODERS] = { { 3, 2 } };  // the two pins of each encoder -  Use pins with Interrupts!

// Choose the CC or MACKIE value
byte ENCODER_CC_N[N_ENCODERS] = { V_POTS[0] };  // Add the CC NUMBER of each encoder you want

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

byte preset[N_ENCODER_MIDI_CHANNELS][N_ENCODERS] = {
  //* stores presets to start your encoders
  //  {64, 64}, // ch 1
  //  {64, 64}, // ch 2
  //  {64, 64}, // ch 3
  //  {64, 64}, // ch 4
  //  {64, 64}, // ch 5
  //  {64, 64}, // ch 6
  //  {64, 64}, // ch 7
  //  {64, 64}, // ch 8
  //  {64, 64}, // ch 9
  //  {64, 64}, // ch 10
  //  {64, 64}, // ch 11
  //  {64, 64}, // ch 12
  //  {64, 64}, // ch 13
  //  {64, 64}, // ch 14
  //  {64, 64}, // ch 15
  //  {64, 64}  // ch 16
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#ifdef USING_MACKIE
byte encoderSens = 3;  // 1-63
#endif

#endif  // USING_ENCODER

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/////////////////////////////////////////////
// MIDI STUFF
byte POT_MIDI_CH = 0;  //* MIDI channel to be used
byte BUTTON_MIDI_CH = 0;
byte ENCODER_MIDI_CH = 0;

byte selectedTrack = 0;  // stores which track is selected in the DAW
byte pitchBendMidiIn[8] = { 0 };

/////////////////////////////////////////////
// MOTORIZED FADERS
#ifdef USING_MOTORIZED_FADERS

// Arduino Pin Assignments
const byte N_M_FADERS = 1;
const byte motorDownPin[N_M_FADERS] = { 7 };   // H-Bridge control to make the motor descend
const byte motorUpPin[N_M_FADERS] = { 8 };     // H-Bridge control to make the motor ascend
const byte faderSpeedPin[N_M_FADERS] = { 9 };  // motor speed pin (PWM)

byte faderSpeed[N_M_FADERS] = { 255 };  // 0-255
byte faderSpeedMin = 155;               // 0-255 - 140?
byte faderSpeedMax = 255;               // 0-255 -  250?

const float motorStopPoint = 16;  // the motor will stop X values before reaching its target. Increase to avoid jitter (will be less precise).

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// variables you don't need to change
int faderPos[N_M_FADERS] = { 0 };   // position of the fader
int faderPPos[N_M_FADERS] = { 0 };  // previous position of the fader
int faderMax;                       // Value read by fader's maximum position (0-1023)
int faderMin;                       // Value read by fader's minimum position (0-1023)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Midi
byte pFaderInVal[16][N_M_FADERS] = { 0 };
byte pFaderPBInVal[N_M_FADERS] = { 0 };  // Pitch bend for Mackie

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Cap Sense
boolean isTouched[N_M_FADERS] = { true };  // Is the fader currently being touched?

long touchLine[N_M_FADERS] = { 0 };

unsigned long capTimeNow[N_M_FADERS] = { 0 };

// Capacitive Sensor - Touch Pin
// 10M resistor between pins 16 & 10, pin 2 is sensor pin, add a wire and/or foil if desired
CapacitiveSensor capSense[N_M_FADERS] = {
  CapacitiveSensor(16, 10)
};  // capSense = CapacitiveSensor(7, 8)

const int touchSendPin[N_M_FADERS] = { 16 };     // Send pin for Capacitance Sensing Circuit (Digital 16)
const int touchReceivePin[N_M_FADERS] = { 10 };  // Receive pin for Capacitance Sensing Circuit (Digital 10)

byte capSenseSpeed = 15;   // number of samples
int capSensitivity = 150;  // touch threshold

unsigned long capTimeout = 1500;

#endif  // USING_MOTORIZED_FADERS
