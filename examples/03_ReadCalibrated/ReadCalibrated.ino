#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);

void setup() {
  Serial.begin(9600);
  qtr.calibrate(100);
}

void loop() {
  for (int i = 0; i < 16; i++) {
    Serial.print("Sensor [");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(qtr.readCalibrated(i));
  }
  delay(500);
}