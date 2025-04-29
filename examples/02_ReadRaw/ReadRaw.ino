#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 16; i++) {
    Serial.print("Raw [");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(qtr.readRaw(i));
  }
  Serial.println("---");
  delay(500);
}