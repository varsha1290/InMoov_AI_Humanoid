# InMoov AI Humanoid Robot

An open development repository for a modular InMoov humanoid robot with ESP32-based servo control, Raspberry Pi high-level processing, and a planned AI-powered voice interaction layer.

This repository documents the hardware identified so far, provides starter firmware and configuration templates, and records the work still required to make the robot fully operational. It is intentionally transparent about what is implemented and what remains a placeholder.

---

## 1. Project overview

The goal is to develop an interactive humanoid robot that can:

- Move its head, neck, jaw, eyes, hands and fingers.
- Receive spoken input through a microphone.
- Convert speech into text using Whisper.
- Generate an AI response using the Gemini API.
- Speak the response using the selected Nova voice service.
- Send approved movement commands from the Raspberry Pi to an ESP32.
- Drive hobby servos through a PCA9685 PWM servo driver.
- Progress toward ROS 2 integration for modular robot control, visualization and simulation.

## 2. System architecture

The intended high-level data flow is:

```text
                USER
                 |
          Microphone input
                 |
        Raspberry Pi computer
                 |
        Whisper speech-to-text
                 |
          Recognized text
                 |
          Gemini API
                 |
          AI response text
                 |
        Nova text-to-speech
                 |
             Speaker

        Movement request / command
                 |
          Raspberry Pi app
                 |
             USB / UART
                 |
              ESP32
                 |
             I2C bus
                 |
             PCA9685
                 |
          PWM servo outputs
                 |
       Head / neck / jaw / eyes
              Hands / fingers
```

The diagram describes the intended architecture, not a claim that every connection and software module is already implemented. The actual wiring, communication protocol and final joint mapping must be verified against the assembled robot.

### Controller responsibilities

| Subsystem | Intended responsibility |
|---|---|
| Raspberry Pi | High-level application, AI integration, speech processing and command coordination |
| ESP32 | Low-level command handling and servo-control interface |
| PCA9685 | PWM signal generation for connected hobby servos |
| Servos | Physical movement of the robot joints |
| ROS 2 | Planned robotics middleware for future modular control and visualization |

## 3. Hardware inventory

The following component models and roles have been identified from the project information available so far.

| Component | Identified model / type | Intended use |
|---|---|---|
| Main computer | Raspberry Pi | AI and high-level control | Exact Pi model and OS need confirmation |
| Microcontroller | ESP32 | Low-level control | Exact board variant needs confirmation |
| PWM driver | PCA9685 | Servo PWM generation | Board count, I2C address and wiring need confirmation |
| Hand servos | Hitec HS-755HB | Main hand movement | Exact quantity and joint allocation need confirmation |
| Head / neck / jaw servos | MG996R | Head, neck and jaw movement | Exact quantity and joint allocation need confirmation |
| Eye / finger servos | MG90S | Eye movement and finger joints | User reported insufficient torque for the TPU finger mechanism |
| Mechanical structure | InMoov printed components | Head, neck, torso, hands and other joints | Actual assembly photographs and measured dimensions are needed |
| Finger components | TPU printed joints | Finger articulation | Material hardness, dimensions and linkage details need recording |

Do not infer the total servo count from the example channel map. The number of servos per hand, number of finger joints and total PCA9685 channels are still to be measured.

See [docs/hardware_inventory.md](docs/hardware_inventory.md) and the templates in [hardware/](hardware/).

## 4. Software and AI components

| Software / service | Planned role |
|---|---|
| Python | Raspberry Pi application and integration |
| Whisper | Speech-to-text |
| Gemini API | AI response generation |
| Nova voice | Text-to-speech output |
| ESP32 Arduino framework | Microcontroller firmware |
| PlatformIO | ESP32 project build environment |
| Adafruit PCA9685 library | PWM driver interface |
| ROS 2 | Future robot middleware |

### Python dependency groups

The Raspberry Pi folder separates some optional dependencies so that the robot does not install every package unnecessarily:

- `requirements.txt` — minimal common dependencies.
- `requirements-gemini.txt` — Gemini client.
- `requirements-whisper-api.txt` — hosted speech-to-text client dependency.
- `requirements-whisper-local.txt` — local Whisper-related dependencies.
- `requirements-audio.txt` — optional audio capture/playback libraries.
- `requirements-camera.txt` — optional camera-related Python dependency.
- `requirements-dev.txt` — development and code-quality tools.

Some packages, especially local speech recognition and audio/camera libraries, may require OS-level packages, supported hardware or additional setup. Install only the feature groups you intend to use.

## 5. Repository structure

```text
InMoov_AI_Humanoid/
|
|-- README.md
|-- .gitignore
|
|-- docs/
|   |-- project_status.md
|   |-- hardware_inventory.md
|   |-- servo_calibration.md
|   |-- api_configuration.md
|   |-- assembly_photos.md
|
|-- hardware/
|   |-- bom_template.csv
|   |-- servo_channel_map_template.csv
|
|-- firmware/
|   |-- esp32/
|       |-- platformio.ini
|       |-- src/
|           |-- main.cpp
|           |-- servo_driver.h
|           |-- servo_driver.cpp
|           |-- joint.h
|           |-- joint.cpp
|           |-- joint_config.h
|
|-- raspberry_pi/
|   |-- app.py
|   |-- .env.example
|   |-- config.example.yaml
|   |-- requirements*.txt
|
|-- ros2/
    |-- README.md
```

Some modules are deliberately small starter files. Their presence does not mean the corresponding feature is complete.

## 6. Getting started

### A. Clone the repository

```bash
git clone https://github.com/varsha1290/InMoov_AI_Humanoid.git
cd InMoov_AI_Humanoid
```

### B. Prepare the ESP32 development environment

1. Install Visual Studio Code and PlatformIO, or install the PlatformIO CLI.
2. Open the `firmware/esp32/` directory as a PlatformIO project.
3. Confirm the exact ESP32 board model and select the matching PlatformIO board identifier.
4. Check the PCA9685 I2C wiring and address before powering the servo system.
5. Build the firmware first. Do not connect loaded mechanical linkages for the first test.
6. Do not assume the example pulse values or joint limits are safe for your individual servos.

The current PlatformIO configuration uses the generic `esp32dev` board target. Change it if your actual ESP32 board requires a different target.

### C. Prepare the Raspberry Pi Python environment

```bash
cd raspberry_pi
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install -r requirements.txt
cp .env.example .env
cp config.example.yaml config.yaml
```

Install optional requirements only for the selected integrations. For example, install the Gemini dependency with:

```bash
python -m pip install -r requirements-gemini.txt
```

The current `app.py` is a placeholder. It does not yet perform speech recognition, call Gemini, synthesize speech or control the robot.

## 7. Servo control and calibration

The ESP32 firmware scaffold uses a PCA9685 driver and a configurable joint table.

The example joint table currently contains illustrative entries for neck pan, neck tilt, jaw, eye pan, eye tilt, left and right hand main movement, and one example finger joint. These are not a verified map of the assembled robot.

### Important technical points

- The PCA9685 generates PWM signals; it does not read the internal potentiometer in a standard hobby servo.
- Hobby servos normally use their own internal feedback electronics to control their output position.
- A requested angle is not proof that the physical joint reached that angle.
- Servo pulse limits and mechanical travel differ between models and individual units.
- The MG90S torque limitation reported for the TPU finger mechanism must be addressed before treating the finger design as reliable.

Before enabling any joint, measure and record its safe pulse limits, centre position, direction, mechanical travel and supply requirements. Follow [docs/servo_calibration.md](docs/servo_calibration.md).

**The example firmware keeps all joints disabled by default.** Do not enable them until the actual servo/channel mapping and safe calibration values have been entered.

## 8. Serial command scaffold

The current ESP32 source contains a simple serial command parser. The intended command forms are:

| Command | Intended behavior |
|---|---|
| `PING` | Respond with `PONG` |
| `HELP` | Print the command summary |
| `STATUS` | Report PCA status and joint enabled flags |
| `MOVE,<joint>,<degrees>` | Request movement of a named, enabled joint |
| `STOP` | Disable PCA9685 PWM outputs |

Example command format:

```text
MOVE,neck_pan,10
```

This is an early development protocol. It does not include authentication, robust error recovery, command timeouts, motion planning or a safety-rated emergency-stop function.

**The `STOP` command is not an emergency stop.** A separate physical means of isolating servo power is required for safe testing. The current scaffold also has all example joints disabled, so movement requests will be rejected until the configuration is deliberately completed and tested.

## 9. API keys and configuration

All credential fields are intentionally blank in `raspberry_pi/.env.example`.

The placeholders include:

- `GEMINI_API_KEY`
- `OPENAI_API_KEY`
- `WHISPER_MODE`
- `NOVA_TTS_API_KEY`
- `NOVA_TTS_BASE_URL`
- `NOVA_TTS_MODEL`
- `ESP32_SERIAL_PORT`
- `ESP32_BAUDRATE`

The exact Nova voice service has not yet been confirmed. Do not assume that a voice name alone identifies a particular API provider.

Keep actual credentials in the local `.env` file. The `.gitignore` file excludes it from normal Git commits. Never paste private API keys into source code, README files, screenshots or public issues. If a real key is ever committed, revoke or rotate it; removing it in a later commit does not erase it from Git history.

See [docs/api_configuration.md](docs/api_configuration.md).

## 10. ROS 2 integration plan

ROS 2 integration is a future development step, not a completed package in this repository.

The robot description should be built from the actual assembled geometry and measured joint properties. Required inputs include:

- Mesh or CAD files with appropriate usage rights.
- Link and joint names.
- Joint origins and rotation axes.
- Joint limits and direction.
- Link masses and inertial properties.
- Collision geometry.
- A verified hardware communication interface to the ESP32.

The planned sequence is to create a URDF/Xacro description, validate it in RViz, then develop the hardware interface and simulation/control integration. See [ros2/README.md](ros2/README.md).

## 11. Safety and testing

This project contains moving mechanisms and high-current servo loads. Test incrementally.

- Secure the robot structure before powering servos.
- Use a suitable regulated servo power supply sized for the actual servo load.
- Do not draw servo power from the ESP32 3.3 V pin or Raspberry Pi GPIO.
- Confirm common signal ground and correct wiring.
- Check each servo's voltage and current requirements from its exact datasheet.
- Begin with one unloaded servo and a narrow verified pulse range.
- Keep hands clear of linkages and pinch points.
- Provide a physical way to disconnect servo power.
- Test reset, communication loss and power interruption behavior.
- Do not allow an AI-generated response to directly trigger arbitrary joint movement. Use a validated, allowlisted command layer with limits.

No safety certification or full hardware validation is claimed.

## 12. Development roadmap

| Phase | Work | Completion evidence |
|---|---|---|
| 1. Hardware inventory | Record every servo, board, supply and printed component | Completed BOM and photos |
| 2. Wiring and channel map | Verify PCA9685 addresses, I2C wiring and servo channels | Tested wiring diagram and channel CSV |
| 3. Servo calibration | Measure safe pulse and mechanical travel per joint | Calibration record for each servo |
| 4. ESP32 controller | Build, flash and test serial commands and PWM | Build log and bench test results |
| 5. Raspberry Pi bridge | Implement reliable serial communication | Tested command/response logs |
| 6. Voice input | Integrate microphone and Whisper | Verified speech-to-text test |
| 7. AI response | Integrate Gemini with error handling | Verified API test with private key stored locally |
| 8. Voice output | Integrate the confirmed Nova TTS service | Verified audio playback test |
| 9. Robot behavior | Add safe, allowlisted movement commands | Repeatable joint and behavior tests |
| 10. ROS 2 | Create measured robot description and control integration | RViz/ROS 2 validation |
| 11. Full-system testing | Test faults, resets, communication and power behavior | Documented test report |

## 14. Contributing and updating the project

When adding a feature:

1. Create a branch for the change.
2. Keep hardware-specific values in configuration or documented tables.
3. Do not hard-code API credentials.
4. Record the exact hardware and software versions used.
5. Add build/test evidence and known limitations.
6. Update the relevant documentation when wiring, channels or behavior change.
7. Merge only after reviewing the changes.

---

## Project owner

Repository: [varsha1290/InMoov_AI_Humanoid](https://github.com/varsha1290/InMoov_AI_Humanoid)

This project is being developed iteratively. The aim is to make each subsystem understandable, testable and documented before integrating the complete humanoid robot.
