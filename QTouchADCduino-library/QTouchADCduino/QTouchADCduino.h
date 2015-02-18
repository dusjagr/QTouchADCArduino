/*
  QTouchSense.h - Library for Capacitive touch sensors using only one ADC PIN and a Reference
  modified from https://github.com/jgeisler0303/QTouchADCArduino
  Released into the public domain.
*/

#ifndef QTouchADCduino_h
#define QTouchADCduino_h

#include <Arduino.h>

class QTouchADCduinoClass
{
  public:
    void init();
    uint16_t sense(byte ADCReadPin, byte ADCRef, int samples);
};

extern QTouchADCduinoClass QTouchADCduino;

#endif

