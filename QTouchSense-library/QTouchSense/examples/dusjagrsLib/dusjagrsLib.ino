#include <QTouchSense.h>

int RefPin  = 5;

int ref1 = 0;
int ref2 = 0;
int ref3 = 0;
int ref4 = 0;
int ref5 = 0;

void setup() {

  Serial.begin(115200);
  QTouchSense.settings();
  ref1 = QTouchSense.sense(0, RefPin, 64);
  ref2 = QTouchSense.sense(1, RefPin, 64);
  ref3 = QTouchSense.sense(2, RefPin, 64);
  ref4 = QTouchSense.sense(3, RefPin, 64);
  ref5 = QTouchSense.sense(4, RefPin, 64);
  
}

void loop() {

  int value1 = QTouchSense.sense(0, RefPin, 20);
  int value2 = QTouchSense.sense(1, RefPin, 20);
  int value3 = QTouchSense.sense(2, RefPin, 20);
  int value4 = QTouchSense.sense(3, RefPin, 20);
  int value5 = QTouchSense.sense(4, RefPin, 20);
  Serial.print(ref1-value1);
  Serial.print(' ');
  Serial.print(ref2-value2);
  Serial.print(' ');
  Serial.print(ref3-value3);
  Serial.print(' ');
  Serial.print(ref4-value4);
  Serial.print(' ');
  Serial.println(ref5-value5);

  delay(10);
}
