#include <Adafruit_NeoPixel.h>
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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, PIN2, NEO_RGBW + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip2.begin();
  strip2.show();
}

// *** REPLACE FROM HERE ***
void loop() { 
  // ---> here we call the effect function <---
  // VERT ROUGE BLEU TOUT EST INVERSE trop chelou
   // RGBLoop();

   FadeInOut(0x00, 0xff, 0x00); // red
   FadeInOut(0x77, 0xff, 0x00); // orange 
   FadeInOut(0xff, 0xff, 0x00); // yellow 255 255 0
   
   FadeInOut(0x00, 0x00, 0xff); // blue
   FadeInOut(0x00 ,  0x77, 0xa5 ); // violet  119 0 165
   FadeInOut(0x00, 0xff,  0xff); // pink = 255 0 225
   FadeInOut(0x00, 0xff, 0x77); // birght pink

   FadeInOut(0xff, 0x00, 0x00); // green
   FadeInOut(0xff, 0x00, 0xe5); // turquoise = 0 255 229
   FadeInOut(0x8d, 0x00, 0xa5); // emerald = 8 141 165

   FadeInOut(0xff, 0xff, 0xff); // white 
 // 165 = 0xa5
 // 229 = 0xe5
 // 119 = 0x77
  // Slower:
 Strobe(0xff, 0x77, 0x00, 10, 100, 1000);// green
 Strobe(0x77, 0xff, 0x00, 10, 70, 1000); //orange
 Strobe(0x00, 0xff, 0x77, 10, 70, 1000); //pink = 255 0 225
  // Fast:
 Strobe(0xff, 0xff, 0xff, 10, 50, 1000);

  // Fixed:
//   HalloweenEyes(0xff, 0x00, 0x00, 1,4, true, 10, 80, 3000);
  // or Random:
//   HalloweenEyes(0xff, 0x00, 0x00, 
//                1, 4, 
//                true, random(5,50), random(50,150), 
//                random(1000, 10000));

   CylonBounce(0x00, 0xff, 0x00, 4, 10, 50);
   CylonBounce(0x77, 0xff, 0x00, 4, 10, 50);
   CylonBounce(0xff, 0xff, 0x00, 4, 10, 50);
   
   CylonBounce(0x00, 0x00, 0xff, 4, 10, 50);
   CylonBounce(0x00 ,  0x77, 0xa5, 4, 10, 50);
   CylonBounce(0x00, 0xff,  0xff, 4, 10, 50);
   CylonBounce(0x00, 0xff, 0x77, 4, 10, 50);

   CylonBounce(0xff, 0x00, 0x00, 4, 10, 50);
   CylonBounce(0xff, 0x00, 0xe5, 4, 10, 50);
   CylonBounce(0x8d, 0x00, 0xa5, 4, 10, 50);

   NewKITT(0x00, 0xff, 0x00, 8, 10, 50);
   NewKITT(0x77, 0xff, 0x00, 8, 10, 50);
   NewKITT(0xff, 0xff, 0x00, 8, 10, 50);

   NewKITT(0x00, 0x00, 0xff, 8, 10, 50);
   NewKITT(0x00 ,  0x77, 0xa5, 8, 10, 50);
   NewKITT(0x00, 0xff,  0xff, 8, 10, 50);
   NewKITT(0x00, 0xff, 0x77, 8, 10, 50);

   NewKITT(0xff, 0x00, 0x00, 8, 10, 50);
    NewKITT(0xff, 0x00, 0xe5, 8, 10, 50);
    NewKITT(0x8d, 0x00, 0xa5, 8, 10, 50);

   Twinkle(0x00, 0xff, 0x00, 10, 100, false);
   Twinkle(0x77, 0xff, 0x00, 10, 100, false);
   Twinkle(0xff, 0xff, 0x00, 10, 100, false);

   Twinkle(0x00, 0x00, 0xff, 10, 100, false);
   Twinkle(0x00 ,  0x77, 0xa5, 10, 100, false);
   Twinkle(0x00, 0xff,  0xff, 10, 100, false);
   Twinkle(0x00, 0xff, 0x77, 10, 100, false);

   Twinkle(0xff, 0x00, 0x00, 10, 100, false);
   Twinkle(0xff, 0x00, 0xe5, 10, 100, false);
   Twinkle(0x8d, 0x00, 0xa5, 10, 100, false);

   TwinkleRandom(20, 100, false);
   TwinkleRandom(40, 80, false);
   TwinkleRandom(60, 90, false);

   Sparkle(0x00, 0xff, 0x00, 0);
   Sparkle(0x77, 0xff, 0x00, 0);
   Sparkle(0xff, 0xff, 0x00, 0);

   Sparkle(0x00, 0x00, 0xff, 0);
   Sparkle(0x00 ,  0x77, 0xa5, 0);
   Sparkle(0x00, 0xff,  0xff, 0);
   Sparkle(0x00, 0xff, 0x77, 0);

   Sparkle(0xff, 0x00, 0x00, 0);
   Sparkle(0xff, 0x00, 0xe5, 0);
   Sparkle(0x8d, 0x00, 0xa5, 0);

   SnowSparkle(0x10, 0x10, 0x10, 20, random(100,1000));
   SnowSparkle(0x10, 0x10, 0x10, 20, random(100,1000));
   SnowSparkle(0x10, 0x10, 0x10, 20, random(100,1000));
   SnowSparkle(0x10, 0x10, 0x10, 20, random(100,1000));
   SnowSparkle(0x10, 0x10, 0x10, 20, random(100,1000));
   SnowSparkle(0x10, 0x10, 0x10, 20, random(100,1000));

   SnowSparkle(0x00, 0xff, 0x00, 20, random(100,1000));
   SnowSparkle(0x77, 0xff, 0x00, 20, random(100,1000));
   SnowSparkle(0xff, 0xff, 0x00, 20, random(100,1000));

   SnowSparkle(0x00, 0x00, 0xff, 20, random(100,1000));
   SnowSparkle(0x00 ,  0x77, 0xa5, 20, random(100,1000));
   SnowSparkle(0x00, 0xff,  0xff, 20, random(100,1000));
   SnowSparkle(0x00, 0xff, 0x77, 20, random(100,1000));

   SnowSparkle(0xff, 0x00, 0x00, 20, random(100,1000));
   SnowSparkle(0xff, 0x00, 0xe5, 20, random(100,1000));
   SnowSparkle(0x8d, 0x00, 0xa5, 20, random(100,1000));

   RunningLights(0x00, 0xff, 0x00, 50);
   RunningLights(0x77, 0xff, 0x00, 50);
   RunningLights(0xff, 0xff, 0x00, 50);

   RunningLights(0x00, 0x00, 0xff, 50);
   RunningLights(0x00 ,  0x77, 0xa5, 50);
   RunningLights(0x00, 0xff,  0xff, 50);
   RunningLights(0x00, 0xff, 0x77, 50);

   RunningLights(0xff, 0x00, 0x00, 50);
   RunningLights(0xff, 0x00, 0xe5, 50);
   RunningLights(0x8d, 0x00, 0xa5, 50);

   colorWipe(0x00, 0xff, 0x00, 50);
   colorWipe(0x77, 0xff, 0x00, 50);
   colorWipe(0xff, 0xff, 0x00, 50);

   colorWipe(0x00, 0x00, 0xff, 50);
   colorWipe(0x00 ,  0x77, 0xa5, 50);
   colorWipe(0x00, 0xff,  0xff, 50);
   colorWipe(0x00, 0xff, 0x77, 50);

   colorWipe(0xff, 0x00, 0x00, 50);
   colorWipe(0xff, 0x00, 0xe5, 50);
   colorWipe(0x8d, 0x00, 0xa5, 50);

   rainbowCycle(20);
   rainbowCycle(50);


   theaterChase(0x00, 0xff, 0x00,25);
   theaterChase(0x77, 0xff, 0x00,25);
   theaterChase(0xff, 0xff, 0x00,25);

   theaterChase(0x00, 0x00, 0xff,25);
   theaterChase(0x00 ,  0x77, 0xa5,25);
   theaterChase(0x00, 0xff,  0xff,25);
   theaterChase(0x00, 0xff, 0x77,25);

   theaterChase(0xff, 0x00, 0x00,25);
   theaterChase(0xff, 0x00, 0xe5,25);
   theaterChase(0x8d, 0x00, 0xa5,25);

   theaterChaseRainbow(50);
  
for(int j = 0; j < 100; j++ ) { 
   Fire(10,150,60);
}

   // BouncingBalls(0xff,0,0, 3);

   // byte colors[3][3] = { {0xff, 0,0}, 
                        // {0xff, 0xff, 0xff}, 
                       // {0   , 0   , 0xff} };
   // BouncingColoredBalls(3, colors);
}

// ---> here we define the effect function <---
// *** REPLACE TO HERE ***

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
   strip2.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
   strip2.setPixelColor(Pixel, strip2.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

void RGBLoop(){
  for(int j = 0; j < 3; j++ ) { 
    // Fade IN
    for(int k = 0; k < 256; k++) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

void FadeInOut(byte red, byte green, byte blue){
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAll(0,0,0);
    showStrip();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}

void HalloweenEyes(byte red, byte green, byte blue, 
                   int EyeWidth, int EyeSpace, 
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause){
  randomSeed(analogRead(0));
  
  int i;
  int StartPoint  = random( 0, NUM_LEDS - (2*EyeWidth) - EyeSpace );
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;
  
  for(i = 0; i < EyeWidth; i++) {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
  }
  
  showStrip();
  
  if(Fade==true) {
    float r, g, b;
  
    for(int j = Steps; j >= 0; j--) {
      r = j*(red/Steps);
      g = j*(green/Steps);
      b = j*(blue/Steps);
      
      for(i = 0; i < EyeWidth; i++) {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
      }
      
      showStrip();
      delay(FadeDelay);
    }
  }
  
  setAll(0,0,0); // Set all black
  
  delay(EndPause);
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}

void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i =((NUM_LEDS-EyeSize)/2); i>=0; i--) {
    setAll(0,0,0);
    
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue); 
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
    
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i<=((NUM_LEDS-EyeSize)/2); i++) {
    setAll(0,0,0);
    
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue); 
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
    
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),red,green,blue);
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}

void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red,green,blue);
  
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,0xff,0xff,0xff);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      showStrip();
      delay(WaveDelay);
  }
}

void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      setPixel(i, red, green, blue);
      showStrip();
      delay(SpeedDelay);
  }
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}

void theaterChase(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, red, green, blue);    //turn every third pixel on
      }
      showStrip();
     
      delay(SpeedDelay);
     
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, 0,0,0);        //turn every third pixel off
      }
    }
  }
}

void theaterChaseRainbow(int SpeedDelay) {
  byte *c;
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < NUM_LEDS; i=i+3) {
          c = Wheel( (i+j) % 255);
          setPixel(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        showStrip();
       
        delay(SpeedDelay);
       
        for (int i=0; i < NUM_LEDS; i=i+3) {
          setPixel(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}

void BouncingBalls(byte red, byte green, byte blue, int BallCount) {
  float Gravity = -9.81;
  int StartHeight = 1;
  
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  
  for (int i = 0 ; i < BallCount ; i++) {   
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0; 
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2); 
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
  
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
  
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }
  
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],red,green,blue);
    }
    
    showStrip();
    setAll(0,0,0);
  }
}

void BouncingColoredBalls(int BallCount, byte colors[][3]) {
  float Gravity = -9.81;
  int StartHeight = 1;
  
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  
  for (int i = 0 ; i < BallCount ; i++) {   
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0; 
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2); 
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
  
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
  
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }
  
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],colors[i][0],colors[i][1],colors[i][2]);
    }
    
    showStrip();
    setAll(0,0,0);
  }
}

