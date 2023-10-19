// Extracted from the following sources. Adapted by Gustavo Silveira
//
// https://sites.google.com/view/mackiecontroluniversaldiyguide/home
// CC List https://professionalcomposers.com/midi-cc-list/
// Note List https://computermusicresource.com/midikeys.html

// CC - Value CW = 1 or CCW = 65 | Channel = 1
// NOTES - value/On = 127 or value/Off = 0 | Channel = 1
// PITCH BEND - Value/Max = 8176 / Value/Min -8192  | Channel (fader number)


// FADER - PITCH BEND
const byte VOLUME_1 = 0;       //Volume fader 1 (In/Out)
const byte VOLUME_2 = 1;       //Volume fader 2 (In/Out)
const byte VOLUME_3 = 2;       //Volume fader 3 (In/Out)
const byte VOLUME_4 = 3;       //Volume fader 4 (In/Out)
const byte VOLUME_5 = 4;       //Volume fader 5 (In/Out)
const byte VOLUME_6 = 5;       //Volume fader 6 (In/Out)
const byte VOLUME_7 = 6;       //Volume fader 7 (In/Out)
const byte VOLUME_8 = 7;       //Volume fader 8 (In/Out)
const byte MASTER_VOLUME = 8;  //Master volume (In/Out)

// ENCODER - CC
const byte V_POT_1 = 0x10;              //V-Pot 1 (Relative) (Out)
const byte V_POT_2 = 0x11;              //V-Pot 2 (Relative) (Out)
const byte V_POT_3 = 0x12;              //V-Pot 3 (Relative) (Out)
const byte V_POT_4 = 0x13;              //V-Pot 4 (Relative) (Out)
const byte V_POT_5 = 0x14;              //V-Pot 5 (Relative) (Out)
const byte V_POT_6 = 0x15;              //V-Pot 6 (Relative) (Out)
const byte V_POT_7 = 0x16;              //V-Pot 7 (Relative) (Out)
const byte V_POT_8 = 0x17;              //V-Pot 8 (Relative) (Out)
const byte EXTERNAL_CONTROLLER = 0x2E;  //External controller (Out)
const byte JOG_WHEEL = 0x3C;            //Jog wheel (Relative) (Out)

// BUTTONS - NN
const byte REC_RDY_1 = 0x00;            //Record/Ready 1 (In/Out)
const byte REC_RDY_2 = 0x01;            //Record/Ready 2 (In/Out)
const byte REC_RDY_3 = 0x02;            //Record/Ready 3 (In/Out)
const byte REC_RDY_4 = 0x03;            //Record/Ready 4 (In/Out)
const byte REC_RDY_5 = 0x04;            //Record/Ready 5 (In/Out)
const byte REC_RDY_6 = 0x05;            //Record/Ready 6 (In/Out)
const byte REC_RDY_7 = 0x06;            //Record/Ready 7 (In/Out)
const byte REC_RDY_8 = 0x07;            //Record/Ready 8 (In/Out)
const byte SOLO_1 = 0x08;               //Solo 1 (In/Out)
const byte SOLO_2 = 0x09;               //Solo 2 (In/Out)
const byte SOLO_3 = 0x0A;               //Solo 3 (In/Out)
const byte SOLO_4 = 0x0B;               //Solo 4 (In/Out)
const byte SOLO_5 = 0x0C;               //Solo 5 (In/Out)
const byte SOLO_6 = 0x0D;               //Solo 6 (In/Out)
const byte SOLO_7 = 0x0E;               //Solo 7 (In/Out)
const byte SOLO_8 = 0x0F;               //Solo 8 (In/Out)
const byte MUTE_1 = 0x10;               //Mute 1 (In/Out)
const byte MUTE_2 = 0x11;               //Mute 2 (In/Out)
const byte MUTE_3 = 0x12;               //Mute 3 (In/Out)
const byte MUTE_4 = 0x13;               //Mute 4 (In/Out)
const byte MUTE_5 = 0x14;               //Mute 5 (In/Out)
const byte MUTE_6 = 0x15;               //Mute 6 (In/Out)
const byte MUTE_7 = 0x16;               //Mute 7 (In/Out)
const byte MUTE_8 = 0x17;               //Mute 8 (In/Out)
const byte SELECT_1 = 0x18;             //Select 1 (In/Out)
const byte SELECT_2 = 0x19;             //Select 2 (In/Out)
const byte SELECT_3 = 0x1A;             //Select 3 (In/Out)
const byte SELECT_4 = 0x1B;             //Select 4 (In/Out)
const byte SELECT_5 = 0x1C;             //Select 5 (In/Out)
const byte SELECT_6 = 0x1D;             //Select 6 (In/Out)
const byte SELECT_7 = 0x1E;             //Select 7 (In/Out)
const byte SELECT_8 = 0x1F;             //Select 8 (In/Out)
const byte V_POT_SELECT_1 = 0x20;       //V-Pot select 1 (In/Out)
const byte V_POT_SELECT_2 = 0x21;       //V-Pot select 2 (In/Out)
const byte V_POT_SELECT_3 = 0x22;       //V-Pot select 3 (In/Out)
const byte V_POT_SELECT_4 = 0x23;       //V-Pot select 4 (In/Out)
const byte V_POT_SELECT_5 = 0x24;       //V-Pot select 5 (In/Out)
const byte V_POT_SELECT_6 = 0x25;       //V-Pot select 6 (In/Out)
const byte V_POT_SELECT_7 = 0x26;       //V-Pot select 7 (In/Out)
const byte V_POT_SELECT_8 = 0x27;       //V-Pot select 8 (In/Out)
const byte ASSIGN_TRACK = 0x28;         //Assign Track (In/Out)
const byte ASSIGN_SEND = 0x29;          //Assign Send (In/Out)
const byte ASSIGN_PAN = 0x2A;           //Assign Pan (In/Out)
const byte ASSIGN_PLUGIN = 0x2B;        //Assign Pluggin (In/Out)
const byte ASSIGN_EQ = 0x2C;            //Assign Equalizer (In/Out)
const byte ASSIGN_INSTR = 0x2D;         //Assign Instrument (In/Out)
const byte BANK_LEFT = 0x2E;            //Banks: Bank Left (Out)
const byte BANK_RIGHT = 0x2F;           //Banks: Bank Right (Out)
const byte CHANNEL_LEFT = 0x30;         //Banks: Channel Left (Out)
const byte CHANNEL_RIGHT = 0x31;        //Banks: Channel Right (Out)
const byte FLIP = 0x32;                 //Flip (In/Out)
const byte GLOBAL_VIEW = 0x33;          //Global View (In/Out)
const byte NAME_VALUE = 0x34;           //Name/Value (Out)
const byte SMPTE_BEATS = 0x35;          //SMPTE/Beats (Out)
const byte F1 = 0x36;                   //Function key 1 (Out)
const byte F2 = 0x37;                   //Function key 2 (Out)
const byte F3 = 0x38;                   //Function key 3 (Out)
const byte F4 = 0x39;                   //Function key 4 (Out)
const byte F5 = 0x3A;                   //Function key 5 (Out)
const byte F6 = 0x3B;                   //Function key 6 (Out)
const byte F7 = 0x3C;                   //Function key 7 (Out)
const byte F8 = 0x3D;                   //Function key 8 (Out)
const byte VIEW_MIDI = 0x3E;            //View MIDI tracks (Out)
const byte VIEW_INPUTS = 0x3F;          //View inputs (Out)
const byte VIEW_AUDIO = 0x40;           //View audio tracks (Out)
const byte VIEW_INSTR = 0x41;           //View audio instrument (Out)
const byte VIEW_AUX = 0x42;             //View auxiliary (Out)
const byte VIEW_BUSSES = 0x43;          //View busses (Out)
const byte VIEW_OUTPUTS = 0x44;         //View outputs (Out)
const byte VIEW_USER = 0x45;            //View user (Out)
const byte SHIFT = 0x46;                //Shift (Out)
const byte OPTION = 0x47;               //Option (Out)
const byte CONTROL = 0x48;              //Control (Out)
const byte CMD_ALT = 0x49;              //Command/Alt (Out)
const byte AUTOMATION_READ_OFF = 0x4A;  //Automation read/off (In/Out)
const byte AUTOMATION_WRITE = 0x4B;     //Automation write (In/Out)
const byte AUTOMATION_TRIM = 0x4C;      //Automation trim (In/Out)
const byte AUTOMATION_TOUCH = 0x4D;     //Automation touch (In/Out)
const byte AUTOMATION_LATCH = 0x4E;     //Automation latch (In/Out)
const byte GROUP = 0x4F;                //Group (In/Out)
const byte SAVE = 0x50;                 //Save (In/Out)
const byte UNDO = 0x51;                 //Undo (In/Out)
const byte CANCEL = 0x52;               //Cancel (Out)
const byte ENTER = 0x53;                //Enter (Out)
const byte MARKER = 0x54;               //Marker (In/Out)
const byte NUDGE = 0x55;                //Nudge (In/Out)
const byte CYCLE = 0x56;                //Cycle (In/Out)
const byte DROP = 0x57;                 //Drop (In/Out)
const byte REPLACE = 0x58;              //Replace (In/Out)
const byte CLICK = 0x59;                //Click (In/Out)
const byte SOLO = 0x5A;                 //Solo (In/Out)
const byte REWIND = 0x5B;               //Rewind (In/Out)
const byte FAST_FWD = 0x5C;             //Fast forward (In/Out)
const byte STOP = 0x5D;                 //Stop (In/Out)
const byte PLAY = 0x5E;                 //Play (In/Out)
const byte RECORD = 0x5F;               //Record (In/Out)
const byte UP = 0x60;                   //Cursor up (Out)
const byte DOWN = 0x61;                 //Cursor down (Out)
const byte LEFT = 0x62;                 //Cursor left (Out)
const byte RIGHT = 0x63;                //Cursor right (Out)
const byte ZOOM = 0x64;                 //Zoom (In/Out)
const byte SCRUB = 0x65;                //Scrub (In/Out)
const byte USER_SWITCH_A = 0x66;        //User switch A (Out)
const byte USER_SWITCH_B = 0x67;        //User switch B (Out)
const byte FADER_TOUCH_1 = 0x68;        //Fader touch 1 (Out)
const byte FADER_TOUCH_2 = 0x69;        //Fader touch 2 (Out)
const byte FADER_TOUCH_3 = 0x6A;        //Fader touch 3 (Out)
const byte FADER_TOUCH_4 = 0x6B;        //Fader touch 4 (Out)
const byte FADER_TOUCH_5 = 0x6C;        //Fader touch 5 (Out)
const byte FADER_TOUCH_6 = 0x6D;        //Fader touch 6 (Out)
const byte FADER_TOUCH_7 = 0x6E;        //Fader touch 7 (Out)
const byte FADER_TOUCH_8 = 0x6F;        //Fader touch 8 (Out)
const byte FADER_TOUCH_MASTER = 0x70;   //Fader touch master (Out)
const byte SMPTE = 0x71;                //SMPTE LED (In)
const byte BEATS = 0x72;                //Beats LED (In)
const byte RUDE_SOLO = 0x73;            //Rude solo light (In)
const byte RELAY = 0x76;                //Relay (In)
const byte LOOP_InOut = 0x56;           //Loop (In/Out)



// ARRAYS


// For the Volumes:
const byte VOLUMES[8] = {
  VOLUME_1, VOLUME_2, VOLUME_3, VOLUME_4,
  VOLUME_5, VOLUME_6, VOLUME_7, VOLUME_8
};

//For the Encoder CC Messages:
const byte V_POTS[8] = {
  V_POT_1, V_POT_2, V_POT_3, V_POT_4,
  V_POT_5, V_POT_6, V_POT_7, V_POT_8
};

//For the Button NN Messages:
const byte REC_RDY[8] = {
  REC_RDY_1, REC_RDY_2, REC_RDY_3, REC_RDY_4,
  REC_RDY_5, REC_RDY_6, REC_RDY_7, REC_RDY_8
};

const byte SOLOS[8] = {
  SOLO_1, SOLO_2, SOLO_3, SOLO_4,
  SOLO_5, SOLO_6, SOLO_7, SOLO_8
};

const byte MUTE[8] = {
  MUTE_1, MUTE_2, MUTE_3, MUTE_4,
  MUTE_5, MUTE_6, MUTE_7, MUTE_8
};

const byte SELECT[8] = {
  SELECT_1, SELECT_2, SELECT_3, SELECT_4,
  SELECT_5, SELECT_6, SELECT_7, SELECT_8
};

const byte V_POT_SELECT[8] = {
  V_POT_SELECT_1, V_POT_SELECT_2, V_POT_SELECT_3, V_POT_SELECT_4,
  V_POT_SELECT_5, V_POT_SELECT_6, V_POT_SELECT_7, V_POT_SELECT_8
};

const byte F_KEYS[8] = {
  F1, F2, F3, F4,
  F5, F6, F7, F8
};

const byte VIEW_MODES[8] = {
  VIEW_MIDI, VIEW_INPUTS, VIEW_AUDIO, VIEW_INSTR,
  VIEW_AUX, VIEW_BUSSES, VIEW_OUTPUTS, VIEW_USER
};


// Please note that these arrays assume that you have assigned the messages in the same order they were specified in your original list.
// You can use these arrays to easily access and iterate through the respective messages as needed.