#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);  // MUX control pins and analog pin

void setup() {
  Serial.begin(9600);
  Serial.println("Calibrating...");
  qtr.calibrate(100, 10);  // 100 samples, 10 ms delay
  Serial.println("Calibration done!");
}

void loop() {
  for (int i = 0; i < 16; i++) {
    Serial.print("Calibrated [");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(qtr.readCalibrated(i));
  }
  delay(500);
}