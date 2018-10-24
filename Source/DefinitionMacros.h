/*
  ==============================================================================

    Definitions.cpp
    Created: 22 Oct 2018 10:19:54pm
    Author:  Wojtek Pilwinski

  ==============================================================================
*/

// COLOURS AND LABELS
#define PAJ_YELLOW Colour(0xff, 0xe7, 0x00)
#define PAJ_RED    Colour(0xff, 0x65, 0x23)

#define MAGNITUDE   "MAGNITUDE"
#define PHASE_SHIFT "PHASE SHIFT"



// BUTTONS LAYOUT
#define MARG_X   49
#define LAB_X    10
#define BUF_LAB_X 82
#define BUF_BUT_X 95
#define SPACE_X  38.5



// BUTTONS AND FFT SIZE IDs
#define B_1024ID        0
#define B_2048ID        1
#define B_4096ID        2
#define B_8192ID        3
#define B_16384ID       4
#define B_32768ID       5
#define B_65536ID       6

#define MUTE_IMPULSE_ID 7
#define NUM_OF_RADIO_BUTTONS 7

#define PAJ_OFF_BUTTON_ID   20
#define PAJ_RESET_BUTTON_ID 21
#define PAJ_PHASE_BUTTON_ID 22

#define BUFF_BUTTON_RADIO_GROUP 100

#define UNWRAP_PHASE_ID 10
#define LATENCY_ID      11



// TIMERS IDs
#define SETTINGS_TIMER_ID 0
#define BYPASS_TIMER_ID   1
#define WAIT_FOR_PREP_TO_PLAY_ID 2
#define HINT_TIMER_ID 3
#define MSG_RECEIVED_TIMER_ID 50



// REMOTE BOOLEANs
#define W_CLICK       true
#define W_DONT_CLICK  false
#define W_BUTTON_ON   true
#define W_BUTTON_OFF  false
#define SETTINGS_READY true



// STATUS IDs
#define PAJ_PLAY       19



// CHANNELS AND GRAPH TYPE
#define W_MAGN 0
#define W_PHAS 1

#define W_LEFT  0
#define W_RIGHT 1



// DISPLAY LAYOUT
#define MARG_X_LEFT  50.0f
#define MARG_X_RIGHT 10.0f
#define MARG_Y_BOT   20.0f
#define MARG_Y_TOP   23.0f



// FFT SETTINGS BOOLEAN
#define SETTINGS_READY true
