#pragma once
#include "joint.h"
static const JointConfig JOINTS[] = {
 {"neck_pan","head",0,ServoType::MG996R,false,1475,1500,1525,-3,0,3,false},
 {"neck_tilt","head",1,ServoType::MG996R,false,1475,1500,1525,-3,0,3,false},
 {"jaw","jaw",2,ServoType::MG996R,false,1475,1500,1525,-3,0,3,false},
 {"eye_pan","eyes",3,ServoType::MG90S,false,1475,1500,1525,-3,0,3,false},
 {"eye_tilt","eyes",4,ServoType::MG90S,false,1475,1500,1525,-3,0,3,false},
 {"left_hand_main","left_hand",5,ServoType::HITECH_HS755HB,false,900,1500,2100,-45,0,45,false},
 {"right_hand_main","right_hand",6,ServoType::HITECH_HS755HB,false,900,1500,2100,-45,0,45,false},
 {"finger_joint_example","left_hand",7,ServoType::MG90S,false,1475,1500,1525,-3,0,3,false},
};
static const size_t JOINT_COUNT=sizeof(JOINTS)/sizeof(JOINTS[0]);
static const uint8_t PCA9685_ADDRESS=0x40;
static const float SERVO_PWM_HZ=50.0f;
