#include "servo_driver.h"
bool ServoDriver::begin(uint8_t address,float frequencyHz){
 frequencyHz_=frequencyHz; pca_=Adafruit_PWMServoDriver(address);
 pca_.begin(); pca_.setPWMFreq(frequencyHz_); delay(10); ready_=true; return true;
}
bool ServoDriver::writePulseUs(uint8_t channel,uint16_t pulseUs){
 if(!ready_||channel>15||pulseUs<500||pulseUs>2500)return false;
 float periodUs=1000000.0f/frequencyHz_;
 uint16_t ticks=(uint16_t)((pulseUs/periodUs)*4096.0f);
 if(ticks>4095)ticks=4095; pca_.setPWM(channel,0,ticks); return true;
}
void ServoDriver::disableAll(){if(ready_)for(uint8_t c=0;c<16;c++)pca_.setPWM(c,0,0);}
