/*
 * The Effect abstract class for the GauntletII project.
 */

#ifndef Effect_h
#define Effect_h
#define SWITCH_T 2    // Pin for the switch interrupt
#define SWITCH_B 3
#import <FastLED.h>
#import "TimePrint.h"
class Effect {

    protected:
        CRGB *leds;
        int width, height;
    
        struct CRGB& pixel(int x, int y);
        bool inXRange(int x);
        bool inYRange(int y);
    
        void clearLeds();

    public:
        Effect(CRGB *leds, int width, int height);

        virtual void start() {};

};

#endif
