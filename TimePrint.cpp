#include "TimePrint.h"
#define PHOTO A1
Time ::Time() {}
int cycle_counter = 0;
CHSV digits_color_normal(26,255,150);
CHSV digits_color_bright(128, 00, 255);
CHSV digits_color_night(16, 255, 4);
// CHSV digits_colour() = digits_colour_normal();
// int r = 255;
// int g = 255;
// int b1 = 255;

const int Digits[10][10] = {
  { 32, 33, 34, 36, 69, 71, 102, 101 },  // 0
  //{32,36,66,71,101},  // 1
  { 32, 33, 35, 67, 66, 70, 102, 101 },
  { 32, 33, 36, 67, 66, 69, 102, 101 },          // 2
  { 32, 33, 36, 66, 67, 71, 102, 101 },          // 3
  { 32, 35, 67, 69, 70, 71, 65, 101 },           // 4
  { 32, 33, 34, 67, 66, 71, 102, 101 },          // 5
  { 35, 32, 67, 66, 69, 71, 102, 101 },          // 6
  { 31, 32, 33, 36, 66, 70, 102 },               // 7
  { 32, 33, 36, 34, 67, 66, 69, 71, 102, 101 },  // 8
  { 32, 33, 36, 34, 67, 66, 70, 102 },           // 9
};

int row1[17] = { 0,   1,   2,    3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15, 16  };
int row2[17] = { 33,  32,  31,   30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18, 17  };
int row3[17] = { 34,  35,  36,   37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49, 50  };
int row4[18] = { 68,  67,  66,   65,  64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53, 52, 51 };
int row5[17] = { 69,  70,  71,   72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84, 85  };
int row6[17] = { 102, 101, 100,  99,  98,  97,  96,  95,  94,  93,  92,  91,  90,  89,  88,  87, 86  };
int row7[17] = { 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119 };

DS3232RTC myRTC(false);
tmElements_t tm;
CRGB leds[120];
volatile int actual_time[4];
// Colore del testo

int d1 = 1;  // 10s digit of hour
int d2 = 5;  //  1s digit of hour
int d3 = 5;  // 10s digit of minute
int d4 = 0;  //  1s digit of minute

int time_to_int(int hour, int minute) {
  int x = map(hour, 0, 24, 0, 240);
  int y = map(minute, 0, 60, 0, 100);
  int time_index = 10 * x + y;
  return time_index;
}

CHSV lerpCHSV(CHSV c1, CHSV c2, float t) {
    return CHSV(
        c2.h,  // Interpolate Hue
        c1.s + (c2.s - c1.s) * t,  // Interpolate Saturation
        c1.v + (c2.v - c1.v) * t   // Interpolate Brightness
    );
}

CHSV compute_digits_color(int minNormal, int maxNormal, CHSV BRIGHT, CHSV NORMAL, CHSV DIM, int time_now) {

  // int time_value = time_to_int(hour, minute);
  // int red, green, blue;
  // if (hour >= 9 && hour < 17) {
  //   digits_color.hue = map(time_value, time_to_int(9, 0), time_to_int(17, 0), 191, 60);
  //   digits_color.sat = map(time_value, time_to_int(9, 0), time_to_int(17, 0), 198, 10);
  //   digits_color.val = map(time_value, time_to_int(9, 0), time_to_int(17, 0), 204, 5);
  // }

  // else if (hour >= 17 && hour < 24) {
  //   digits_color.hue = map(time_value, time_to_int(17, 0), time_to_int(23, 59), 60, 10);
  //   digits_color.sat = map(time_value, time_to_int(17, 0), time_to_int(23, 59), 20, 5);
  //   digits_color.val = map(time_value, time_to_int(17, 0), time_to_int(23, 59), 5, 0);
  // }

  // else if (hour >= 0 && hour < 9) {
  //   digits_color.hue = map(time_value, time_to_int(0, 0), time_to_int(9, 0), 10, 191);
  //   digits_color.sat = map(time_value, time_to_int(0, 0), time_to_int(9, 0), 5, 198);
  //   digits_color.val = map(time_value, time_to_int(0, 0), time_to_int(9, 0), 0, 204);
  // }

  int brightness = analogRead(PHOTO);
  if (brightness < minNormal) { 
      // Room is BRIGHTER than normal → Interpolate NORMAL → BRIGHT
      float t = (float)(brightness - 200) / (minNormal - 200);  // Map [300, minNormal] to [0,1]
      return lerpCHSV(BRIGHT, NORMAL, constrain(t, 0.0, 1.0));
  } 
  // else if (brightness > maxNormal) { 
  //     // Room is DARKER than normal → Interpolate NORMAL → DIM
  //     float t = (float)(brightness - maxNormal) / (800 - maxNormal);  // Map [maxNormal, 600] to [0,1]
  //     return lerpCHSV(NORMAL, DIM, constrain(t, 0.0, 1.0));
  else if(time_now>0&&time_now<=8){
    return DIM;
  } 
  else {
      return NORMAL;  // Within the normal range, return NORMAL color
  }

  // return digits_color;
  // Serial.print(red);
  // Serial.print(" ");
  // Serial.print(green);
  // Serial.print(" ");
  // Serial.print(blue);
  // Serial.print(" ");
}




// Posizione delle cifre

bool LEDrow_is_even(int position) {
  //int len = sizeof(Digits[number])/sizeof(Digits[number][0]);
  for (int i = 0; i < 17; i++) {
    if (position == row2[i] || position == row4[i] || position == row6[i]) {
      return 1;
    }
  }
  return 0;
}

void write_digit_one(int number, CHSV digits_color) {
  int len = sizeof(Digits[number]) / sizeof(Digits[number][0]);
  for (int i = 0; i < len; i++) {
    if (Digits[number][i] != 0) { leds[(Digits[number][i])] = digits_color; };
  }
  if (tm.Second % 2 == 0) {
    leds[42] = digits_color;
    leds[77] = digits_color;
  }
}

void write_digit_two(int number, CHSV digits_color) {

  int len = sizeof(Digits[number]) / sizeof(Digits[number][0]);
  for (int i = 0; i < len; i++) {
    if (Digits[number][i] != 0) {
      if (LEDrow_is_even(Digits[number][i])) {
        leds[(Digits[number][i]) - 4] = digits_color;
      } else if (!LEDrow_is_even(Digits[number][i])) {
        leds[(Digits[number][i]) + 4] = digits_color;
      }
    }
  };
}

void write_digit_three(int number, CHSV digits_color) {
  int len = sizeof(Digits[number]) / sizeof(Digits[number][0]);
  for (int i = 0; i < len; i++) {
    if (Digits[number][i] != 0) {
      if (LEDrow_is_even(Digits[number][i])) {
        leds[(Digits[number][i]) - 10] = digits_color;
      } else {
        leds[(Digits[number][i]) + 10] = digits_color;
      }
    }
  }
}

void write_digit_four(int number, CHSV digits_color) {
  int len = sizeof(Digits[number]) / sizeof(Digits[number][0]);
  for (int i = 0; i < len; i++) {
    if (Digits[number][i] != 0) {
      if (LEDrow_is_even(Digits[number][i])) {
        leds[(Digits[number][i]) - 14] = digits_color;
      } else {
        leds[(Digits[number][i]) + 14] = digits_color;
      }
    }
  }
}

void read_time() {

  myRTC.read(tm);
  // d4++;
  // if (d4 == 10) {
  //   d3++;
  //   d4 = 0;
  // }
  // if (d3 == 6) {
  //   d2++;
  //   d3 = 0;
  // }
  // if (d2 == 10) {
  //   d1++;
  //   d2 = 0;
  // }
  // if (d2 == 4 && d1 == 2) {
  //   d1 = 0;
  //   d2 = 0;
  //   d3 = 0;
  //   d4 = 0;
  // }
  d1 = tm.Hour / 10;
  d2 = tm.Hour % 10; 
  d3 = tm.Minute / 10;
  d4 = tm.Minute % 10;

  // delay(10);
}

void Time ::write_time(int a, int b, int c, int d) {
  read_time();
  CHSV color = compute_digits_color(450,600, digits_color_bright, digits_color_normal, digits_color_night, tm.Hour);



  write_digit_one(a, color);
  write_digit_two(b, color);
  write_digit_three(c, color);
  write_digit_four(d, color);
}


void Time ::print_time() {

  write_time(d1, d2, d3, d4);
  actual_time[0] = d1;
  actual_time[1] = d2;
  actual_time[2] = d3;
  actual_time[3] = d4;
}

// void Time ::digital_read(){

// }