#include <WS2812FX.h>

#define DEBUG 1
#define PIN 6
#define PIN2 5
#define NUM_LEDS 150

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
WS2812FX strips[2] {
  WS2812FX(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800),
  WS2812FX(NUM_LEDS, PIN2, NEO_GRBW + NEO_KHZ800)
};


// === COLORS
#define GOLD      (uint32_t) 0xFFAF00
#define DARK_ORANGE (uint32_t) 0xFF6500
#define BORDEAUX (uint32_t) 0xCD0101
#define DARK_BLUE (uint32_t) 0x1F19AF
#define LIGHT_BLUE (uint32_t) 0x00BAFF
#define DEEP_PINK (uint32_t) 0xDB016D


// === TIME AND CLOCK
// the measure for our clock
#define MEASURE 1000
#define STEP_MICRO_TIME 5

#define LOOP_SECONDS 1200
#define SECONDS_IN_MINUTE 120

byte *c;
uint16_t b_i;

unsigned long lastTimeMillis = 0;
unsigned long timeMillis = 0;
unsigned long lastTimeSeconds = 0;
unsigned long timeSeconds = 0;
unsigned long timeMinutes = 0;


int stepMillis = 10;
int step = 0;

bool next = false;
bool nextBig = false;

int nextConfig = 0;


// === LAYOUT PARAMS
#define RIGHT_1_START 0
#define RIGHT_2_START 49
#define RIGHT_3_START 79
#define RIGHT_4_START 90

#define LEFT_1_START 0
#define LEFT_2_START 47
#define LEFT_3_START 77
#define LEFT_4_START 100

// range options
uint8_t options1;
uint32_t colors1[3];
int speed1;
int mode1;

uint8_t options2;
uint32_t colors2[3];
int speed2;
int mode2;

uint8_t options3;
uint32_t colors3[3];
int speed3;
int mode3;

uint8_t options4;
uint32_t colors4[3];
int speed4;
int mode4;

//  === SETUP
void setup() { 
  #ifdef DEBUG
    Serial.begin(9600);
  #endif

  strips[0].init();
  strips[0].setBrightness(255);
  strips[0].start();

  strips[1].init();
  strips[1].setBrightness(255);
  strips[1].start();
}

void loop() {
  unsigned long showSteps = timeMinutes;

  // ==== PHASE 1 FIRE DAWN

  // COMET BIRTH
  if (showSteps == 0) {
    options1 = FADE_XXSLOW;
    options2 = FADE_MEDIUM + REVERSE;
    options3 = FADE_FAST;
    options4 = FADE_FAST + REVERSE;

    colors1[0] = YELLOW;
    colors1[1] = BLUE;
    colors1[2] = BLACK;

    colors2[0] = BLUE;
    colors2[1] = RED;
    colors2[2] = BLACK;

    colors3[0] = YELLOW;
    colors3[1] = RED;
    colors3[2] = BLACK;

    colors4[0] = BLUE;
    colors4[1] = RED;
    colors4[2] = BLACK;

    colors5[0] = YELLOW;
    colors5[1] = BLUE;
    colors5[2] = BLACK;

    speed1 = 1000;
    speed2 = 60;
    speed3 = 600;
    speed4 = 10;
    speed5 = 150;

    mode1 = FX_MODE_COMET;
    mode2 = FX_MODE_COMET;
    mode3 = FX_MODE_COMET;
    mode4 = FX_MODE_COMET;
    mode5 = FX_MODE_COMET;

    
    setRModes();
  }


  strips[1].service();
  strips[0].service();

  // TIME MANAGEMENT
  lastTimeSeconds = timeSeconds;
  lastTimeMillis = timeMillis;
  timeMillis = millis();
  timeSeconds = int(timeMillis / 1000);
  timeSeconds = timeSeconds % LOOP_SECONDS;
  timeMinutes = int(timeSeconds / SECONDS_IN_MINUTE);
  // Serial.print("Seconds: ");
  // Serial.print(timeSeconds);
  // Serial.print("Mnutes: ");
  // Serial.print(timeMinutes);
}

void setRModes() {
    strips[0].setSegment(0, RIGHT_1_START, RIGHT_2_START-1, mode1, colors1, speed1, options1);
    strips[1].setSegment(0, LEFT_1_START, LEFT_2_START-1, mode1, colors1, speed1, options1);

    strips[0].setSegment(1, RIGHT_2_START, RIGHT_3_START-1, mode2, colors2, speed2, options2);
    strips[1].setSegment(1, LEFT_2_START, LEFT_3_START-1, mode2, colors2, speed2, options2);

    strips[0].setSegment(2, RIGHT_3_START, RIGHT_4_START-1, mode3, colors3, speed3, options3);
    strips[1].setSegment(2, LEFT_3_START, LEFT_4_START-1, mode3, colors3, speed3, options3);

    strips[0].setSegment(3, RIGHT_4_START, RIGHT_5_START-1, mode4, colors4, speed4, options4);
    strips[1].setSegment(3, LEFT_4_START, LEFT_5_START-1, mode4, colors4, speed4, options4);

    strips[0].setSegment(4, RIGHT_5_START, NUM_LEDS, mode5, colors5, speed5, options5);
    strips[1].setSegment(4, LEFT_5_START, NUM_LEDS, mode5, colors5, speed5, options5);
}

// LOG THIS WHEN YOU WANT TO KNOW HOW MUCH RAM IS LEFT
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}







