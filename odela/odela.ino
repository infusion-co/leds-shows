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

#define GOLD      (uint32_t) 0xFFAF00
#define DARK_ORANGE (uint32_t) 0xFF6500
#define BORDEAUX (uint32_t) 0xCD0101
#define DARK_BLUE (uint32_t) 0x1F19AF
#define LIGHT_BLUE (uint32_t) 0x00BAFF
#define DEEP_PINK (uint32_t) 0xDB016D

// === odela params
#define RIGHT_1_START 19
#define RIGHT_2_START 49
#define RIGHT_3_START 79
#define RIGHT_4_START 109
#define RIGHT_5_START 139


#define LEFT_1_START 17
#define LEFT_2_START 47
#define LEFT_3_START 77
#define LEFT_4_START 107
#define LEFT_5_START 137

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

uint8_t options5;
uint32_t colors5[3];
int speed5;
int mode5;


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

  
  // ==== PHASE 1 FIRE DAWN
  
  unsigned long showSteps = timeMinutes;


  // COMET BIRTH
  if (showSteps == 0) {
    options1 = FADE_XXSLOW;
    options2 = FADE_MEDIUM + REVERSE;
    options3 = FADE_FAST;
    options4 = FADE_FAST + REVERSE;
    options5 = FADE_MEDIUM;

    colors1[0] = YELLOW;
    colors1[1] = BLUE;
    colors1[2] = BLACK;

    colors2[0] = BLUE;
    colors2[1] = RED;
    colors2[2] = BLACK;

    colors3[0] = YELLOW;
    colors3[1] = RED;
    colors3[2] = BLACK;

    colors4[0] = BLUE; // dark orange
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
  
  // FIRE FLICKER
  if (showSteps == 1) {
    // 
    options1 = FADE_XXSLOW;
    options2 = FADE_SLOW + REVERSE;
    options3 = FADE_XSLOW;
    options4 = FADE_SLOW + REVERSE;
    options5 = FADE_MEDIUM;

    colors1[0] = RED;
    colors1[1] = BLACK;
    colors1[2] = BLACK;

    colors2[0] = GOLD;
    colors2[1] = BORDEAUX;
    colors2[2] = BLACK;

    colors3[0] = GOLD;
    colors3[1] = DEEP_PINK;
    colors3[2] = BLACK;

    colors4[0] = DARK_ORANGE; // dark orange
    colors4[1] = RED;
    colors4[2] = BLACK;

    colors5[0] = RED;
    colors5[1] = BLACK;
    colors5[2] = BLACK;

    speed1 = 700;
    speed2 = 900;
    speed3 = 1400;
    speed4 = 1100;
    speed5 = 700;

    mode1 = FX_MODE_FIRE_FLICKER_INTENSE;
    mode2 = FX_MODE_FIRE_FLICKER_INTENSE;
    mode3 = FX_MODE_FIRE_FLICKER_INTENSE;
    mode4 = FX_MODE_FIRE_FLICKER_INTENSE;
    mode5 = FX_MODE_FIRE_FLICKER_INTENSE;

    // more glacial less frequency 
    // too only yellow les 2 en haut
    setRModes();
  }

  // FIRE THEATER CHASE
  if (showSteps == 2) {

    options1 = FADE_XSLOW;
    options2 = FADE_MEDIUM + REVERSE;
    options3 = FADE_FAST;
    options4 = FADE_FAST + REVERSE;
    options5 = FADE_XSLOW;

    colors1[0] = RED;
    colors1[1] = DARK_ORANGE;
    colors1[2] = GOLD;

    colors2[0] = LIGHT_BLUE;
    colors2[1] = PURPLE;
    colors2[2] = BLACK;

    colors3[0] = DARK_BLUE;
    colors3[1] = DEEP_PINK;
    colors3[2] = BLACK;

    colors4[0] = PINK; // dark orange
    colors4[1] = CYAN;
    colors4[2] = PINK;

    colors5[0] = RED;
    colors5[1] = DARK_ORANGE;
    colors5[2] = GOLD;

    speed1 = 3000;
    speed2 = 2500;
    speed3 = 1500;
    speed4 = 2000;
    speed5 = 3000;

    mode1 = FX_MODE_THEATER_CHASE;
    mode2 = FX_MODE_THEATER_CHASE;
    mode3 = FX_MODE_THEATER_CHASE;
    mode4 = FX_MODE_THEATER_CHASE;
    mode5 = FX_MODE_THEATER_CHASE;

    // on voit rien sur le bleu xxx
    
    setRModes();
  }

  // FIRE TWINKLE FADE -- keeps previous colors and makes small dots fade
  if (showSteps == 3) {

    options1 = FADE_GLACIAL;
    options2 = FADE_XXSLOW + REVERSE;
    options3 = FADE_SLOW;
    options4 = FADE_GLACIAL + REVERSE;
    options5 = FADE_GLACIAL;

    colors1[0] = GOLD;
    colors1[1] = WHITE;
    colors1[2] = BLACK;

    colors2[0] = DEEP_PINK;
    colors2[1] = LIGHT_BLUE;
    colors2[2] = BLACK;

    colors3[0] = CYAN;
    colors3[1] = DARK_BLUE;
    colors3[2] = BLACK;

    colors4[0] = DEEP_PINK; 
    colors4[1] = CYAN;
    colors4[2] = BLACK;

    colors5[0] = GOLD;
    colors5[1] = WHITE;
    colors5[2] = BLACK;

    speed1 = 10;
    speed2 = 100;
    speed3 = 1000;
    speed4 = 100;
    speed5 = 10;

    mode1 = FX_MODE_TWINKLE_FADE;
    mode2 = FX_MODE_TWINKLE_FADE;
    mode3 = FX_MODE_TWINKLE_FADE;
    mode4 = FX_MODE_TWINKLE_FADE;
    mode5 = FX_MODE_TWINKLE_FADE;

    // on voit rien sur le bleu xxx
    
    setRModes();
  }

  // CIRCUS COMBUSTUS BLACK WHITE RED circus show + STROBING RED WHITE CLOUD
  if (showSteps == 4) {
    stepMillis = 100;
    step = (int) floor(timeMillis / stepMillis)  % 3;
    next = (timeMillis != lastTimeMillis);
    
    int flashMode = FX_MODE_STROBE;
    
    uint32_t flashCols2[] = {WHITE, RED, BLACK};
    uint32_t flashCols3[] = {WHITE, RED, BLACK};
    uint32_t flashCols4[] = {WHITE, RED, BLACK};
    int speed = 70;

    if (next) {
      if (step == 0) {

        options2 = FADE_MEDIUM + REVERSE;
        options3 = FADE_SLOW;
        options4 = FADE_FAST + REVERSE;

        colors2[0] = flashCols2[0];
        colors2[1] = flashCols2[1];
        colors2[2] = flashCols2[2];

        colors3[0] = BLACK;
        colors3[1] = BLACK;
        colors3[2] = BLACK;

        colors4[0] = BLACK; 
        colors4[1] = BLACK;
        colors4[2] = BLACK;

        speed2 = speed;
        speed3 = speed;
        speed4 = speed;

        mode2 = flashMode;
        mode3 = FX_MODE_STATIC;
        mode4 = FX_MODE_STATIC;
      }


      if (step == 1) {
        options2 = FADE_MEDIUM + REVERSE;
        options3 = FADE_SLOW;
        options4 = FADE_FAST + REVERSE;

        colors2[0] = BLACK;
        colors2[1] = BLACK;
        colors2[2] = BLACK;

        colors3[0] = flashCols3[0];
        colors3[1] = flashCols3[1];
        colors3[2] = flashCols3[2];

        colors4[0] = BLACK; 
        colors4[1] = BLACK;
        colors4[2] = BLACK;

        speed2 = speed;
        speed3 = speed;
        speed4 = speed;

        mode2 = FX_MODE_STATIC;
        mode3 = flashMode;
        mode4 = FX_MODE_STATIC;
      }


      if (step == 2) {
        options2 = FADE_MEDIUM + REVERSE;
        options3 = FADE_SLOW;
        options4 = FADE_FAST + REVERSE;

        colors2[0] = BLACK;
        colors2[1] = BLACK;
        colors2[2] = BLACK;

        colors3[0] = BLACK;
        colors3[1] = BLACK;
        colors3[2] = BLACK;

        colors4[0] = flashCols4[0]; 
        colors4[1] = flashCols4[1];
        colors4[2] = flashCols4[2];

        speed2 = speed;
        speed3 = speed;
        speed4 = speed;

        mode2 = FX_MODE_STATIC;
        mode3 = FX_MODE_STATIC;
        mode4 = flashMode;
      }
    }

    options1 = FADE_XSLOW;
    options5 = FADE_XSLOW;

    colors1[0] = DARK_ORANGE;
    colors1[1] = RED;
    colors1[2] = BLACK;


    colors5[0] = DARK_ORANGE;
    colors5[1] = RED;
    colors5[2] = BLACK;

    speed1 = 150;
    
    speed5 = 150;

    mode1 = FX_MODE_CIRCUS_COMBUSTUS;
    
    mode5 = FX_MODE_CIRCUS_COMBUSTUS;

    
    setRModes();
  }


  // ==== PHASE 2 SUN BRIGHT DAY
  // CLICKING SUNS + RUNNING DAWN
  if (showSteps == 5) {
    stepMillis = 100;
    step = (int) floor(timeMillis / stepMillis)  % 3;
    next = (timeMillis != lastTimeMillis);
    
    int flashMode = FX_MODE_STROBE;
    
    uint32_t flashCols2[] = {YELLOW, ORANGE, BLACK};
    uint32_t flashCols3[] = {GOLD, DARK_ORANGE, BLACK};
    uint32_t flashCols4[] = {ORANGE, RED, BLACK};
    int speed = 50;

    if (next) {
      if (step == 0) {

        options2 = FADE_MEDIUM + REVERSE;
        options3 = FADE_SLOW;
        options4 = FADE_FAST + REVERSE;

        colors2[0] = flashCols2[0];
        colors2[1] = flashCols2[1];
        colors2[2] = flashCols2[2];

        colors3[0] = BLACK;
        colors3[1] = BLACK;
        colors3[2] = BLACK;

        colors4[0] = BLACK; 
        colors4[1] = BLACK;
        colors4[2] = BLACK;

        speed2 = speed;
        speed3 = speed;
        speed4 = speed;

        mode2 = flashMode;
        mode3 = FX_MODE_STATIC;
        mode4 = FX_MODE_STATIC;
      }


      if (step == 1) {
        options2 = FADE_MEDIUM + REVERSE;
        options3 = FADE_SLOW;
        options4 = FADE_FAST + REVERSE;

        colors2[0] = BLACK;
        colors2[1] = BLACK;
        colors2[2] = BLACK;

        colors3[0] = flashCols3[0];
        colors3[1] = flashCols3[1];
        colors3[2] = flashCols3[2];

        colors4[0] = BLACK; 
        colors4[1] = BLACK;
        colors4[2] = BLACK;

        speed2 = speed;
        speed3 = speed;
        speed4 = speed;

        mode2 = FX_MODE_STATIC;
        mode3 = flashMode;
        mode4 = FX_MODE_STATIC;
      }


      if (step == 2) {
        options2 = FADE_MEDIUM + REVERSE;
        options3 = FADE_SLOW;
        options4 = FADE_FAST + REVERSE;

        colors2[0] = BLACK;
        colors2[1] = BLACK;
        colors2[2] = BLACK;

        colors3[0] = BLACK;
        colors3[1] = BLACK;
        colors3[2] = BLACK;

        colors4[0] = flashCols4[0]; 
        colors4[1] = flashCols4[1];
        colors4[2] = flashCols4[2];

        speed2 = speed;
        speed3 = speed;
        speed4 = speed;

        mode2 = FX_MODE_STATIC;
        mode3 = FX_MODE_STATIC;
        mode4 = flashMode;
      }
    }

    options1 = FADE_XXSLOW;
    options5 = FADE_XXSLOW;

    colors1[0] = DARK_ORANGE;
    colors1[1] = RED;
    colors1[2] = YELLOW;


    colors5[0] = DARK_ORANGE;
    colors5[1] = RED;
    colors5[2] = YELLOW;

    speed1 = 3000;
    
    speed5 = 3000;

    mode1 = FX_MODE_RUNNING_RED_BLUE;
    
    mode5 = FX_MODE_RUNNING_RED_BLUE;

    // ce strobre est bizarre
    
    setRModes();
  }

  // BREATHING SUNS AND BREATHING SKY
  if (showSteps == 6) {
    

    options1 = FADE_XSLOW;
    options2 = FADE_MEDIUM + REVERSE;
    options3 = FADE_SLOW;
    options4 = FADE_FAST + REVERSE;
    options5 = FADE_XSLOW;

    colors1[0] = DARK_ORANGE;
    colors1[1] = BLACK;
    colors1[2] = BLACK;

    colors2[0] = (uint32_t) 0x00bfff;
    colors2[1] = BLUE;
    colors2[2] = BLACK;

    colors3[0] = CYAN;
    colors3[1] = BLUE;
    colors3[2] = BLACK;

    colors4[0] = LIGHT_BLUE; 
    colors4[1] = DARK_BLUE;
    colors4[2] = BLACK;

    colors5[0] = DARK_ORANGE;
    colors5[1] = BLACK;
    colors5[2] = BLACK;

    speed1 = 1300;
    speed2 = 300;
    speed3 = 600;
    speed4 = 3000;
    speed5 = 1300;

    mode1 = FX_MODE_BREATH;
    mode2 = FX_MODE_BREATH;
    mode3 = FX_MODE_BREATH;
    mode4 = FX_MODE_BREATH;
    mode5 = FX_MODE_BREATH;

    
    setRModes();
  }

  // BREATHING SUNS + RAINBOWS CHASE
  if (showSteps == 7) {
    

    options1 = FADE_XSLOW;
    options2 = FADE_MEDIUM + REVERSE;
    options3 = FADE_SLOW;
    options4 = FADE_FAST + REVERSE;
    options5 = FADE_XSLOW;

    colors1[0] = GOLD;
    colors1[1] = BLACK;
    colors1[2] = BLACK;

    colors2[0] = (uint32_t) 0x00bfff;
    colors2[1] = BLUE;
    colors2[2] = BLACK;

    colors3[0] = CYAN;
    colors3[1] = BLUE;
    colors3[2] = BLACK;

    colors4[0] = LIGHT_BLUE; 
    colors4[1] = DARK_BLUE;
    colors4[2] = BLACK;

    colors5[0] = GOLD;
    colors5[1] = BLACK;
    colors5[2] = BLACK;

    speed1 = 2000;
    speed2 = 300;
    speed3 = 1000;
    speed4 = 3000;
    speed5 = 2000;

    mode1 = FX_MODE_BREATH;
    mode2 = FX_MODE_CHASE_RAINBOW;
    mode3 = FX_MODE_CHASE_RAINBOW;
    mode4 = FX_MODE_CHASE_RAINBOW;
    mode5 = FX_MODE_BREATH;

    // breathing yellow moyen : un peu plus rouge ? xxx
    
    setRModes();
  }

  // BREATHING SUNS + RAINBOWS SLOW
  if (showSteps == 8) {
    options1 = FADE_XSLOW;
    options2 = FADE_MEDIUM + REVERSE;
    options3 = FADE_SLOW;
    options4 = FADE_FAST + REVERSE;
    options5 = FADE_XSLOW;

    colors1[0] = GOLD;
    colors1[1] = BLACK;
    colors1[2] = BLACK;

    colors2[0] = GOLD;
    colors2[1] = BLACK;
    colors2[2] = BLACK;

    colors3[0] = YELLOW;
    colors3[1] = BLACK;
    colors3[2] = BLACK;

    colors4[0] = ORANGE; 
    colors4[1] = BLACK;
    colors4[2] = BLACK;

    colors5[0] = GOLD;
    colors5[1] = BLACK;
    colors5[2] = BLACK;

    speed1 = 300;
    speed2 = 300;
    speed3 = 1000;
    speed4 = 3000;
    speed5 = 300;

    mode1 = FX_MODE_RAINBOW_CYCLE;
    mode2 = FX_MODE_BREATH;
    mode3 = FX_MODE_BREATH;
    mode4 = FX_MODE_BREATH;
    mode5 = FX_MODE_RAINBOW_CYCLE;
    

    setRModes();
  }


  // FIRE WHITE CLOUD + REGULAR THUNDER
  if (showSteps == 9) {

    options1 = FADE_XSLOW;
    options2 = FADE_GLACIAL + REVERSE;
    options3 = FADE_SLOW;
    options4 = FADE_MEDIUM + REVERSE;
    options5 = FADE_XSLOW;

    colors1[0] = CYAN;
    colors1[1] = BLACK;
    colors1[2] = BLACK;

    colors2[0] = PURPLE;
    // colors2[1] = (uint32_t) 0xBB3E03; //ocre
    colors2[1] = (uint32_t) 0x722501; //darker ocre
    colors2[2] = BLACK;

    colors3[0] = DEEP_PINK;
    // colors3[1] = (uint32_t) 0x03BBBB; //dark turquoise
    colors3[1] = (uint32_t) 0x057D7D; //darker turquoise
    colors3[2] = BLACK;

    colors4[0] = (uint32_t) 0x1E00FF; // better blue
    // colors4[1] = (uint32_t) 0xFF0051; //some pink
    colors4[1] = (uint32_t) 0x93002F; //some pink darker
    colors4[2] = BLACK;

    colors5[0] = CYAN;
    colors5[1] = BLACK;
    colors5[2] = BLACK;

    speed1 = 1000;
    speed2 = 1500;
    speed3 = 500;
    speed4 = 30;
    speed5 = 1000;

    mode1 = FX_MODE_FIRE_FLICKER_INTENSE;
    mode2 = FX_MODE_COMET;
    mode3 = FX_MODE_COMET;
    mode4 = FX_MODE_COMET;
    mode5 = FX_MODE_FIRE_FLICKER_INTENSE;

    // Manque d'un background pour les cometes
    
    setRModes();
  }

  //FIRE WHITE CLOUD + BLUE COMETS
  if (showSteps == -1) {
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
  if (showSteps == -1) {
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
  if (showSteps == -1) {
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

