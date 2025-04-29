#include "QTRMuxSensor.h"

QTRMuxSensor::QTRMuxSensor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t signalPin, uint8_t totalChannels)
  : signalPin(signalPin), totalChannels(totalChannels), isWhiteLine(false) {

  muxPins[0] = s0;
  muxPins[1] = s1;
  muxPins[2] = s2;
  muxPins[3] = s3;

  for (int i = 0; i < 4; i++) {
    pinMode(muxPins[i], OUTPUT);
    digitalWrite(muxPins[i], LOW);
  }

  sensorMin = new int[totalChannels];
  sensorMax = new int[totalChannels];
  sensorValues = new int[totalChannels];

  for (int i = 0; i < totalChannels; i++) {
    sensorMin[i] = 1023;
    sensorMax[i] = 0;
    sensorValues[i] = 0;
  }
}

void QTRMuxSensor::setWhiteLine(bool white) {
  isWhiteLine = white;
}

void QTRMuxSensor::calibrate(uint16_t samples, uint16_t delayMs) {
  for (uint16_t s = 0; s < samples; s++) {
    for (uint8_t ch = 0; ch < totalChannels; ch++) {
      int val = readRaw(ch);
      if (val < sensorMin[ch]) sensorMin[ch] = val;
      if (val > sensorMax[ch]) sensorMax[ch] = val;
    }
    delay(delayMs);
  }
}

int QTRMuxSensor::readCalibrated(uint8_t channel) {
  int raw = readRaw(channel);
  int minV = sensorMin[channel];
  int maxV = sensorMax[channel];
  if (maxV == minV) return 0;
  int value = constrain((1000L * (raw - minV)) / (maxV - minV), 0, 1000);
  return isWhiteLine ? 1000 - value : value;
}

int QTRMuxSensor::readRaw(uint8_t channel) {
  setMuxChannel(channel);
  delayMicroseconds(5);
  return analogRead(signalPin);
}

int QTRMuxSensor::readLine() {
  long avg = 0;
  long sum = 0;

  for (uint8_t i = 0; i < totalChannels; i++) {
    int value = readCalibrated(i);
    sensorValues[i] = value;

    if (value > 50) {
      avg += (long)value * (i * 1000);
      sum += value;
    }
  }

  if (sum == 0) return -1;
  return avg / sum;
}

int* QTRMuxSensor::getSensorValues() {
  return sensorValues;
}

void QTRMuxSensor::setMuxChannel(uint8_t channel) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(muxPins[i], (channel >> i) & 0x01);
  }
}
