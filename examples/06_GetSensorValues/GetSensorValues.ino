#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);

void setup() {
  Serial.begin(9600);
  qtr.calibrate(100);
}

void loop() {
  qtr.readLine();  // updates internal sensorValues array
  int* values = qtr.getSensorValues();

  for (int i = 0; i < 16; i++) {
    Serial.print("[" + String(i) + "]: ");
    Serial.print(values[i]);
    Serial.print("  ");
  }

  Serial.println();
  delay(500);
}