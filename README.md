# ESP32 ThingsBoard Simple Telemetry

This project is a **simple template** for ESP32 that sends random temperature telemetry data to **ThingsBoard** IoT platform, simulated in **Wokwi**.

## 📋 Description

The project implements:
- 📡 Automatic WiFi connection
- 📊 Random temperature telemetry sending every 3 seconds
- 🌐 MQTT communication with ThingsBoard
- 📱 Complete simulation in Wokwi

## 🔧 Hardware Used

### Physical Components
- **ESP32 DevKit C v4** - Main microcontroller only

## 📚 Dependencies and Libraries

### PlatformIO Libraries
```ini
lib_deps = 
    thingsboard/ThingsBoard@0.14.0                    # ThingsBoard MQTT Client
    arduino-libraries/ArduinoHttpClient@^0.6.1        # HTTP Client
    arduino-libraries/ArduinoMqttClient@^0.1.8        # MQTT Client
    knolleary/PubSubClient@^2.8                       # MQTT Pub/Sub
```

### System Libraries
- `WiFi.h` - WiFi connectivity (ESP32)
- `Arduino_MQTT_Client.h` - MQTT client for ThingsBoard

## ⚙️ Configuration

### 1. WiFi Credentials
```cpp
constexpr char WIFI_SSID[] = "Wokwi-GUEST";      // WiFi Network
constexpr char WIFI_PASSWORD[] = "";             // Password (empty for Wokwi)
```

### 2. ThingsBoard Configuration
```cpp
constexpr char TOKEN[] = "xxxxxxxxxxxxxxxxxxxx";           // Device token (from ThingsBoard)
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud"; // ThingsBoard server
constexpr uint16_t THINGSBOARD_PORT = 1883U;               // MQTT port
```

## 🚀 Installation and Usage

### 1. Prerequisites
- [PlatformIO IDE](https://platformio.org/platformio-ide) or [PlatformIO Core](https://platformio.org/install/cli)
- Account on [ThingsBoard Cloud](https://thingsboard.cloud/) or local server
- Access to [Wokwi](https://wokwi.com/) for simulation

### 2. Project Setup
```bash
# Clone the repository
git clone <repository-url>
cd esp32-thingsboard-platformio-wokwi-telemetry

# Install dependencies
pio lib install

# Build the project
pio run
```

### 3. ThingsBoard Configuration
1. Create a new device in ThingsBoard
2. Copy the device **Access Token**
3. Replace the `TOKEN` in `main.cpp`
4. Configure dashboard to visualize:
   - `temperature` (°C) - Random values between 18.0 and 35.0°C

### 4. Wokwi Simulation
1. Open the project in Wokwi
2. The `diagram.json` file contains hardware configuration
3. Run the simulation
4. Monitor serial port for debugging

## 📊 Features

### Automatic Telemetry (every 3s)
- **temperature**: Random temperature values between 18.0°C and 35.0°C

## 🏗️ Project Structure

```
esp32-thingsboard-platformio-wokwi-telemetry/
├── src/
│   └── main.cpp             # Main code
├── include/
│   └── README               # Custom headers
├── lib/
│   └── README               # Local libraries
├── test/
│   └── README               # Unit tests
├── platformio.ini           # PlatformIO configuration
├── wokwi.toml               # Wokwi configuration
├── diagram.json             # Wokwi circuit diagram (ESP32 only)
└── README.md                
```

## 🔍 Monitoring and Debug

### Serial Monitor
```bash
pio device monitor --baud 115200
```

### Main Debug Messages
- WiFi connection: `"WiFi connected!"`
- ThingsBoard connection: `"Connected to ThingsBoard successfully!"`
- Telemetry sending: `"Sending telemetry - Temperature: XX.X°C"`

## 🎛️ Customization

### Change Telemetry Interval
```cpp
constexpr uint32_t TELEMETRY_SEND_INTERVAL = 3000U;  // Change value in ms
```

## 🐛 Troubleshooting

### Common Issues

1. **WiFi connection fails**
   - Verify SSID and password
   - In Wokwi use "Wokwi-GUEST" without password

2. **ThingsBoard connection fails**
   - Verify device token in `main.cpp`
   - Check network connectivity
   - Review firewall on port 1883

3. **Random temperature not generating**
   - Check if `randomSeed(analogRead(0))` is called in setup()
   - Verify telemetry sending interval

## 📄 License

This project is an open source educational template. Free to use and modify.

## 🤝 Contributions

Contributions are welcome! Please:
1. Fork the project
2. Create a branch for your feature
3. Commit your changes
4. Open a Pull Request

## 📞 Support

For questions or issues:
- Create an issue in the repository
- Review [ThingsBoard documentation](https://thingsboard.io/docs/devices-library/esp32-dev-kit-v1/)
- Check [Wokwi documentation](https://docs.wokwi.com/)

---
**Author**: Mirutec - Roger Chung  
**Version**: 2.0 - Simple Telemetry  
**Date**: November 2025