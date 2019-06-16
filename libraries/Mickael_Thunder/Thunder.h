/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Thunder_h
#define Thunder_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class Morse
{
  public:
    Thunder(Adafruit_NeoPixel strip);
    void play(int step);
  private:
    Adafruit_NeoPixel _strip;
};

#endif
