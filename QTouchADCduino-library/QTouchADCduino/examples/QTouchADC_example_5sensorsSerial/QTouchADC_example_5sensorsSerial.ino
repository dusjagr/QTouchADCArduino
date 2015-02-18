#include <QTouchADCduino.h>

int RefPin  = 5;

int ref1 = 0;
int ref2 = 0;
int ref3 = 0;
int ref4 = 0;
int ref5 = 0;

void setup() {

  Serial.begin(115200);
  QTouchADCduino.init();
  ref1 = QTouchADCduino.sense(0, RefPin, 64);
  ref2 = QTouchADCduino.sense(1, RefPin, 64);
  ref3 = QTouchADCduino.sense(2, RefPin, 64);
  ref4 = QTouchADCduino.sense(3, RefPin, 64);
  ref5 = QTouchADCduino.sense(4, RefPin, 64);
  
}

void loop() {

  int value1 = QTouchADCduino.sense(0, RefPin, 20);
  int value2 = QTouchADCduino.sense(1, RefPin, 20);
  int value3 = QTouchADCduino.sense(2, RefPin, 20);
  int value4 = QTouchADCduino.sense(3, RefPin, 20);
  int value5 = QTouchADCduino.sense(4, RefPin, 20);
  Serial.print(value1 - ref1);
  Serial.print(' ');
  Serial.print(value2 - ref2);
  Serial.print(' ');
  Serial.print(value3 - ref3);
  Serial.print(' ');
  Serial.print(value4 - ref4);
  Serial.print(' ');
  Serial.println(value5 - ref5);

  delay(10);
}
