#pragma once
#include <Arduino.h>
#include "servo_driver.h"
enum class ServoType { HITECH_HS755HB, MG996R, MG90S };
struct JointConfig {
 const char* name; const char* module; uint8_t channel; ServoType type; bool enabled;
 uint16_t minPulseUs,centerPulseUs,maxPulseUs;
 float minAngleDeg,centerAngleDeg,maxAngleDeg; bool reversed;
};
class Joint {
public:
 void configure(const JointConfig& c,ServoDriver* d){cfg_=c;driver_=d;}
 const char* name() const{return cfg_.name;}
 bool enabled() const{return cfg_.enabled;}
 bool moveTo(float angle);
private:
 JointConfig cfg_{}; ServoDriver* driver_=nullptr;
};
