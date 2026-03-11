#ifndef Time_h
#define Time_h
#define NUM_LEDS 120
#import <FastLED.h>
#import <DS3232RTC.h>
class Time {
  protected : 

  public : 
    Time();
    void print_time();
    CRGB leds[NUM_LEDS];
    CHSV digits_color;
    void write_time(int a, int b, int c, int d);
    volatile int actual_time[];
    // int d1;
    // int d2;
    // int d3;
    // int d4;
    
};


#endif
