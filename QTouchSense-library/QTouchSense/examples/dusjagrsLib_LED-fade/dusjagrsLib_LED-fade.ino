#include <QTouchSense.h>

int RefPin  = 5;

int ref1 = 0;

const uint16_t ledFadeTable[32] = {0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 21, 25, 30, 36, 43, 51, 61, 73, 87, 104, 125, 149, 178, 213, 255}; // this is an exponential series to model the perception of the LED brightness by the human eye

void setup() {

  Serial.begin(115200);
  QTouchSense.settings();
  ref1 = QTouchSense.sense(0, RefPin, 64);
  
}

void loop() {

  int value1 = (ref1 - QTouchSense.sense(0, RefPin, 16));
  
  int16_t idx= (value1); // offset probe_val by value of untouched probe
  if(idx<0) idx= 0; // limit the index!!!
  idx/= 1; // scale the index
  if(idx>31) idx= 31; // limit the index!!!
  
  analogWrite(9, ledFadeTable[idx]);
  
  Serial.print(value1);
  Serial.print(' ');
  Serial.println(idx);
  
  delay(10);
}
