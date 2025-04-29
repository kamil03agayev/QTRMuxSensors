# QTRMuxSensor Library

The **QTRMuxSensor** library is designed for interfacing with QTR (Quadrature Reflectance) sensors using a 4-bit multiplexer. It allows you to read values from multiple QTR sensors using a single analog pin on your microcontroller, and it supports features like calibration, line-following, and detection of black/white lines.

This library is perfect for robotics projects where multiple sensors are used for line-following or object detection, and you need to manage a limited number of analog pins.

## Features
- **Multiple Sensor Support**: Can read up to 16 QTR sensors using a 4-bit multiplexer .
- **Calibration**: Calibrate sensor values for more accurate readings.
- **Line Detection**: Detect the position of a line based on sensor readings.
- **White/Black Line Support**: Switch between white line on black background and black line on white background detection.
- **Easy Integration**: Simple API for integration into any Arduino project.

## Installation
1. Download the library from [GitHub](https://github.com/kamil03agayev/QTRMuxSensors) or use the ZIP file provided.
2. Open the Arduino IDE.
3. Go to **Sketch > Include Library > Add .ZIP Library**.
4. Select the downloaded `.zip` file to install the library.

Alternatively, you can manually copy the `QTRMuxSensor` folder into your Arduino libraries directory:
- **Windows**: `Documents/Arduino/libraries/`
- **macOS/Linux**: `~/Documents/Arduino/libraries/`

After installation, restart the Arduino IDE.

## Example Usage

### 1. Calibration Example

This example shows how to calibrate the QTR sensors by reading multiple samples and setting minimum and maximum values.

```cpp
#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);  // MUX pins (S0, S1, S2, S3) and signal pin

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
```

### 2. Raw Sensor Reading Example

This example shows how to read the raw values from each sensor channel.

```cpp
#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);  // MUX pins (S0, S1, S2, S3) and signal pin

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
```

### 3. Line Following Example

This example shows how to read the sensor values and use them for line following.

```cpp
#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);

void setup() {
  Serial.begin(9600);
  qtr.setWhiteLine(false);  // False for black line on white background
  qtr.calibrate(100);
}

void loop() {
  int pos = qtr.readLine();
  Serial.print("Line Position: ");
  Serial.println(pos);
  delay(100);
}
```

### 4. White Line Detection

This example shows how to detect a white line on a black background by setting the setWhiteLine(true) function.

```cpp
#include <QTRMuxSensor.h>

QTRMuxSensor qtr(2, 3, 4, 5, A0);

void setup() {
  Serial.begin(9600);
  qtr.setWhiteLine(true);  // True for white line on black background
  qtr.calibrate(100);
}

void loop() {
  int pos = qtr.readLine();
  Serial.print("White Line Position: ");
  Serial.println(pos);
  delay(100);
}
```

## API

`QTRMuxSensor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t signalPin, uint8_t totalChannels = 16);`
Constructor to initialize the sensor object with the multiplexer control pins (s0, s1, s2, s3) and the signal pin used to read analog values.

`void setWhiteLine(bool white);`
Sets whether you're using a white line on black background (true) or black line on white background (false).

`void calibrate(uint16_t samples = 100, uint16_t delayMs = 10);`
Calibrates the sensor by reading samples number of values and storing the minimum and maximum values.

`int readRaw(uint8_t channel);`
Reads the raw value from a specified sensor channel.

`int readCalibrated(uint8_t channel);`
Reads the calibrated value from a specified sensor channel.

`int readLine();`
Reads all sensors and returns the position of the line.

`int* getSensorValues();`
Returns an array of raw or calibrated sensor values.

## Troubleshooting

- If the example code doesn't work, ensure that the MUX pins are connected correctly and the signalPin is properly configured.
- Calibration values may need adjustment depending on your sensors and environment.

## License

This library is licensed under the MIT License.
