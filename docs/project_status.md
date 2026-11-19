# Project status

This repository is a reconstructed project foundation because the original source code is unavailable.

## Confirmed
- One InMoov head and two separate hands.
- Raspberry Pi high-level computer, ESP32 low-level controller and PCA9685 PWM servo driver.
- Hitec HS-755HB servos for hand/main hand movement.
- MG996R servos for head/neck movement and jaw.
- MG90S servos for eyes and TPU finger joints; the user reported insufficient torque for the finger mechanism.
- Whisper speech recognition, Gemini API and Nova voice output are part of the intended AI/voice stack.

## Not yet verified or implemented
- Exact servo quantities and finger-servo count per hand.
- PCA9685 board count, I2C addresses, channel allocation and wiring.
- Per-servo pulse limits, safe mechanical travel and calibration.
- Complete Raspberry Pi Whisper/Gemini/Nova adapters.
- Final ROS 2 description, URDF/Xacro, simulation and control packages.
- Physical safety validation and full robot testing.

## Important
The ESP32 code is a starter scaffold and has not been compiled or tested on the physical robot. The Raspberry Pi application is a placeholder. Do not treat this repository as production-ready or safety-certified.
