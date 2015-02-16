#include <QTouchSense.h>

int RefPin  = 5;

int ref1 = 0;

void setup() {

  Serial.begin(115200);
  QTouchSense.settings();
  ref1 = QTouchSense.sense(0, RefPin, 64);
  
}

void loop() {

  int value1 = (ref1 - QTouchSense.sense(0, RefPin, 16));

  Serial.println(value1);

  delay(10);
}
