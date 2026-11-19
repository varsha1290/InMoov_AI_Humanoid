#include <Arduino.h>
#include <Wire.h>
#include "joint_config.h"
#include "servo_driver.h"
#include "joint.h"
ServoDriver driver;
Joint joints[JOINT_COUNT];
String line;
bool pcaReady=false;
Joint* findJoint(const char* n){for(size_t i=0;i<JOINT_COUNT;i++)if(!strcmp(joints[i].name(),n))return &joints[i];return nullptr;}
void setup(){
 Serial.begin(115200);line.reserve(128);Wire.begin();
 pcaReady=driver.begin(PCA9685_ADDRESS,SERVO_PWM_HZ);
 for(size_t i=0;i<JOINT_COUNT;i++)joints[i].configure(JOINTS[i],&driver);
 Serial.println("INMOOV_ESP32_BOOT");Serial.println(pcaReady?"PCA_READY":"PCA_INIT_FAILED");
 Serial.println("ALL_JOINTS_DISABLED_BY_DEFAULT");
}
void handle(String s){
 s.trim();
 if(s=="PING"){Serial.println("PONG");return;}
 if(s=="HELP"){Serial.println("PING|STATUS|MOVE,<joint>,<deg>|STOP");return;}
 if(s=="STATUS"){Serial.print("PCA,");Serial.println(pcaReady?"READY":"FAILED");for(size_t i=0;i<JOINT_COUNT;i++){Serial.print(joints[i].name());Serial.print(",enabled=");Serial.println(joints[i].enabled());}return;}
 if(s=="STOP"){driver.disableAll();Serial.println("PWM_DISABLED_NOT_SAFETY_ESTOP");return;}
 if(s.startsWith("MOVE,")){
  int k=s.indexOf(',',5);if(k<0){Serial.println("ERR,FORMAT");return;}
  String n=s.substring(5,k);float a=s.substring(k+1).toFloat();Joint* j=findJoint(n.c_str());
  if(!j){Serial.println("ERR,UNKNOWN_JOINT");return;}
  if(!pcaReady||!j->moveTo(a)){Serial.println("ERR,DISABLED_OR_OUT_OF_RANGE");return;}
  Serial.println("OK");return;
 }
 Serial.println("ERR,UNKNOWN_COMMAND");
}
void loop(){
 while(Serial.available()){char c=(char)Serial.read();if(c=='\n'||c=='\r'){if(line.length()){handle(line);line="";}}else if(line.length()<120)line+=c;else{line="";Serial.println("ERR,LINE_TOO_LONG");}}
}
