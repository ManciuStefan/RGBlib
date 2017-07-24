/*
  RGBlib.cpp - Library for controlling an RGB led or strip.
  Created by Stefan Manciu, July 7, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "RGBlib.h"

#define MAX_HUE 360
#define MAX_SATURATION 100
#define MAX_BRIGHTNESS 100

RGBlib::RGBlib(int redPin, int greenPin, int bluePin)
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;

  _hue = 0;
  _saturation = 255;
  _brightness = 255;
}

long RGBlib::HSBtoRGB(int hue, float saturation, float brightness) {
  float r = 0, g = 0, b = 0;

  hue = hue % MAX_HUE;
  saturation = saturation / MAX_SATURATION;
  brightness = brightness / MAX_BRIGHTNESS;

  int hue_case = hue / 60;

  float f = (hue / 60.0) - hue_case;
  float pv = brightness * (1 - saturation);
  float qv = brightness * (1 - saturation * f);
  float tv = brightness * (1 - saturation * (1 - f));
  
  switch (hue_case) {
    case 0:
      r = brightness;
      g = tv;
      b = pv;
      break;
    case 1:
      r = qv;
      g = brightness;
      b = pv;
      break;
    case 2:
      r = pv;
      g = brightness;
      b = tv;
      break;
    case 3:
      r = pv;
      g = qv;
      b = brightness;
      break;
    case 4:
      r = tv;
      g = pv;
      b = brightness;
      break;
    case 5:
      r = brightness;
      g = pv;
      b = qv;
      break;
  }

  long red    = constrain(255 * r, 0, 255);
  long green  = constrain(255 * g, 0, 255);
  long blue   = constrain(255 * b, 0, 255);

  return long((red << 16) | (green << 8) | (blue));
}

void RGBlib::setColorRGB(unsigned char red, unsigned char green, unsigned char blue)
{
  analogWrite(_redPin, red);
  analogWrite(_greenPin, green);
  analogWrite(_bluePin, blue);
}

void RGBlib::setColorHSB(float hue, float saturation, float brightness)
{
  long hsb = HSBtoRGB(hue, saturation, brightness);
  int red = hsb >> 16 & 255;
  int green = hsb >> 8 & 255;
  int blue = hsb & 255;

  setColorRGB(red, green, blue);

  _hue = hue;
  _saturation = saturation;
  _brightness = brightness;

  _red = red;
  _green = green;
  _blue = blue;
}

void RGBlib::setHue(int hue)
{
  setColorHSB(hue, _saturation, _brightness);
}

void RGBlib::setSaturation(int saturation)
{
  setColorHSB(_hue, saturation, _brightness);
}

void RGBlib::setBrightness(int brightness)
{
  setColorHSB(_hue, _saturation, brightness);
}
