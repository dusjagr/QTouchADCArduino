#include <QTouchADCduino.h>

int refPin  = 0;
int value1 = 0;
int value2 = 0;
int ref1 = 0;
int ref2 = 0;

int16_t idx = 0;
const uint16_t ledFadeTable[32] = {0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 21, 25, 30, 36, 43, 51, 61, 73, 87, 104, 125, 149, 178, 213, 255}; // this is an exponential series to model the perception of the LED brightness by the human eye

void setup() {

  Serial.begin(115200);
  QTouchADCduino.init();
  ref1 = QTouchADCduino.sense(1, refPin, 64);
  ref2 = QTouchADCduino.sense(2, refPin, 64);
  
}

void loop() {
  unsigned long time;
  time= micros();
  
  value1 = (QTouchADCduino.sense(1, refPin, 20) - ref1);
  time= micros() - time;
  value2 = (QTouchADCduino.sense(2, refPin, 20) - ref1);
  
  idx= (value1); // offset probe_val by value of untouched probe
  if(idx<0) idx= 0; // limit the index!!!
  idx/= 5; // scale the index
  if(idx>31) idx= 31; // limit the index!!!
  
  analogWrite(9, ledFadeTable[idx]);
  
  idx= (value2); // offset probe_val by value of untouched probe
  if(idx<0) idx= 0; // limit the index!!!
  idx/= 1; // scale the index
  if(idx>31) idx= 31; // limit the index!!!
  
  analogWrite(10, ledFadeTable[idx]);
  
  Serial.print(value1);
  Serial.print(' ');
  Serial.print(time);
  Serial.print(' ');
  Serial.println(value2);
  
  delay(10);
}
