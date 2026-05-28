ESP8266 NodeMCU (ESP-12E)

Overview

The ESP8266 NodeMCU serves as the main controller of the WiFi Robot Car Radar Detection System. It processes sensor inputs, controls motor movement, and communicates with the Android application over WiFi.

Purpose in the Project

- Acts as the central processing unit.
- Hosts the WiFi server for remote control.
- Processes ultrasonic sensor data.
- Controls motors and servo motor.

Technical Specifications

ParameterDetails| 
Operating Voltage| 3.3V
WiFi Standard| IEEE 802.11 b/g/n
Flash Memory| 4MB
GPIO Pins| Multiple Digital I/O
Microcontroller| Tensilica L106

Pin Connections

Component| NodeMCU Pin
HC-SR04 Trigger| D5
HC-SR04 Echo| D6
Servo Signal| D4
L298N IN1| D1
L298N IN2| D2

Advantages

- Built-in WiFi support.
- Low cost and power efficient.
- Easy programming using Arduino IDE.

Working Principle

The NodeMCU receives commands from the Android app through WiFi and controls the motors accordingly. It also processes distance data from the ultrasonic sensor to detect obstacles.