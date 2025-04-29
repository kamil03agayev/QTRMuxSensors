#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);

void setup() {
  Serial.begin(9600);
  qtr.setWhiteLine(true);  // Track white line on black background
  qtr.calibrate(100);
}

void loop() {
  int pos = qtr.readLine();
  Serial.print("White Line Position: ");
  Serial.println(pos);
  delay(100);
}