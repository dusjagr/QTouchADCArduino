/*
  QTouchSense.h - Library for Capacitive touch sensors using only one ADC PIN and a Reference
  modified from https://github.com/jgeisler0303/QTouchADCArduino
  Released into the public domain.
*/

#ifndef QTouchSense_h
#define QTouchSense_h

#include <Arduino.h>

class QTouchSenseClass
{
  public:
    void settings();
    uint16_t sense(byte ADCReadPin, byte ADCRef, int samples);
};

extern QTouchSenseClass QTouchSense;

#endif

