#ifndef QTRMUXSENSOR_H
#define QTRMUXSENSOR_H

#include <Arduino.h>

class QTRMuxSensor {
  public:
    QTRMuxSensor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t signalPin, uint8_t totalChannels = 16);
    
    void setWhiteLine(bool white);
    void calibrate(uint16_t samples = 100, uint16_t delayMs = 10);
    int readCalibrated(uint8_t channel);
    int readRaw(uint8_t channel);
    int readLine();
    int* getSensorValues();

  private:
    void setMuxChannel(uint8_t channel);

    uint8_t muxPins[4];
    uint8_t signalPin;
    uint8_t totalChannels;
    int* sensorMin;
    int* sensorMax;
    int* sensorValues;
    bool isWhiteLine;
};

#endif
