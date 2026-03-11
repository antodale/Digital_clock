/*        ARDUINO PONG CLOCK 
 *        Author: Henry Gilbert, verion updated by Antonio D'Alessandro
 *        Date Created: July 20th, modified on April 24th
 *        Essential Engineering 
 */

#include <FastLED.h>
#include "Plasma.cpp"
// #include <arduinoFFT.h>
// #include "interrupt_manager.h"
#include "Effect.h"
#include <DS3232RTC.h>
#include "TimePrint.h"
#define LED_PIN 4  // LED Pin for controlling LED address
// #define NUM_LEDS 120  // Defining the number of addressable LEDs used in the circuit
#define CLOCK_MODE 6  // Pin definition for the clock mode digital input.
#define SET_TIME 7    // Pin definition for the set time mode digital input.
#define PATTERN A0    // Pin definition for the potentiometer/pattern set analog input.
#define SWITCH_T 2    // Pin for the switch interrupt
#define SWITCH_B 3    // Pin for the switch interrupt
#define WIDTH 17
#define HEIGHT 7
#define B_BUTTON 10
#define PHOTO A1
#define SAMPLES 64
#define SAMPLING_FREQUENCY 4000 // Hz
// ************************************************  GLOBAL VARIABLES AND STRUCTURES  ************************************************
// CRGB leds_rainbow[120];
CHSV colour(0, 180, 100);  // Oggetto colore per l'effetto arcobaleno
int clock_mode_reading;    // Switch input reading for clock mode (display time vs show pattern)
int set_time_reading;      // Switch input reading for set time mode. Changes how fast time increases.
int pattern_setting;       // Analog potentiometer reading for pattern mode. Changes which pattern is displayed.
extern CRGB leds[120];     // Array creation of leds - allows the LED to be address using array [] notation.
int background = 0;
int buttnt;
int buttnb;
extern DS3232RTC myRTC;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000;
const int time_array[4] = { 0, 0, 0, 8 };

extern tmElements_t tm;
Time tempo;

// LED assignment of the clock perimeter
int perimeter[34] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                    103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119 };


// FFT fucntions
// arduinoFFT FFT = arduinoFFT();

// double vReal[SAMPLES];
// double vImag[SAMPLES];


typedef enum {  // Vari sfondi possibili
  only_background,
  only_time,
  nothing,
} display_state;
display_state show_display = nothing;  // Inizializziamo l'oggetto sfondo

// ************************************************ END GLOBALS ********************************************************

// ************************************************ BACKGROUND PATTERNS PLASMA************************************************

void doPlasma() {
  Plasma plasma(leds, WIDTH, HEIGHT);
  plasma.start();
}

// ************************************************ BACKGROUND PATTERNS ************************************************

void constant_background_color(int red, int green, int blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(red, green, blue);
  }
}



// void music_sync() {
  
// }



// ******************************************** END BACKGROUND PATTERNS ************************************************


// ************************************************ TIME FUNCTIONS *****************************************************



void setup() {
  Serial.begin(9600);

  pinMode(SET_TIME, INPUT);
  pinMode(CLOCK_MODE, INPUT);
  pinMode(PATTERN, INPUT);
  pinMode(SWITCH_T, INPUT);
  pinMode(SWITCH_B, INPUT);
  pinMode(B_BUTTON, INPUT);

  attachInterrupt(digitalPinToInterrupt(SWITCH_T), set_display_state, CHANGE);  // Attenzione all'oggetto interrupt
  attachInterrupt(digitalPinToInterrupt(SWITCH_B), set_display_state, CHANGE);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 700);
  FastLED.clear();
  FastLED.show();

  // startMillis = millis();
  myRTC.begin();

  set_display_state();
}





void set_display_state() {

  buttnt = digitalRead(SWITCH_T);
  buttnb = digitalRead(SWITCH_B);

  if (buttnt && buttnb) {
    show_display = nothing;
  } else if (!buttnt && buttnb) {
    show_display = only_background;
  } else if (buttnt && !buttnb) {
    show_display = only_time;
  } else {
    show_display = nothing;
  }
}


void time_equal_to() {


    if (tempo.actual_time[0] == time_array[0] && tempo.actual_time[1] == time_array[1] && tempo.actual_time[2] == time_array[2] && tempo.actual_time[0] == time_array[3]) {

  show_display = only_time;
  // Serial.println("didn't work");
  }

}

void update_time() {

  FastLED.show();
  // FastLED.clear();
  // tempo.print_time(); 
  switch (show_display) {
    case only_background:
      FastLED.clear();
      doPlasma();
      break;
    case only_time:
      FastLED.clear();
      tempo.print_time();
      if (tm.Second % 2 == 0) {
      }
      break;
      
    case nothing:
      FastLED.clear();
      break;
  }
}




// ********************************************* END TIME FUNCTIONS ***************************************************


// ************************************************ MAIN FUNCTIONS ************************************************


void loop() {
  update_time();
  // time_equal_to();
}

// ************************************************ END MAIN FUNCTIONS ************************************************
