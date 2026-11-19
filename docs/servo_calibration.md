# Servo calibration

## Critical rule
A commanded angle is not proof of the mechanism's actual angle. Standard hobby servos close their own position loop internally. The PCA9685 generates PWM and does not read the servo's internal potentiometer.

## Safe procedure
1. Disconnect the mechanical linkage and secure the servo.
2. Confirm the exact servo model and permitted supply voltage from its datasheet.
3. Start with a narrow pulse range around the neutral point; do not assume 500–2500 microseconds is safe for every servo.
4. Move in small increments and watch for hard stops, buzzing, heating or rising current.
5. Record the minimum safe pulse, centre pulse and maximum safe pulse for that individual servo.
6. Reattach the horn at the measured centre position.
7. Repeat at low speed with the linkage, checking the full mechanical clearance.
8. Store calibration values in the servo channel map.

Do not force a servo against a mechanical stop. Stop immediately if it buzzes, stalls or heats up. Use a suitable external servo power supply; do not power multiple servos from the ESP32 regulator.
