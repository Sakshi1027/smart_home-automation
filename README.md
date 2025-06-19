# Smart Home Automation System

This project implements a low-cost, IoT-based smart home automation system using ESP32 and ESP8266 microcontrollers. The system integrates various sensors and actuators to monitor and control household devices remotely via the Blynk IoT platform. It enhances security, energy efficiency, and user convenience through real-time environmental monitoring and automation.

## Features
- **Intrusion Detection**: Ultrasonic sensor triggers a buzzer when an object is detected within a specified range.
- **Motion Detection**: IR sensor detects motion to turn on/off an LED, controllable via Blynk.
- **Light Intensity Control**: LDR sensor measures ambient light intensity to automatically control a light.
- **Fan Control**: DC fan can be turned on/off remotely using Blynk.
- **Water Pump Automation**: Ultrasonic sensor monitors water level to control a pump, turning it off when the level is high.
- **Real-Time Monitoring**: Sensor data (ultrasonic distance, IR motion, LDR intensity, water level) is displayed on the Blynk app.
- **WiFi Connectivity**: ESP32/ESP8266 connects to the internet for remote access via Blynk.

## Hardware Requirements
- ESP32 or ESP8266 microcontroller
- Ultrasonic sensor (HC-SR04)
- IR sensor
- LDR (Light Dependent Resistor)
- LED
- Buzzer
- DC fan
- Water pump
- Relay module
- Jumper wires and breadboard

## Software Requirements
- Arduino IDE
- Blynk IoT platform (mobile app and server)
- ESP32/ESP8266 board support package for Arduino IDE
- Libraries: Blynk, ESP8266WiFi (for ESP8266), WiFi (for ESP32)

## Project Structure
- `final_ir_ultra.ino`: Code for intrusion detection (ultrasonic + buzzer) and motion detection (IR + LED) with Blynk integration.
- `dc_dht_ldr_blynk.ino`: Code for light intensity control (LDR + light) and DC fan control with Blynk integration.
- `pump_blynk.ino`: Code for water pump control based on water level (ultrasonic) with Blynk integration.

## Setup Instructions
1. **Hardware Setup**:
   - Connect the ultrasonic sensor, IR sensor, LED, buzzer, LDR, DC fan, and water pump to the ESP32/ESP8266 as per the pin configurations in the code.
   - Use a relay module to control high-power devices like the pump and fan.
   - Ensure stable power supply for all components.

2. **Software Setup**:
   - Install Arduino IDE and add ESP32/ESP8266 board support.
   - Install required libraries (Blynk, WiFi) via Arduino Library Manager.
   - Sign up on the Blynk platform, create a new project, and obtain the authentication token.
   - Update the WiFi credentials (SSID, password) and Blynk auth token in each `.ino` file.
   - Upload the respective `.ino` files to the ESP32/ESP8266 using Arduino IDE.

3. **Blynk Configuration**:
   - In the Blynk app, add widgets to display sensor data (e.g., gauges for distance, intensity, water level) and control devices (e.g., buttons for LED, fan, pump).
   - Map the widgets to the virtual pins defined in the code.

4. **Testing**:
   - Power on the system and connect to WiFi.
   - Monitor sensor data and control devices via the Blynk app.
   - Verify functionality (e.g., buzzer on intrusion, LED on motion, pump off at high water level).

## Future Enhancements
- Add voice control using Alexa or Google Assistant.
- Integrate cloud-based data logging for historical analysis.
- Enhance security with camera integration and real-time alerts.

## Contributing
Contributions are welcome! Please fork the repository, make changes, and submit a pull request.

