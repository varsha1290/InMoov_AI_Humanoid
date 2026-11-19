# Hardware inventory

| Item | Confirmed details | Still required |
|---|---|---|
| Humanoid frame | InMoov | STL revision and assembly list |
| Main computer | Raspberry Pi | Exact model, RAM, OS |
| Motion controller | ESP32 | Board variant, USB/UART details |
| PWM driver | PCA9685 | Board count, address, wiring |
| Hand/main movement servos | Hitec HS-755HB | Count and exact joint allocation |
| Head/neck servos | MG996R | Count and exact joint allocation |
| Jaw servo | MG996R | Confirm whether separate unit |
| Eye servos | MG90S | Count and axes |
| Finger servos | MG90S | Count per hand/finger and linkage |
| Finger structure | TPU finger-joint parts | TPU hardness, geometry, joint friction |
| AI | Gemini API | Model, API method, configuration |
| Voice | Nova voice | Exact service/provider/API and audio hardware |

For each servo model, record the exact manufacturer's datasheet, allowed voltage, stall current, pulse range and operating travel. For clone/variant models, use the exact unit's documentation or bench measurements.
