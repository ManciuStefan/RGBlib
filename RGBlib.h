/*
  RGBlib.h - Library for controlling an RGB led or strip.
  Created by Stefan Manciu, July 7, 2017.
  Released into the public domain.
*/

#ifndef RGB_H
#define RGB_H

#include "Arduino.h"

class RGBlib{
  public:
    RGBlib(int redPin, int greenPin, int bluePin);
    long HSBtoRGB(int hue, float saturation, float brightness);
    void setColorRGB(unsigned char red, unsigned char green, unsigned char blue);
    void setColorHSB(float hue, float saturation, float brightness);
    void setHue(int hue);
    void setSaturation(int saturation);
    void setBrightness(int brightness);
  private:
    int _redPin, _greenPin, _bluePin;
    int _red, _green, _blue;
    int _hue, _saturation, _brightness;
};

#endif
