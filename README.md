<div align="center">

<!-- Animated Banner -->
<img width="100%" src="https://capsule-render.vercel.app/api?type=waving&color=0:00ff88,100:00b4d8&height=200&section=header&text=WiFi%20Radar%20Bot&fontSize=52&fontColor=ffffff&fontAlignY=38&desc=ESP8266%20%7C%20Ultrasonic%20Radar%20%7C%20Android%20Control&descAlignY=58&descSize=18&animation=fadeIn"/>

<br/>

<p>
  <img src="https://img.shields.io/badge/Platform-ESP8266%20NodeMCU-00b4d8?style=for-the-badge&logo=espressif&logoColor=white"/>
  <img src="https://img.shields.io/badge/Android-Kotlin-7F52FF?style=for-the-badge&logo=kotlin&logoColor=white"/>
  <img src="https://img.shields.io/badge/Protocol-HTTP%20over%20WiFi-00ff88?style=for-the-badge&logo=wifi&logoColor=white"/>
  <img src="https://img.shields.io/badge/Radar-HC--SR04%20+%20SG90-ff6b35?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/IDE-Arduino%20+%20Android%20Studio-3DDC84?style=for-the-badge&logo=android-studio&logoColor=white"/>
</p>

<br/>

> **A smart robotic system combining embedded IoT, real-time radar scanning, and a custom Android application — all communicating over WiFi.**

<br/>

</div>

---

## 🧭 Table of Contents

- [📖 Project Overview](#-project-overview)
- [✨ Key Features](#-key-features)
- [🏗️ System Architecture](#️-system-architecture)
- [🔧 Hardware Requirements](#-hardware-requirements)
- [💻 Software Stack](#-software-stack)
- [📡 How It Works](#-how-it-works)
- [📱 Android Application](#-android-application)
- [🌐 Radar Web Interface](#-radar-web-interface)
- [⚙️ Setup & Installation](#️-setup--installation)
- [🗂️ Project Structure](#️-project-structure)
- [🛡️ Safety Features](#️-safety-features)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)

---

## 📖 Project Overview

The **WiFi Controlled Radar Detection System** is an embedded IoT project that integrates a remotely operated robotic car with real-time ultrasonic radar scanning. Built around the **ESP8266 NodeMCU**, the robot connects to a local WiFi network and hosts an HTTP server, receiving directional and speed commands from a **custom Kotlin Android application** via IP address.

The radar subsystem uses an **HC-SR04 ultrasonic sensor** mounted on an **SG90 servo motor**, continuously sweeping 0°–180° and sending live angle-distance data to both a **canvas-based radar web interface** (served by the ESP8266) and the Android app — creating a complete, interactive, smart robotic platform.

```
┌─────────────────────────────────────────────────────────────┐
│                    SYSTEM OVERVIEW                          │
│                                                             │
│   📱 Android App  ──── WiFi HTTP ────►  🤖 ESP8266 Bot     │
│        │                                      │            │
│        │◄───── Radar Data (angle/dist) ────────┤            │
│        │                                      │            │
│   🌐 Web Radar  ◄── HTML Canvas Page ──────────┘            │
└─────────────────────────────────────────────────────────────┘
```

---

## ✨ Key Features

| Feature | Description |
|--------|-------------|
| 🎮 **Remote Control** | Directional control (Forward / Backward / Left / Right / Stop) via Android app |
| 📡 **Live Radar Scan** | Ultrasonic sensor on servo sweeps 0°–180°, streaming real-time distance data |
| 🌐 **Web Radar Interface** | ESP8266-hosted HTML5 canvas page visualizing radar sweeps in real-time |
| ⚡ **Speed Control** | Variable motor speed adjustable from the Android application |
| 🔊 **Buzzer Siren** | Triggerable buzzer/siren from the app for alerts |
| 🛡️ **Auto-Stop Safety** | Robot halts automatically if no command is received within a timeout window |
| 📶 **HTTP over WiFi** | Lightweight command protocol over ESP8266-hosted HTTP server |
| 📲 **Custom Android App** | Kotlin-built controller app with intuitive UI for control + radar view |

---

## 🏗️ System Architecture

<img width="1060" height="678" alt="image" src="https://github.com/user-attachments/assets/a4a14a36-521b-407f-b495-d9178fe3f11f" />

---

## 🔧 Hardware Requirements

| # | Component | Specification |
|---|-----------|---------------|
| 1 | **ESP8266 NodeMCU** | ESP-12E Module |
| 2 | **Ultrasonic Sensor** | HC-SR04 |
| 3 | **Servo Motor** | SG90 Micro Servo (0–180°) |
| 4 | **Motor Driver** | L298N Dual H-Bridge Module |
| 5 | **DC Geared Motors** | BO Motors – 100 RPM |
| 6 | **Buzzer** | Active Buzzer Module |
| 7 | **Robot Chassis** | 2WD Acrylic/Plastic Chassis Kit |
| 8 | **Wheels** | Standard BO Motor Wheels |
| 9 | **Power Supply** | 7.4V Li-ion Battery Pack (18650 Cells) |

### 🔌 Pin Connections (ESP8266 NodeMCU)

```
ESP8266 Pin  │  Connected To
─────────────┼──────────────────────────────
D1 (GPIO5)   │  L298N – IN1 (Motor A)
D2 (GPIO4)   │  L298N – IN2 (Motor A)
D3 (GPIO0)   │  L298N – IN3 (Motor B)
D4 (GPIO2)   │  L298N – IN4 (Motor B)
D5 (GPIO14)  │  SG90 Servo Signal
D6 (GPIO12)  │  HC-SR04 Trigger
D7 (GPIO13)  │  HC-SR04 Echo
D8 (GPIO15)  │  Active Buzzer (+)
3.3V / GND   │  Sensor Power
VIN          │  7.4V (via voltage regulator)
```
<img width="842" height="542" alt="image" src="https://github.com/user-attachments/assets/3116d835-b472-4789-8d1c-9377a6dcce0f" />

---

## 💻 Software Stack

<table>
<tr>
<td>

**Embedded / Firmware**
- 🛠️ Arduino IDE `1.8.x / 2.x`
- 📦 ESP8266 Board Package
- 💾 Embedded C/C++ (Arduino Framework)
- 📚 Libraries: `ESP8266WiFi`, `ESP8266WebServer`, `Servo`

</td>
<td>

**Mobile Application**
- 📱 Android Studio (Latest Stable)
- 🟣 Kotlin (Primary Language)
- 🌐 OkHttp / HttpURLConnection
- 🎨 Android Jetpack Components

</td>
</tr>
<tr>
<td>

**Web Interface (Radar)**
- 🌐 HTML5 Canvas API
- 🎨 CSS3 (Animations & Styling)
- ⚡ JavaScript (Radar Visualization)
- 📡 Served directly by ESP8266

</td>
<td>

**Communication**
- 📶 WiFi (IEEE 802.11 b/g/n)
- 🔗 HTTP GET/POST over local network
- 🔄 Real-time polling for radar data
- 🏠 ESP8266 as HTTP Server

</td>
</tr>
</table>

---

## 📡 How It Works

### 1. WiFi & HTTP Server Initialization
The ESP8266 connects to a configured WiFi network on boot and starts an HTTP server. The device IP is displayed on the Serial monitor and used by the Android app to send commands.

### 2. Robot Control Flow
```
Android App  ──►  HTTP GET /forward  ──►  ESP8266  ──►  L298N  ──►  Motors
             ──►  HTTP GET /backward ──►     │
             ──►  HTTP GET /left     ──►     │
             ──►  HTTP GET /right    ──►     │
             ──►  HTTP GET /stop     ──►     │
             ──►  HTTP GET /speed?val=X ──►  │
             ──►  HTTP GET /siren    ──────────►  Buzzer
```

### 3. Radar Scanning Loop
```
Servo sweeps 0° → 180° → 0°  (continuous)
    │
    ├── At each degree: HC-SR04 fires ultrasonic pulse
    │       └── Measures echo return time → calculates distance (cm)
    │
    └── Sends: angle, distance to:
            ├── Web client (via HTTP endpoint /radar)
            └── Android app (via polling)
```

### 4. Radar Visualization
The HTML5 canvas-based radar page fetches angle/distance data from `/radar` endpoint and renders a live sweeping radar display with detected objects plotted as green dots.

---

## 📱 Android Application

The custom Kotlin app provides:

- **Directional Control Pad** — Touch buttons for Forward / Backward / Left / Right / Stop
- **Speed Control Slider** — Adjusts PWM-based motor speed in real-time
- **Siren Toggle** — Activates/deactivates the buzzer remotely
- **Embedded Radar View** — WebView loading the ESP8266-hosted radar HTML page
- **IP Configuration** — Input field to set the ESP8266's IP address

```kotlin
// Example HTTP command structure
val url = "http://$espIpAddress/forward"
val request = Request.Builder().url(url).build()
client.newCall(request).enqueue(callback)
```

---

## 🌐 Radar Web Interface

The radar visualization page is served directly from ESP8266's flash memory. It uses:

- **HTML5 `<canvas>`** for the sweeping radar arc
- **JavaScript `setInterval()`** to poll `/radar` endpoint for live data
- **CSS3** for the dark-themed, green-on-black radar aesthetic

<img width="811" height="516" alt="image" src="https://github.com/user-attachments/assets/c4cd4c99-d8b2-40de-bf06-1c0c865a338f" />


---

## ⚙️ Setup & Installation

### Step 1: Clone the Repository
```bash
git clone https://github.com/lokeshtekade77-source/ESP8266-WiFi-Robot-Car-with-Radar-Detection-System
cd ESP8266-WiFi-Robot-Car-with-Radar-Detection-System
```

### Step 2: Flash ESP8266 Firmware

1. Open **Arduino IDE** and install the **ESP8266 Board Package**
   - Go to `File > Preferences > Additional Board Manager URLs`
   - Add: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - Install via `Tools > Board > Board Manager > ESP8266`

2. Open `firmware/radar_bot.ino`

3. Configure your WiFi credentials:
```cpp
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

4. Select board: `Tools > Board > NodeMCU 1.0 (ESP-12E Module)`

5. Upload the sketch. Note the IP address from Serial Monitor.

### Step 3: Build Android App

1. Open the `android/` folder in **Android Studio**
2. Sync Gradle dependencies
3. Build and run on your Android device
4. Enter the ESP8266 IP address in the app settings
5. Start controlling! 🚀

---

## 🗂️ Project Structure

```
wifi-radar-bot/
│
├── 📁 firmware/
│   ├── radar_bot.ino          # Main ESP8266 sketch
│   ├── motor_control.ino      # Motor driver logic
│   ├── radar_scan.ino         # Servo + ultrasonic scan
│   └── web_server.ino         # HTTP server & radar page
│
├── 📁 android/
│   ├── app/
│   │   ├── src/main/
│   │   │   ├── java/.../
│   │   │   │   ├── MainActivity.kt      # Main controller UI
│   │   │   │   ├── RadarActivity.kt     # Radar WebView
│   │   │   │   └── HttpHelper.kt        # HTTP communication
│   │   │   └── res/layout/
│   │   │       ├── activity_main.xml
│   │   │       └── activity_radar.xml
│   └── build.gradle
│
├── 📁 web/
│   └── radar.html             # Standalone radar visualizer
│
├── 📁 hardware/
│   ├── schematic.png          # Circuit diagram
│   └── wiring_diagram.pdf     # Detailed wiring guide
│
├── 📁 docs/
│   └── project_report.pdf
│
└── README.md
```

---

## 🛡️ Safety Features

- ⏱️ **Watchdog Auto-Stop** — If no HTTP command is received within `2000ms`, motors are automatically halted to prevent runaway behavior
- 🔄 **Servo Safe Sweep** — Servo angle is clamped to `0°–180°` to prevent mechanical damage
- 🔋 **Battery Monitoring** — Optional ADC-based voltage check with low-battery serial warnings
- 📶 **WiFi Reconnect** — Automatic reconnection logic if the WiFi connection drops during operation

---

## 🤝 Contributing

Contributions are welcome! Feel free to:

1. 🍴 Fork the repository
2. 🌿 Create a feature branch (`git checkout -b feature/your-feature`)
3. 💾 Commit your changes (`git commit -m 'Add amazing feature'`)
4. 📤 Push to the branch (`git push origin feature/your-feature`)
5. 🔁 Open a Pull Request

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

<div align="center">

**Built with ❤️ using ESP8266, Kotlin & Arduino**

<img width="100%" src="https://capsule-render.vercel.app/api?type=waving&color=0:00b4d8,100:00ff88&height=100&section=footer"/>

</div>
