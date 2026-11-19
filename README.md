# InMoov AI Humanoid Robot

A reconstructed project foundation for the InMoov humanoid robot.

## Confirmed project context
- One InMoov head and two separate hands.
- Raspberry Pi high-level computer, ESP32 low-level servo controller and PCA9685 PWM servo driver.
- Hitec HS-755HB servos for hands/main hand movement.
- MG996R servos for head/neck movement and jaw.
- MG90S servos for eyes and TPU finger joints; reported insufficient torque for the finger mechanism.
- Whisper speech recognition, Gemini API and Nova voice output are intended components. Exact provider/model details remain to be confirmed.

## API credentials
All API credential fields are blank in raspberry_pi/.env.example. Add credentials locally only; never commit .env.

## Repository layout
- docs/ — project status, hardware inventory, API configuration and servo calibration
- hardware/ — BOM and servo channel templates
- firmware/esp32/ — ESP32/PCA9685 firmware scaffold
- raspberry_pi/ — Python application placeholder and dependency groups
- ros2/ — ROS 2 integration plan

## Important status
This is not a completed robot implementation. ESP32 firmware is an untested scaffold; Raspberry Pi AI/voice adapters and final ROS 2 packages are not implemented. Exact servo counts, wiring, channel mapping and calibration values remain to be measured. See docs/project_status.md.
