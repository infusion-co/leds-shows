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

// WS2812FX strip = WS2812FX(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
// WS2812FX strip2 = WS2812FX(NUM_LEDS, PIN2, NEO_GRBW + NEO_KHZ800);

// ==== THUNDER MODE PARAMS
#define CENTRAL_NUAGE_END_0  26
#define RIGHT_NUAGE_END_0 57
#define RIGHT_THUNDER_1_END_0 87
#define RIGHT_THUNDER_2_END_0 117

#define CENTRAL_NUAGE_END_1 20
#define LEFT_NUAGE_END_1 51
#define LEFT_THUNDER_1_END_1 81
#define LEFT_THUNDER_2_END_1 111

#define THUNDER_START_1 60
#define THUNDER_START_2 80


typedef struct
 {
      int MAX_FLASHES_NUMBER;
      int MIN_FLASHES_NUMBER;
      int FLASHES_OUT_OF;
      int STRIKE_RED_COLOR_RATIO;
      int STRIKE_GREEN_COLOR_RATIO;
      int STRIKE_BLUE_COLOR_RATIO;
      int STRIKE_LIGHT_RATIO;
      int STRIKE_LIGHT_BASE;
      int STRIKE_LIGHT_RANDOM_RATIO;
      int STRIKE_RED_RANDOM_RATIO;
      int STRIKE_GREEN_RANDOM_RATIO;
      int STRIKE_BLUE_RANDOM_RATIO;

      int MAX_REMOVE_NUMBER;
      int MIN_REMOVE_NUMBER;

      int strikeRedRatio;
      int strikeBlueRatio;
      int strikeGreenRatio;

      int flashesRemaining;
      int flashesSteps;

      int removesRemaining;
      int removesSteps;
 }  thunder_params_type;

thunder_params_type thunders[2];

uint8_t thunderMode0;
uint8_t thunderMode1;

// options for thunders and nuages
uint8_t toptions;
uint32_t tcolors[3];
int tspeed;
int tmode;

// central, left and right cloud
uint8_t cc_options;
uint32_t cc_colors[3];
int cc_speed;
int cc_mode;

uint8_t rc_options;
uint32_t rc_colors[3];
int rc_speed;
int rc_mode;

uint8_t lc_options;
uint32_t lc_colors[3];
int lc_speed;
int lc_mode;


// the measure for our clock
#define MEASURE 1000
#define STEP_MICRO_TIME 5

#define LOOP_SECONDS 1200 
#define SECONDS_IN_MINUTE 60

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

void setup() { 
  #ifdef DEBUG
    Serial.begin(9600);
  #endif

  strips[0].init();
  strips[0].setBrightness(255);
  thunderMode0 = strips[0].setCustomMode(F("Thunder Effect 0"), thunderEffect0);
  strips[0].start();

  thunderMode1 = strips[1].setCustomMode(F("Thunder Effect 1"), thunderEffect1);
  strips[1].init();
  strips[1].setBrightness(255);
  strips[1].start();
}

void loop() {

  // pluie, crepitant, multicolores, flashes tournants et aleatoires
  // arc en ciel
  // feu
 
  // == REGULAR THUNDER EFFECT INIT

  if (timeSeconds == 0) {
    if (nextConfig == 0) {
      nextConfig++;
    }

    regularThunderEffectSettings();
    strips[0].setSegment(0, 0, CENTRAL_NUAGE_END_0, FX_MODE_RAINBOW, MAGENTA, 50, FADE_GLACIAL);
    strips[0].setSegment(1, CENTRAL_NUAGE_END_0 + 1, RIGHT_NUAGE_END_0, FX_MODE_BREATH, GREEN, 300, FADE_GLACIAL);
    strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, NUM_LEDS, thunderMode0, WHITE, 3, 1);

    strips[1].setSegment(0, 0, CENTRAL_NUAGE_END_1, FX_MODE_RAINBOW, MAGENTA, 50, FADE_GLACIAL);
    strips[1].setSegment(1, CENTRAL_NUAGE_END_1 + 1 , LEFT_NUAGE_END_1, FX_MODE_BREATH, BLUE, 100, FADE_GLACIAL);
    strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, NUM_LEDS, thunderMode1, WHITE, 3, 1);
  }


  // === TEST CLOUD TURNING FLASHES
  if (timeMinutes == -1) {
    if (nextConfig == 1) {
      nextConfig++;
      stepMillis = 100;
    }

    step = (int) floor(timeMillis / stepMillis)  % 3;
    next = (timeMillis != lastTimeMillis);
    int flashMode = FX_MODE_STROBE;
    uint32_t flashColors[] = {WHITE, RED, BLACK};
    int speed = 70;

    if (next) {
      if (step == 0) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = flashColors[0];
        lc_colors[1] = flashColors[1];
        lc_colors[2] = flashColors[2];
        lc_speed = speed;
        lc_mode = flashMode;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 1) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = flashColors[0];
        cc_colors[1] = flashColors[1];
        cc_colors[2] = flashColors[2];
        cc_speed = speed;
        cc_mode = flashMode;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 2) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = flashColors[0];
        rc_colors[1] = flashColors[1];
        rc_colors[2] = flashColors[2];
        rc_speed = speed;
        rc_mode = flashMode;
      }

      setModes();
    }
  }

  // TEST ALTERNATE FLASHING BARS ACCELERATING
  // XXX BAD
  if (timeMinutes == -1) {
    if (nextConfig == 2) {
      nextConfig++;
      stepMillis = 10;
    }

    step = (int) floor(millis() / stepMillis)  % 6;
    // next = (timeMillis != lastTimeMillis);
    next = true;
    nextBig = (timeSeconds != lastTimeSeconds);
    int flashingMode = FX_MODE_STATIC;
    uint32_t flashingColors[] = {YELLOW, RED, YELLOW};

    if (nextBig) {
      // stepMillis = stepMillis - (int) floor(30 / 10);
    }

    if (next) {
      if (step == 0) {
        strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, RIGHT_THUNDER_1_END_0,
          flashingMode, flashingColors, 30, false
        );

        strips[0].setSegment(3, RIGHT_THUNDER_1_END_0 + 1, RIGHT_THUNDER_2_END_0, FX_MODE_STATIC, BLACK, 30, false);

        strips[0].setSegment(4, RIGHT_THUNDER_2_END_0 + 1, NUM_LEDS, FX_MODE_STATIC, BLACK, 30, false);


        strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, LEFT_THUNDER_1_END_1, FX_MODE_STATIC, BLACK, 30, false);

        strips[1].setSegment(3, LEFT_THUNDER_1_END_1 + 1, LEFT_THUNDER_2_END_1, FX_MODE_STATIC, BLACK, 30, false);

        strips[1].setSegment(4, LEFT_THUNDER_2_END_1 + 1, NUM_LEDS, FX_MODE_STATIC, BLACK, 30, false);
      }


      if (step == 1) {
        strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, RIGHT_THUNDER_1_END_0, 
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[0].setSegment(3, RIGHT_THUNDER_1_END_0 + 1, RIGHT_THUNDER_2_END_0,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[0].setSegment(4, RIGHT_THUNDER_2_END_0 + 1, NUM_LEDS,
          FX_MODE_STATIC, BLACK, 30, false
        );


        strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, LEFT_THUNDER_1_END_1,
          flashingMode, flashingColors, 30, false
        );

        strips[1].setSegment(3, LEFT_THUNDER_1_END_1 + 1, LEFT_THUNDER_2_END_1,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[1].setSegment(4, LEFT_THUNDER_2_END_1 + 1, NUM_LEDS, 
          FX_MODE_STATIC, BLACK, 30, false
        );
      }


      if (step == 2) {
        strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, RIGHT_THUNDER_1_END_0, 
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[0].setSegment(3, RIGHT_THUNDER_1_END_0 + 1, RIGHT_THUNDER_2_END_0,
          flashingMode, flashingColors, 30, false
        );

        strips[0].setSegment(4, RIGHT_THUNDER_2_END_0 + 1, NUM_LEDS,
          FX_MODE_STATIC, BLACK, 30, false
        );


        strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, LEFT_THUNDER_1_END_1,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[1].setSegment(3, LEFT_THUNDER_1_END_1 + 1, LEFT_THUNDER_2_END_1,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[1].setSegment(4, LEFT_THUNDER_2_END_1 + 1, NUM_LEDS, 
          FX_MODE_STATIC, BLACK, 30, false
        );
      }

      if (step == 3) {
        strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, RIGHT_THUNDER_1_END_0, 
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[0].setSegment(3, RIGHT_THUNDER_1_END_0 + 1, RIGHT_THUNDER_2_END_0,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[0].setSegment(4, RIGHT_THUNDER_2_END_0 + 1, NUM_LEDS,
          FX_MODE_STATIC, BLACK, 30, false
        );


        strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, LEFT_THUNDER_1_END_1,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[1].setSegment(3, LEFT_THUNDER_1_END_1 + 1, LEFT_THUNDER_2_END_1,
          flashingMode, flashingColors, 30, false
        );

        strips[1].setSegment(4, LEFT_THUNDER_2_END_1 + 1, NUM_LEDS, 
          FX_MODE_STATIC, BLACK, 30, false
        );
      }

      if (step == 4) {
        strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, RIGHT_THUNDER_1_END_0, 
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[0].setSegment(3, RIGHT_THUNDER_1_END_0 + 1, RIGHT_THUNDER_2_END_0,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[0].setSegment(4, RIGHT_THUNDER_2_END_0 + 1, NUM_LEDS,
          flashingMode, flashingColors, 30, false
        );


        strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, LEFT_THUNDER_1_END_1,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[1].setSegment(3, LEFT_THUNDER_1_END_1 + 1, LEFT_THUNDER_2_END_1,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[1].setSegment(4, LEFT_THUNDER_2_END_1 + 1, NUM_LEDS, 
          FX_MODE_STATIC, BLACK, 30, false
        );
      }

      if (step == 5) {
        strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, RIGHT_THUNDER_1_END_0, 
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[0].setSegment(3, RIGHT_THUNDER_1_END_0 + 1, RIGHT_THUNDER_2_END_0,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[0].setSegment(4, RIGHT_THUNDER_2_END_0 + 1, NUM_LEDS,
          FX_MODE_STATIC, BLACK, 30, false
        );


        strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, LEFT_THUNDER_1_END_1,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[1].setSegment(3, LEFT_THUNDER_1_END_1 + 1, LEFT_THUNDER_2_END_1,
          FX_MODE_STATIC, BLACK, 30, false
        );

        strips[1].setSegment(4, LEFT_THUNDER_2_END_1 + 1, NUM_LEDS, 
          flashingMode, flashingColors, 30, false
        );
      }
    }
  }
  
  // ==== PHASE 1 FIRE DAWN
  
  unsigned long showSteps = timeMinutes;

  // COMET BIRTH
  if (showSteps == 1 || showSteps == 0) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = PURPLE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = RED;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = MAGENTA;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    toptions = FADE_GLACIAL;
    tcolors[0] = (uint32_t) 0xFF6500; // dark orange
    tcolors[1] = RED;
    tcolors[2] = BLACK;
    tspeed = 30;
    tmode = FX_MODE_COMET;
    
    setModes();
  }
  
  // FIRE FLICKER
  if (showSteps == 2) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = PURPLE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = RED;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = MAGENTA;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    toptions = FADE_GLACIAL;
    tcolors[0] = ORANGE; // dark orange
    tcolors[1] = BLUE;
    tcolors[2] = RED;
    tspeed = 3000;
    tmode = FX_MODE_FIRE_FLICKER;
    
    setModes();
  }

  // FIRE FLICKER INTENSE
  if (showSteps == 3) {
    
    lc_options = FADE_GLACIAL;
    lc_colors[0] = PURPLE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = RED;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = MAGENTA;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    toptions = FADE_GLACIAL;
    tcolors[0] = ORANGE; // dark orange
    tcolors[1] = BLACK;
    tcolors[2] = BLACK;
    tspeed = 2000;
    tmode = FX_MODE_FIRE_FLICKER_INTENSE;
    
    setModes();
  }

  // FIRE THEATER CHASE
  if (showSteps == 4) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = PURPLE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = RED;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = MAGENTA;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    toptions = FADE_GLACIAL;
    tcolors[0] = RED;
    tcolors[1] = ORANGE;
    tcolors[2] = (uint32_t) 0xFF6500;
    tspeed = 4000;
    tmode = FX_MODE_THEATER_CHASE;
    
    setModes();
  }

  // FIRE TWINKLE FADE -- keeps previous colors and makes small dots fade
  if (showSteps == 5) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = PURPLE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = RED;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = MAGENTA;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    toptions = FADE_GLACIAL;
    tcolors[0] = (uint32_t) 0xFFD500;
    tcolors[1] = RED;
    tcolors[2] = BLACK;
    tspeed = 10;
    tmode = FX_MODE_TWINKLE_FADE;
    
    setModes();
  }

  // CIRCUS COMBUSTUS BLACK WHITE RED circus show + STROBING RED WHITE CLOUD
  if (showSteps == 6) {
    stepMillis = 100;
    step = (int) floor(timeMillis / stepMillis)  % 3;
    next = (timeMillis != lastTimeMillis);
    int flashMode = FX_MODE_STROBE;
    uint32_t lcflashColors[] = {WHITE, RED, BLACK};
    uint32_t ccflashColors[] = {WHITE, RED, BLACK};
    uint32_t rcflashColors[] = {WHITE, RED, BLACK};
    int speed = 70;

    if (next) {
      if (step == 0) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = lcflashColors[0];
        lc_colors[1] = lcflashColors[1];
        lc_colors[2] = lcflashColors[2];
        lc_speed = speed;
        lc_mode = flashMode;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 1) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = ccflashColors[0];
        cc_colors[1] = ccflashColors[1];
        cc_colors[2] = ccflashColors[2];
        cc_speed = speed;
        cc_mode = flashMode;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 2) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = rcflashColors[0];
        rc_colors[1] = rcflashColors[1];
        rc_colors[2] = rcflashColors[2];
        rc_speed = speed;
        rc_mode = flashMode;
      }
    }

    toptions = FADE_GLACIAL;
    tcolors[0] = (uint32_t) 0xFFD500;
    tcolors[1] = RED;
    tcolors[2] = BLACK;
    tspeed = 150;
    tmode = FX_MODE_CIRCUS_COMBUSTUS;

    setModes();
  }

  // BLINK very simple slow flash or fast flash
  /*
  if (showSteps == 7) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = PURPLE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = RED;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = MAGENTA;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    toptions = FADE_GLACIAL;
    tcolors[0] = (uint32_t) 0xFFD500;
    tcolors[1] = RED;
    tcolors[2] = YELLOW;
    tspeed = 10;
    tmode = FX_MODE_BLINK;
    
    setModes();
  }
  */

  // ==== PHASE 2 SUN BRIGHT DAY
  // CLICKING SUNS + RUNNING DAWN
  if (showSteps == 8 || showSteps == 7) {
    stepMillis = 100;
    step = (int) floor(timeMillis / stepMillis)  % 3;
    next = (timeMillis != lastTimeMillis);
    int flashMode = FX_MODE_STROBE;
    uint32_t lcflashColors[] = {YELLOW, ORANGE, BLACK};
    uint32_t ccflashColors[] = {YELLOW, ORANGE, BLACK};
    // coral on dark orange
    uint32_t rcflashColors[] = {YELLOW, ORANGE, BLACK};
    int speed = 300;

    if (next) {
      if (step == 0) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = lcflashColors[0];
        lc_colors[1] = lcflashColors[1];
        lc_colors[2] = lcflashColors[2];
        lc_speed = speed;
        lc_mode = flashMode;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 1) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = ccflashColors[0];
        cc_colors[1] = ccflashColors[1];
        cc_colors[2] = ccflashColors[2];
        cc_speed = speed;
        cc_mode = flashMode;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 2) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = rcflashColors[0];
        rc_colors[1] = rcflashColors[1];
        rc_colors[2] = rcflashColors[2];
        rc_speed = speed;
        rc_mode = flashMode;
      }
    }

    toptions = FADE_GLACIAL;
    tcolors[0] = (uint32_t) 0xFFD500;
    tcolors[1] = RED;
    tcolors[2] = YELLOW;
    tspeed = 3000;
    tmode = FX_MODE_RUNNING_RED_BLUE;
    
    setModes();
  }

  // BREATHING SUNS AND BREATHING SKY
  if (showSteps == 9) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = ORANGE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_BREATH;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = YELLOW;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_BREATH;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = (uint32_t) 0xffd700;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_BREATH;

    toptions = FADE_GLACIAL;
    tcolors[0] = (uint32_t) 0x00bfff;
    tcolors[1] = BLUE;
    tcolors[2] = BLACK;
    tspeed = 3000;
    tmode = FX_MODE_BREATH;
    
    setModes();
  }

  // BREATHING SUNS + RAINBOWS CHASE
  if (showSteps == 10) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = ORANGE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_BREATH;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = YELLOW;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_BREATH;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = (uint32_t) 0xffd700;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_BREATH;

    toptions = FADE_GLACIAL;
    tcolors[0] = (uint32_t) 0x00bfff;
    tcolors[1] = BLUE;
    tcolors[2] = BLACK;
    tspeed = 300;
    tmode = FX_MODE_CHASE_RAINBOW;
    
    setModes();
  }

  // BREATHING SUNS + RAINBOWS SLOW
  if (showSteps == 11) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = ORANGE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_BREATH;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = YELLOW;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_BREATH;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = (uint32_t) 0xffd700;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_BREATH;

    toptions = FADE_GLACIAL;
    tcolors[0] = (uint32_t) 0x00bfff;
    tcolors[1] = BLUE;
    tcolors[2] = BLACK;
    tspeed = 300;
    tmode = FX_MODE_RAINBOW_CYCLE;
    
    setModes();
  }

  // BREATHING SUNS + YELLOW RAYLIGHTS
  if (showSteps == 12) {
    
    lc_options = FADE_GLACIAL;
    lc_colors[0] = ORANGE;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_BREATH;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = YELLOW;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_BREATH;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = (uint32_t) 0xffd700;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_BREATH;

    redAndGreenThunderEffectSettings();
    
    setModesNoThunder();
    setThunderModes();
  }

  // BLUE CLOUDS + YELLOW RAYLIGHTS
  if (showSteps == 13) {
    
    lc_options = FADE_GLACIAL;
    lc_colors[0] = BLUE;
    lc_colors[1] = (uint32_t) 0x00bfff;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_TWINKLE_FADE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = CYAN;
    cc_colors[1] = BLUE;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_TWINKLE_FADE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = (uint32_t) 0x00bfff;
    rc_colors[1] = (uint32_t) 0x00008b;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_TWINKLE_FADE;

    redAndGreenThunderEffectSettings();
    
    setModesNoThunder();
    setThunderModes();
  }

  // FLASHING DARK BLUE CLOUDS + YELLOW THUNDER
  if (showSteps == 14) {
    stepMillis = 100;
    step = (int) floor(timeMillis / stepMillis)  % 3;
    next = (timeMillis != lastTimeMillis);
    int flashMode = FX_MODE_STROBE;
    uint32_t lcflashColors[] = {BLUE, (uint32_t) 0x00bfff, BLACK};
    uint32_t ccflashColors[] = {CYAN, BLUE, BLACK};
    // coral on dark orange
    uint32_t rcflashColors[] = {(uint32_t) 0x00bfff, (uint32_t) 0x00008b, BLACK};
    int speed = 30;

    if (next) {
      if (step == 0) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = lcflashColors[0];
        lc_colors[1] = lcflashColors[1];
        lc_colors[2] = lcflashColors[2];
        lc_speed = speed;
        lc_mode = flashMode;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 1) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = ccflashColors[0];
        cc_colors[1] = ccflashColors[1];
        cc_colors[2] = ccflashColors[2];
        cc_speed = speed;
        cc_mode = flashMode;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 2) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = rcflashColors[0];
        rc_colors[1] = rcflashColors[1];
        rc_colors[2] = rcflashColors[2];
        rc_speed = speed;
        rc_mode = flashMode;
      }
    }

    redAndGreenThunderEffectSettings();
    
    setModesNoThunder();
    setThunderModes();
  }
  
  // ===== PHASE 3 DARK NIGHT THUNDER > RAIN
  // FLASHING DARK BLUE CLOUDS + REGULAR THUNDER
  if (showSteps == 15) {
    stepMillis = 100;
    step = (int) floor(timeMillis / stepMillis)  % 3;
    next = (timeMillis != lastTimeMillis);
    int flashMode = FX_MODE_STROBE;
    uint32_t lcflashColors[] = {BLUE, (uint32_t) 0x00bfff, BLACK};
    uint32_t ccflashColors[] = {CYAN, BLUE, BLACK};
    // coral on dark orange
    uint32_t rcflashColors[] = {(uint32_t) 0x00bfff, (uint32_t) 0x00008b, BLACK};
    int speed = 30;

    if (next) {
      if (step == 0) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = lcflashColors[0];
        lc_colors[1] = lcflashColors[1];
        lc_colors[2] = lcflashColors[2];
        lc_speed = speed;
        lc_mode = flashMode;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 1) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = ccflashColors[0];
        cc_colors[1] = ccflashColors[1];
        cc_colors[2] = ccflashColors[2];
        cc_speed = speed;
        cc_mode = flashMode;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = BLACK;
        rc_colors[1] = BLACK;
        rc_colors[2] = BLACK;
        rc_speed = speed;
        rc_mode = FX_MODE_STATIC;
      }


      if (step == 2) {
        lc_options = FADE_GLACIAL;
        lc_colors[0] = BLACK;
        lc_colors[1] = BLACK;
        lc_colors[2] = BLACK;
        lc_speed = speed;
        lc_mode = FX_MODE_STATIC;

        cc_options = FADE_GLACIAL;
        cc_colors[0] = BLACK;
        cc_colors[1] = BLACK;
        cc_colors[2] = BLACK;
        cc_speed = speed;
        cc_mode = FX_MODE_STATIC;

        rc_options = FADE_GLACIAL;
        rc_colors[0] = rcflashColors[0];
        rc_colors[1] = rcflashColors[1];
        rc_colors[2] = rcflashColors[2];
        rc_speed = speed;
        rc_mode = flashMode;
      }
    }

    regularThunderEffectSettings2();
    
    setModesNoThunder();
    setThunderModes();
  }

  // FIRE WHITE CLOUD + REGULAR THUNDER
  if (showSteps == 16) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = CYAN;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = WHITE;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = (uint32_t) 0x00bfff;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    regularThunderEffectSettings2();
    
    setModesNoThunder();
    setThunderModes();
  }

  //FIRE WHITE CLOUD + BLUE COMETS
  if (showSteps == 17) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = CYAN;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = WHITE;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = (uint32_t) 0x00bfff;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    toptions = FADE_GLACIAL;
    tcolors[0] = BLUE; // dark orange
    tcolors[1] = BLACK;
    tcolors[2] = BLACK;
    tspeed = 3;
    tmode = FX_MODE_COMET;
    
    setModes();
  }

  // FIRE WHITE CLOUD + BLUE THUNDER
  if (showSteps == 18) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = CYAN;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 1300;
    lc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = WHITE;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_FIRE_FLICKER_INTENSE;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = (uint32_t) 0x00bfff;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 1500;
    rc_mode = FX_MODE_FIRE_FLICKER_INTENSE;
    
    blueThunderEffectSettings();
    
    setModesNoThunder();
    setThunderModes();
  }

  // RAINBOW CLOUDS + CYAN
  if (showSteps == 19) {
    lc_options = FADE_GLACIAL;
    lc_colors[0] = CYAN;
    lc_colors[1] = BLACK;
    lc_colors[2] = BLACK;
    lc_speed = 30;
    lc_mode = FX_MODE_RAINBOW;

    cc_options = FADE_GLACIAL;
    cc_colors[0] = WHITE;
    cc_colors[1] = BLACK;
    cc_colors[2] = BLACK;
    cc_speed = 1000;
    cc_mode = FX_MODE_CHASE_RAINBOW;

    rc_options = FADE_GLACIAL;
    rc_colors[0] = (uint32_t) 0x00bfff;
    rc_colors[1] = BLACK;
    rc_colors[2] = BLACK;
    rc_speed = 5000;
    rc_mode = FX_MODE_RAINBOW_CYCLE;
    
    blueAndGreenThunderEffectSettings();
    
    setModesNoThunder();
    setThunderModes();
  }
  //
  
  
  // CREPUSCULE, COLD, RAIN, SNOW, AND THUNDER, FLASHES, STROBES
  if (showSteps == -1) {
    blueThunderEffectSettings();
    strips[0].setSegment(0, 0, CENTRAL_NUAGE_END_0, FX_MODE_CHASE_RAINBOW, MAGENTA, 50, FADE_GLACIAL);
    strips[0].setSegment(1, CENTRAL_NUAGE_END_0 + 1, RIGHT_NUAGE_END_0, FX_MODE_BREATH, GREEN, 300, FADE_GLACIAL);
    strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, NUM_LEDS, thunderMode0, WHITE, 3, 1);

    strips[1].setSegment(0, 0, CENTRAL_NUAGE_END_1, FX_MODE_CHASE_RAINBOW, MAGENTA, 50, FADE_GLACIAL);
    strips[1].setSegment(1, CENTRAL_NUAGE_END_1 + 1 , LEFT_NUAGE_END_1 , FX_MODE_BREATH, BLUE, 100, FADE_GLACIAL);
    strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, NUM_LEDS, thunderMode1, WHITE, 3, 1);
  }
 
  // ELECTRIC FUTURE AND MATRIX BLIPS FROM CYAN TO GREEN
  if (showSteps == -1) {
    blueAndGreenThunderEffectSettings();
    strips[0].setSegment(0, 0, CENTRAL_NUAGE_END_0, FX_MODE_CHASE_RAINBOW, MAGENTA, 50, FADE_GLACIAL);
    strips[0].setSegment(1, CENTRAL_NUAGE_END_0 + 1, RIGHT_NUAGE_END_0, FX_MODE_BREATH, GREEN, 300, FADE_GLACIAL);
    strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, NUM_LEDS, thunderMode0, WHITE, 3, 1);

    strips[1].setSegment(0, 0, CENTRAL_NUAGE_END_1, FX_MODE_CHASE_RAINBOW, MAGENTA, 50, FADE_GLACIAL);
    strips[1].setSegment(1, CENTRAL_NUAGE_END_1 + 1 , LEFT_NUAGE_END_1 , FX_MODE_BREATH, BLUE, 100, FADE_GLACIAL);
    strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, NUM_LEDS, thunderMode1, WHITE, 3, 1);
  }
 
  // PINK + SHINY AND FUNKY RANDOM PARTY STROBING
  if (showSteps == -1) {
    blueAndRedThunderEffectSettings();
    strips[0].setSegment(0, 0, CENTRAL_NUAGE_END_0, FX_MODE_CHASE_RAINBOW, MAGENTA, 50, FADE_GLACIAL);
    strips[0].setSegment(1, CENTRAL_NUAGE_END_0 + 1, RIGHT_NUAGE_END_0, FX_MODE_BREATH, GREEN, 300, FADE_GLACIAL);
    strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, NUM_LEDS, thunderMode0, WHITE, 3, 1);

    strips[1].setSegment(0, 0, CENTRAL_NUAGE_END_1, FX_MODE_CHASE_RAINBOW, MAGENTA, 50, FADE_GLACIAL);
    strips[1].setSegment(1, CENTRAL_NUAGE_END_1 + 1 , LEFT_NUAGE_END_1 , FX_MODE_BREATH, BLUE, 100, FADE_GLACIAL);
    strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, NUM_LEDS, thunderMode1, WHITE, 3, 1);
  }
  

  strips[1].service();
  strips[0].service();
  
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

void setModes() {
    strips[0].setSegment(0, 0, CENTRAL_NUAGE_END_0, cc_mode, cc_colors, cc_speed, cc_options);
    strips[1].setSegment(0, 0, CENTRAL_NUAGE_END_1, cc_mode, cc_colors, cc_speed, cc_options);

    strips[0].setSegment(1, CENTRAL_NUAGE_END_0 + 1, RIGHT_NUAGE_END_0, rc_mode, rc_colors, rc_speed, rc_options);
    
    strips[1].setSegment(1, CENTRAL_NUAGE_END_1 + 1 , LEFT_NUAGE_END_1, lc_mode, lc_colors, lc_speed, lc_options);
    
    strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, NUM_LEDS, tmode, tcolors, tspeed, toptions);
    strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, NUM_LEDS, tmode, tcolors, tspeed, toptions);
}

void setModesNoThunder() {
    strips[0].setSegment(0, 0, CENTRAL_NUAGE_END_0, cc_mode, cc_colors, cc_speed, cc_options);
    strips[1].setSegment(0, 0, CENTRAL_NUAGE_END_1, cc_mode, cc_colors, cc_speed, cc_options);

    strips[0].setSegment(1, CENTRAL_NUAGE_END_0 + 1, RIGHT_NUAGE_END_0, rc_mode, rc_colors, rc_speed, rc_options);
    
    strips[1].setSegment(1, CENTRAL_NUAGE_END_1 + 1 , LEFT_NUAGE_END_1, lc_mode, lc_colors, lc_speed, lc_options);
}

void setThunderModes() {
  strips[1].setSegment(2, LEFT_NUAGE_END_1 + 1, NUM_LEDS, thunderMode1, WHITE, 3, 1);
    strips[0].setSegment(2, RIGHT_NUAGE_END_0 + 1, NUM_LEDS, thunderMode0, WHITE, 3, 1);
}

void regularThunderEffectSettings() {
  thunders[0].MAX_FLASHES_NUMBER = 7;
  thunders[0].MIN_FLASHES_NUMBER = 3;

  thunders[0].FLASHES_OUT_OF = 3;

  thunders[0].STRIKE_RED_COLOR_RATIO = 200;
  thunders[0].STRIKE_BLUE_COLOR_RATIO = 200;
  thunders[0].STRIKE_GREEN_COLOR_RATIO = 200;
  thunders[0].STRIKE_LIGHT_RATIO = 150;
  thunders[0].STRIKE_LIGHT_BASE = 10;
  thunders[0].STRIKE_LIGHT_RANDOM_RATIO = 40;
  thunders[0].STRIKE_RED_RANDOM_RATIO = 40;
  thunders[0].STRIKE_GREEN_RANDOM_RATIO = 40;
  thunders[0].STRIKE_BLUE_RANDOM_RATIO = 40;
  
  thunders[0].MAX_REMOVE_NUMBER = 40;
  thunders[0].MIN_REMOVE_NUMBER = 10;
  
  thunders[0].strikeRedRatio = 0;
  thunders[0].strikeBlueRatio = 0;
  thunders[0].strikeGreenRatio = 0;
  
  thunders[0].flashesRemaining = 0;
  thunders[0].flashesSteps = -1;
  
  thunders[0].removesRemaining = -1;
  thunders[0].removesSteps = 0;

  
  thunders[1].MAX_FLASHES_NUMBER = 7;
  thunders[1].MIN_FLASHES_NUMBER = 3;

  thunders[1].FLASHES_OUT_OF = 3;

  thunders[1].STRIKE_RED_COLOR_RATIO = 200;
  thunders[1].STRIKE_BLUE_COLOR_RATIO = 200;
  thunders[1].STRIKE_GREEN_COLOR_RATIO = 200;
  thunders[1].STRIKE_LIGHT_RATIO = 150;
  thunders[1].STRIKE_LIGHT_BASE = 10;
  thunders[1].STRIKE_LIGHT_RANDOM_RATIO = 40;
  thunders[1].STRIKE_RED_RANDOM_RATIO = 40;
  thunders[1].STRIKE_GREEN_RANDOM_RATIO = 40;
  thunders[1].STRIKE_BLUE_RANDOM_RATIO = 40;
  
  thunders[1].MAX_REMOVE_NUMBER = 40;
  thunders[1].MIN_REMOVE_NUMBER = 10;
  
  thunders[1].strikeRedRatio = 0;
  thunders[1].strikeBlueRatio = 0;
  thunders[1].strikeGreenRatio = 0;
  
  thunders[1].flashesRemaining = 0;
  thunders[1].flashesSteps = -1;
  
  thunders[1].removesRemaining = -1;
  thunders[1].removesSteps = 0;  
}

void rainbowThunderEffectSettings() {
  thunders[0].MAX_FLASHES_NUMBER = 7;
  thunders[0].MIN_FLASHES_NUMBER = 3;

  thunders[0].FLASHES_OUT_OF = 2;

  thunders[0].STRIKE_RED_COLOR_RATIO = 200;
  thunders[0].STRIKE_BLUE_COLOR_RATIO = 200;
  thunders[0].STRIKE_GREEN_COLOR_RATIO = 200;
  thunders[0].STRIKE_LIGHT_RATIO = 0;
  thunders[0].STRIKE_LIGHT_BASE = 0;
  thunders[0].STRIKE_LIGHT_RANDOM_RATIO = 50;
  thunders[0].STRIKE_RED_RANDOM_RATIO = 50;
  thunders[0].STRIKE_GREEN_RANDOM_RATIO = 50;
  thunders[0].STRIKE_BLUE_RANDOM_RATIO = 50;
  
  thunders[0].MAX_REMOVE_NUMBER = 80;
  thunders[0].MIN_REMOVE_NUMBER = 30;
  
  thunders[0].strikeRedRatio = 0;
  thunders[0].strikeBlueRatio = 0;
  thunders[0].strikeGreenRatio = 0;
  
  thunders[0].flashesRemaining = 0;
  thunders[0].flashesSteps = -1;
  
  thunders[0].removesRemaining = -1;
  thunders[0].removesSteps = 0;

  
  thunders[1].MAX_FLASHES_NUMBER = 7;
  thunders[1].MIN_FLASHES_NUMBER = 3;

  thunders[1].FLASHES_OUT_OF = 2;

  thunders[1].STRIKE_RED_COLOR_RATIO = 200;
  thunders[1].STRIKE_BLUE_COLOR_RATIO = 200;
  thunders[1].STRIKE_GREEN_COLOR_RATIO = 200;
  thunders[1].STRIKE_LIGHT_RATIO = 0;
  thunders[1].STRIKE_LIGHT_BASE = 0;
  thunders[1].STRIKE_LIGHT_RANDOM_RATIO = 50;
  thunders[1].STRIKE_RED_RANDOM_RATIO = 50;
  thunders[1].STRIKE_GREEN_RANDOM_RATIO = 50;
  thunders[1].STRIKE_BLUE_RANDOM_RATIO = 50;
  
  thunders[1].MAX_REMOVE_NUMBER = 80;
  thunders[1].MIN_REMOVE_NUMBER = 30;
  
  thunders[1].strikeRedRatio = 0;
  thunders[1].strikeBlueRatio = 0;
  thunders[1].strikeGreenRatio = 0;
  
  thunders[1].flashesRemaining = 0;
  thunders[1].flashesSteps = -1;
  
  thunders[1].removesRemaining = -1;
  thunders[1].removesSteps = 0;  
}

void regularThunderEffectSettings2() {
  thunders[0].STRIKE_RED_COLOR_RATIO = 200;
  thunders[0].STRIKE_BLUE_COLOR_RATIO = 200;
  thunders[0].STRIKE_GREEN_COLOR_RATIO = 200;
  thunders[0].STRIKE_LIGHT_RATIO = 150;
  thunders[0].STRIKE_LIGHT_BASE = 10;
  thunders[0].STRIKE_LIGHT_RANDOM_RATIO = 40;
  thunders[0].STRIKE_RED_RANDOM_RATIO = 40;
  thunders[0].STRIKE_GREEN_RANDOM_RATIO = 40;
  thunders[0].STRIKE_BLUE_RANDOM_RATIO = 40;
  
  thunders[1].STRIKE_RED_COLOR_RATIO = 200;
  thunders[1].STRIKE_BLUE_COLOR_RATIO = 200;
  thunders[1].STRIKE_GREEN_COLOR_RATIO = 200;
  thunders[1].STRIKE_LIGHT_RATIO = 150;
  thunders[1].STRIKE_LIGHT_BASE = 10;
  thunders[1].STRIKE_LIGHT_RANDOM_RATIO = 40;
  thunders[1].STRIKE_RED_RANDOM_RATIO = 40;
  thunders[1].STRIKE_GREEN_RANDOM_RATIO = 40;
  thunders[1].STRIKE_BLUE_RANDOM_RATIO = 40; 
}

void redThunderEffectSettings() {
  thunders[0].STRIKE_RED_COLOR_RATIO = 230;
  thunders[0].STRIKE_BLUE_COLOR_RATIO = 10;
  thunders[0].STRIKE_GREEN_COLOR_RATIO = 10;
  thunders[0].STRIKE_LIGHT_RATIO = 0;
  thunders[0].STRIKE_LIGHT_BASE = 0;
  thunders[0].STRIKE_LIGHT_RANDOM_RATIO = 0;
  thunders[0].STRIKE_RED_RANDOM_RATIO = 0;
  thunders[0].STRIKE_GREEN_RANDOM_RATIO = 5;
  thunders[0].STRIKE_BLUE_RANDOM_RATIO = 5;

  thunders[1].STRIKE_RED_COLOR_RATIO = 230;
  thunders[1].STRIKE_BLUE_COLOR_RATIO = 10;
  thunders[1].STRIKE_GREEN_COLOR_RATIO = 10;
  thunders[1].STRIKE_LIGHT_RATIO = 0;
  thunders[1].STRIKE_LIGHT_BASE = 0;
  thunders[1].STRIKE_LIGHT_RANDOM_RATIO = 0;
  thunders[1].STRIKE_RED_RANDOM_RATIO = 0;
  thunders[1].STRIKE_GREEN_RANDOM_RATIO = 5;
  thunders[1].STRIKE_BLUE_RANDOM_RATIO = 5;
}

void lightBlueThunderEffectSettings() {
  thunders[0].STRIKE_RED_COLOR_RATIO = 10;
  thunders[0].STRIKE_BLUE_COLOR_RATIO = 230;
  thunders[0].STRIKE_GREEN_COLOR_RATIO = 10;
  thunders[0].STRIKE_LIGHT_RATIO = 50;
  thunders[0].STRIKE_LIGHT_BASE = 5;
  thunders[0].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[0].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[0].STRIKE_GREEN_RANDOM_RATIO = 5;

  thunders[1].STRIKE_RED_COLOR_RATIO = 10;
  thunders[1].STRIKE_BLUE_COLOR_RATIO = 230;
  thunders[1].STRIKE_GREEN_COLOR_RATIO = 10;
  thunders[1].STRIKE_LIGHT_RATIO = 50;
  thunders[1].STRIKE_LIGHT_BASE = 5;
  thunders[1].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[1].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[1].STRIKE_GREEN_RANDOM_RATIO = 5;
  thunders[1].STRIKE_BLUE_RANDOM_RATIO = 5;
}

void blueThunderEffectSettings() {
  thunders[0].STRIKE_RED_COLOR_RATIO = 10;
  thunders[0].STRIKE_BLUE_COLOR_RATIO = 230;
  thunders[0].STRIKE_GREEN_COLOR_RATIO = 10;
  thunders[0].STRIKE_LIGHT_RATIO = 0;
  thunders[0].STRIKE_LIGHT_BASE = 0;
  thunders[0].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[0].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[0].STRIKE_GREEN_RANDOM_RATIO = 5;

  thunders[1].STRIKE_RED_COLOR_RATIO = 10;
  thunders[1].STRIKE_BLUE_COLOR_RATIO = 230;
  thunders[1].STRIKE_GREEN_COLOR_RATIO = 10;
  thunders[1].STRIKE_LIGHT_RATIO = 0;
  thunders[1].STRIKE_LIGHT_BASE = 0;
  thunders[1].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[1].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[1].STRIKE_GREEN_RANDOM_RATIO = 5;
}

void redAndGreenThunderEffectSettings() {
  thunders[0].STRIKE_RED_COLOR_RATIO = 250;
  thunders[0].STRIKE_BLUE_COLOR_RATIO = 0;
  thunders[0].STRIKE_GREEN_COLOR_RATIO = 250;
  thunders[0].STRIKE_LIGHT_RATIO = 0;
  thunders[0].STRIKE_LIGHT_BASE = 0;
  thunders[0].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[0].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[0].STRIKE_GREEN_RANDOM_RATIO = 5;

  thunders[1].STRIKE_RED_COLOR_RATIO = 250;
  thunders[1].STRIKE_BLUE_COLOR_RATIO = 0;
  thunders[1].STRIKE_GREEN_COLOR_RATIO = 250;
  thunders[1].STRIKE_LIGHT_RATIO = 0;
  thunders[1].STRIKE_LIGHT_BASE = 0;
  thunders[1].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[1].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[1].STRIKE_GREEN_RANDOM_RATIO = 5;
}

void blueAndGreenThunderEffectSettings() {
  thunders[0].STRIKE_RED_COLOR_RATIO = 0;
  thunders[0].STRIKE_BLUE_COLOR_RATIO = 250;
  thunders[0].STRIKE_GREEN_COLOR_RATIO = 250;
  thunders[0].STRIKE_LIGHT_RATIO = 0;
  thunders[0].STRIKE_LIGHT_BASE = 0;
  thunders[0].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[0].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[0].STRIKE_GREEN_RANDOM_RATIO = 5;

  thunders[1].STRIKE_RED_COLOR_RATIO = 0;
  thunders[1].STRIKE_BLUE_COLOR_RATIO = 250;
  thunders[1].STRIKE_GREEN_COLOR_RATIO = 250;
  thunders[1].STRIKE_LIGHT_RATIO = 0;
  thunders[1].STRIKE_LIGHT_BASE = 0;
  thunders[1].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[1].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[1].STRIKE_GREEN_RANDOM_RATIO = 5;
}

void blueAndRedThunderEffectSettings() {
  thunders[0].STRIKE_RED_COLOR_RATIO = 250;
  thunders[0].STRIKE_BLUE_COLOR_RATIO = 250;
  thunders[0].STRIKE_GREEN_COLOR_RATIO = 0;
  thunders[0].STRIKE_LIGHT_RATIO = 0;
  thunders[0].STRIKE_LIGHT_BASE = 0;
  thunders[0].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[0].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[0].STRIKE_GREEN_RANDOM_RATIO = 5;

  thunders[1].STRIKE_RED_COLOR_RATIO = 250;
  thunders[1].STRIKE_BLUE_COLOR_RATIO = 250;
  thunders[1].STRIKE_GREEN_COLOR_RATIO = 0;
  thunders[1].STRIKE_LIGHT_RATIO = 0;
  thunders[1].STRIKE_LIGHT_BASE = 0;
  thunders[1].STRIKE_LIGHT_RANDOM_RATIO = 5;
  thunders[1].STRIKE_RED_RANDOM_RATIO = 5;
  thunders[1].STRIKE_GREEN_RANDOM_RATIO = 5;
}

uint16_t thunderEffect0(void) {
  static int stripNumber = 0;
  static int step = 0;
  WS2812FX::Segment* seg = strips[stripNumber].getSegment();

  thunderEffect(seg, stripNumber, step);
  step++;
  if (step > 1000) step = 0;
 
  return (seg->speed / 1000); // return the delay until the next animation step (in msec)
}

uint16_t thunderEffect1(void) {
  static int stripNumber = 1;
  static int step = 0;
  WS2812FX::Segment* seg = strips[stripNumber].getSegment();

  thunderEffect(seg, stripNumber, step);
  step++;
  if (step > 1000) step = 0;
 
  return (seg->speed / 1000); // return the delay until the next animation step (in msec)
}


uint16_t thunderEffect(WS2812FX::Segment* seg, int stripNumber, int step) {

  // EVERY STEP
  if (thunders[stripNumber].flashesRemaining > 0) {
      int shouldFlash = random (0, thunders[stripNumber].FLASHES_OUT_OF);

      if (shouldFlash == 0) {
        int flashAmplitude = thunders[stripNumber].flashesSteps;

        if (thunders[stripNumber].flashesRemaining > 1) {
          //flashAmplitude = flashesSteps - random(min(0, flashesRemaining - 2), (flashesRemaining - 1));
          flashAmplitude = thunders[stripNumber].flashesSteps - thunders[stripNumber].flashesRemaining + 1;
        }

        int endOfFlash = floor((seg->stop - seg->start) * flashAmplitude / thunders[stripNumber].flashesSteps);

        int flashIntensity = thunders[stripNumber].STRIKE_LIGHT_BASE + floor( thunders[stripNumber].STRIKE_LIGHT_RATIO * (thunders[stripNumber].flashesSteps - thunders[stripNumber].flashesRemaining) / thunders[stripNumber].flashesSteps);
     
         for (int thunderPixel = seg->start; thunderPixel < seg->start + endOfFlash ; thunderPixel++) {
            int pixelIntensity = random(0, thunders[stripNumber].STRIKE_LIGHT_RANDOM_RATIO);
            int pixelRedIntensity = random(0, thunders[stripNumber].STRIKE_RED_RANDOM_RATIO);
            int pixelGreenIntensity = random(0, thunders[stripNumber].STRIKE_GREEN_RANDOM_RATIO);
            int pixelBlueIntensity = random(0, thunders[stripNumber].STRIKE_BLUE_RANDOM_RATIO);
          
            strips[stripNumber].setPixelColor(thunderPixel,
              flashIntensity + thunders[stripNumber].strikeRedRatio + pixelRedIntensity,  
              flashIntensity + thunders[stripNumber].strikeGreenRatio + pixelGreenIntensity, 
              flashIntensity + thunders[stripNumber].strikeBlueRatio + pixelBlueIntensity,  
              flashIntensity + pixelIntensity);
         }

         thunders[stripNumber].flashesRemaining--;

         if (thunders[stripNumber].flashesRemaining == 0) {
            thunders[stripNumber].removesRemaining = random(thunders[stripNumber].MIN_REMOVE_NUMBER, thunders[stripNumber].MAX_REMOVE_NUMBER);
            thunders[stripNumber].removesSteps = thunders[stripNumber].removesRemaining;
         }
       }
    }


    if (thunders[stripNumber].removesRemaining >= 0) {
      for (int thunderPixel = seg->start; thunderPixel < seg->stop  ; thunderPixel++) {
         int removeIntensity = floor( (thunders[stripNumber].STRIKE_LIGHT_BASE + thunders[stripNumber].STRIKE_LIGHT_RATIO) * thunders[stripNumber].removesRemaining / thunders[stripNumber].removesSteps);
         int removeRedIntensity = floor( thunders[stripNumber].strikeRedRatio * thunders[stripNumber].removesRemaining / thunders[stripNumber].removesSteps);
         int removeBlueIntensity = floor( thunders[stripNumber].strikeBlueRatio * thunders[stripNumber].removesRemaining / thunders[stripNumber].removesSteps);
         int removeGreenIntensity = floor( thunders[stripNumber].strikeGreenRatio * thunders[stripNumber].removesRemaining / thunders[stripNumber].removesSteps);
         strips[stripNumber].setPixelColor(thunderPixel, removeRedIntensity, removeGreenIntensity, removeBlueIntensity, removeIntensity);
      }

      thunders[stripNumber].removesRemaining--;
    }

   // EVERY 20 STEPS
   if ((step % 20) == 0) {

       // initiate thunder
       int shouldThunderStrike = random(5);

       // Si on a fini les éclairs précédents
       if (shouldThunderStrike == 0 && thunders[stripNumber].removesRemaining == -1) {
            thunders[stripNumber].flashesRemaining = random(thunders[stripNumber].MIN_FLASHES_NUMBER, thunders[stripNumber].MAX_FLASHES_NUMBER);
            thunders[stripNumber].flashesSteps = thunders[stripNumber].flashesRemaining;

            thunders[stripNumber].strikeRedRatio = random(0, thunders[stripNumber].STRIKE_RED_COLOR_RATIO);
            thunders[stripNumber].strikeBlueRatio = random(0, thunders[stripNumber].STRIKE_BLUE_COLOR_RATIO);
            thunders[stripNumber].strikeGreenRatio = random(0, thunders[stripNumber].STRIKE_GREEN_COLOR_RATIO);
       }
    } 

  step++;
  if (step > 1000) step = 0;
 
  return (seg->speed / 1000); // return the delay until the next animation step (in msec)
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

