#include <QTouchADCduino.h>

int refPin  = 5;

int ref1 = 0;

void setup() {

  Serial.begin(115200);
  QTouchADCduino.init();
  ref1 = QTouchADCduino.sense(0, refPin, 64);
  
}

void loop() {

  int value1 = (QTouchADCduino.sense(0, refPin, 16) - ref1);

  Serial.println(value1);

  delay(10);
}
