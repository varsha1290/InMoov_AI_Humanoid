# InMoov AI Humanoid Robot

An open-source robotics project to develop an interactive InMoov humanoid robot using **Raspberry Pi, ESP32, PCA9685 servo control, speech recognition and AI-powered conversation**.

The project brings together mechanical assembly, embedded control, Python-based integration and robotics software. The long-term goal is to create a humanoid robot that can listen, understand, respond through voice and perform controlled physical movements.

---

## Project overview

The robot is being developed around these capabilities:

- **Humanoid movement:** head, neck, jaw, eyes, hands and fingers.
- **Speech input:** capture voice through a microphone and convert it into text using Whisper.
- **AI conversation:** generate responses using the Gemini API.
- **Voice output:** speak responses through the selected Nova voice service.
- **Servo control:** send movement requests from the Raspberry Pi to an ESP32, which controls servos through a PCA9685.
- **Robotics integration:** build toward ROS 2-based robot description, visualization, simulation and modular control.

## System architecture

### Voice interaction flow

```text
User speaks
    |
Microphone
    |
Raspberry Pi
    |
Whisper - speech to text
    |
Recognized text
    |
Gemini API - response generation
    |
Response text
    |
Nova voice - text to speech
    |
Speaker
```

### Motion-control flow

```text
Movement request
    |
Raspberry Pi application
    |
USB / UART serial communication
    |
ESP32 microcontroller
    |
I2C communication
    |
PCA9685 servo driver
    |
PWM signals
    |
Robot servos
    |
Head / neck / jaw / eyes / hands / fingers
```

### Main controller roles

| Subsystem | Responsibility |
|---|---|
| Raspberry Pi | Runs the high-level Python application, AI services, speech processing and command coordination |
| ESP32 | Receives movement commands and manages low-level servo control |
| PCA9685 | Generates PWM control signals for connected servos |
| Hobby servos | Move the robot's mechanical joints |
| ROS 2 | Provides the planned framework for robot description, visualization and future control integration |

These diagrams show the intended system design. Actual wiring, serial protocol, joint mapping and integration must be checked against the assembled robot.

## Hardware

| Component | Model / type | Intended use |
|---|---|---|
| Main computer | Raspberry Pi | High-level processing and AI integration |
| Microcontroller | ESP32 | Embedded control and servo command handling |
| Servo driver | PCA9685 | Multi-channel PWM generation |
| Hand servos | Hitec HS-755HB | Main hand movement |
| Head, neck and jaw servos | MG996R | Head, neck and jaw movement |
| Eye and finger servos | MG90S | Eye movement and finger joints |
| Robot structure | InMoov printed components | Head, neck, torso, arms and hands |
| Finger joints | TPU printed components | Flexible finger articulation |

### Mechanical assembly

The robot uses 3D-printed InMoov components and flexible TPU finger-joint parts. The assembly is being developed in modules, including the head, neck, torso and hands.

### Servo arrangement

- **Hitec HS-755HB:** used for main hand movement.
- **MG996R:** used for head, neck and jaw movement.
- **MG90S:** used for eye movement and finger joints.

The MG90S has been found to provide insufficient torque for the current TPU finger mechanism. Finger actuation should be reviewed mechanically and electrically before increasing load or operating the mechanism repeatedly.

The exact servo quantity, per-hand joint count, PCA9685 board count, I2C addresses and final channel allocation should be recorded in the hardware templates rather than assumed.

See [Hardware inventory](docs/hardware_inventory.md) and the [hardware templates](hardware/).

## Software and AI stack

| Software / service | Purpose |
|---|---|
| Python | Raspberry Pi application and subsystem integration |
| Whisper | Speech recognition |
| Gemini API | AI response generation |
| Nova voice service | Text-to-speech output |
| ESP32 Arduino framework | Embedded firmware development |
| PlatformIO | ESP32 project configuration and build environment |
| Adafruit PCA9685 library | PCA9685 PWM driver interface |
| ROS 2 | Robot middleware, description and future control integration |

### Raspberry Pi Python dependencies

The repository includes separate dependency files for the core application and selected integrations:

- `requirements.txt` — common Python dependencies.
- `requirements-gemini.txt` — Gemini integration dependency.
- `requirements-whisper-api.txt` — hosted Whisper API client dependency.
- `requirements-audio.txt` — audio input/output dependencies.

Local speech recognition, camera support and other optional features may require additional system packages and hardware-specific setup.

## Repository structure

```text
InMoov_AI_Humanoid/
├── README.md
├── .gitignore
├── docs/
│   ├── project_status.md
│   ├── hardware_inventory.md
│   ├── servo_calibration.md
│   ├── api_configuration.md
│   └── assembly_photos.md
├── hardware/
│   ├── bom_template.csv
│   └── servo_channel_map_template.csv
├── firmware/
│   └── esp32/
│       ├── platformio.ini
│       └── src/
│           ├── main.cpp
│           ├── servo_driver.h
│           ├── servo_driver.cpp
│           ├── joint.h
│           ├── joint.cpp
│           └── joint_config.h
├── raspberry_pi/
│   ├── app.py
│   ├── .env.example
│   ├── requirements.txt
│   ├── requirements-gemini.txt
│   ├── requirements-whisper-api.txt
│   └── requirements-audio.txt
└── ros2/
    └── README.md
```

## Getting started

### 1. Clone the repository

```bash
git clone https://github.com/varsha1290/InMoov_AI_Humanoid.git
cd InMoov_AI_Humanoid
```

### 2. ESP32 firmware environment

1. Install Visual Studio Code and the PlatformIO extension, or install PlatformIO Core.
2. Open the `firmware/esp32/` folder as a PlatformIO project.
3. Check that the board identifier in `platformio.ini` matches the ESP32 board being used.
4. Verify the PCA9685 I2C wiring and address.
5. Build the firmware before connecting the mechanism.
6. Calibrate one unloaded servo at a time before enabling additional joints.

The current PlatformIO configuration uses the generic `esp32dev` target. Select the correct target if the physical ESP32 board differs.

### 3. Raspberry Pi Python environment

```bash
cd raspberry_pi
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
python -m pip install -r requirements.txt
cp .env.example .env
```

Install the Gemini dependency when that integration is being configured:

```bash
python -m pip install -r requirements-gemini.txt
```

The `app.py` file is the application entry point for further development. Configure and test each service independently before connecting the complete voice-interaction pipeline.

## Servo control and calibration

The ESP32 firmware uses a PCA9685 driver and a configurable joint table.

The example joint configuration contains sample entries such as:

- Neck pan and neck tilt
- Jaw
- Eye pan and eye tilt
- Left and right hand movement
- An example finger joint

These names are examples for structuring the controller. Confirm the physical joint names and PCA9685 channel mapping for the assembled robot.

### Calibration principles

- The PCA9685 generates PWM signals; it does not read the internal position sensor of a standard hobby servo.
- A hobby servo generally uses its own internal feedback circuit to control its output shaft.
- A commanded angle does not independently confirm the actual mechanical joint angle.
- Pulse limits, centre positions and mechanical travel vary by servo model and individual unit.
- Do not force a servo against a mechanical stop.
- Keep the initial movement range narrow and test without mechanical load.

Record the centre pulse, safe minimum and maximum pulse, movement direction, joint range, supply voltage and PCA9685 channel for each servo. Use [Servo calibration](docs/servo_calibration.md) and [servo channel map template](hardware/servo_channel_map_template.csv).

All example joints in the firmware configuration are disabled by default. Only enable a joint after its wiring and safe movement range have been verified.

## ESP32 serial command interface

The firmware includes a basic serial command structure:

| Command | Function |
|---|---|
| `PING` | Request a connection response |
| `HELP` | Display the available command summary |
| `STATUS` | Display controller and joint configuration information |
| `MOVE,<joint>,<degrees>` | Request movement of an enabled joint |
| `STOP` | Disable PCA9685 PWM outputs |

Example:

```text
MOVE,neck_pan,10
```

This command format is an early control interface. It should be extended with input validation, command timeouts, communication-loss handling and movement limits before regular robot operation.

**Important:** the `STOP` command is not a safety-rated emergency stop. Provide a separate physical method to disconnect servo power during testing.

## AI service configuration

API credentials are kept outside the source code. The `.env.example` file provides blank configuration fields for the integrations.

Configuration keys include:

- `GEMINI_API_KEY`
- `OPENAI_API_KEY`
- `WHISPER_MODE`
- `NOVA_TTS_API_KEY`
- `NOVA_TTS_BASE_URL`
- `NOVA_TTS_MODEL`
- `ESP32_SERIAL_PORT`
- `ESP32_BAUDRATE`

The exact Nova voice provider, endpoint and model must match the service selected for the project. Keep real API keys only in the local `.env` file. Never commit credentials to GitHub.

See [API configuration](docs/api_configuration.md).

## ROS 2 integration

ROS 2 can provide a structured way to represent and control the humanoid robot. A future integration can include:

1. A URDF/Xacro robot description.
2. Link and joint definitions based on the real assembly.
3. Joint axes, origins and movement limits.
4. Visual and collision meshes.
5. RViz visualization.
6. A hardware interface connecting ROS 2 commands to the ESP32.
7. Simulation and motion-control integration.

The robot description should use measured geometry and verified joint limits. Do not estimate link dimensions, masses or inertial values if they are intended for simulation or control.

See [ROS 2 project notes](ros2/README.md).

## Electrical and mechanical safety

Servo systems can draw substantial peak current, especially when several joints move together.

- Use a regulated servo power supply sized for the actual servo load.
- Do not power servos from the Raspberry Pi GPIO or ESP32 3.3 V pin.
- Verify each servo's rated voltage and current using its datasheet.
- Confirm power polarity, common signal ground and wiring before switching on.
- Test one servo at a time with the mechanism unloaded.
- Secure the robot and keep fingers clear of gears, linkages and pinch points.
- Provide a physical servo-power disconnect.
- Test reset and communication-loss behavior.
- Do not let an AI response directly issue unrestricted servo commands. Route movement through a validated command layer with joint limits and an allowlist.

## Development roadmap

| Stage | Engineering task | Expected deliverable |
|---|---|---|
| 1 | Complete the component inventory | Bill of materials |
| 2 | Verify wiring and PCA9685 channels | Wiring diagram and channel map |
| 3 | Calibrate every servo and joint | Servo calibration records |
| 4 | Build and test ESP32 firmware | Firmware build and bench-test records |
| 5 | Establish Raspberry Pi–ESP32 communication | Serial communication test |
| 6 | Integrate microphone and Whisper | Speech recognition test |
| 7 | Integrate Gemini response generation | AI response test |
| 8 | Integrate Nova voice output | Speech playback test |
| 9 | Add controlled robot behaviors | Validated movement routines |
| 10 | Develop ROS 2 description and integration | URDF/Xacro and RViz validation |
| 11 | Perform integrated testing | System test documentation |

## Contributing

When making changes to this project:

1. Keep hardware-specific values in configuration files or documented tables.
2. Never commit API keys or private credentials.
3. Record wiring and channel changes in the relevant documentation.
4. Keep movement limits explicit and review them before enabling a joint.
5. Include reproducible build or test instructions when adding software.
6. Update the README when the architecture or setup process changes.

---

## Project repository

[**varsha1290/InMoov_AI_Humanoid**](https://github.com/varsha1290/InMoov_AI_Humanoid)

The objective is to develop the robot one subsystem at a time, validate the mechanical and electrical interfaces, and then integrate voice interaction, AI and ROS 2 capabilities.
