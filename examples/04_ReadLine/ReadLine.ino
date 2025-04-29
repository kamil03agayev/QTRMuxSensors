#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);

void setup() {
  Serial.begin(9600);
  qtr.setWhiteLine(false);  // true = white line on black background
  qtr.calibrate(100);
}

void loop() {
  int pos = qtr.readLine();
  Serial.print("Line Position: ");
  Serial.println(pos);
  delay(100);
}