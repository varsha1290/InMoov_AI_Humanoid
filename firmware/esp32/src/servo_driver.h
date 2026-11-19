#pragma once
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
class ServoDriver {
public:
 bool begin(uint8_t address,float frequencyHz);
 bool writePulseUs(uint8_t channel,uint16_t pulseUs);
 void disableAll();
private:
 Adafruit_PWMServoDriver pca_{};
 float frequencyHz_=50.0f; bool ready_=false;
};
