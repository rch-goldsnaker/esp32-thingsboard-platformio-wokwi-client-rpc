# ESP32 ThingsBoard Client-Side RPC

This project demonstrates **Client-Side RPC** (Remote Procedure Call) functionality with ESP32 and **ThingsBoard** IoT platform. The ESP32 makes periodic RPC calls to the server to get the current time, showcasing bidirectional communication, simulated in **Wokwi**.

## 🎯 Features

- **Client-Side RPC**: Device initiates RPC calls to ThingsBoard server
- **Real-time Communication**: Periodic requests every 10 seconds
- **Server Response Handling**: Processes and displays server responses
- **Timeout Management**: Handles cases where server doesn't respond
- **Simple Design**: Clean code focused on RPC functionality
- **Wokwi Simulation**: Complete ESP32 simulation environment

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
- `Client_Side_RPC.h` - Client-side RPC functionality
- `RPC_Request_Callback.h` - RPC callback management

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
const unsigned long RPC_INTERVAL = 10000;                  // RPC call interval (10 seconds)
```

### 3. RPC Configuration
```cpp
const unsigned long RPC_INTERVAL = 10000;      // RPC call interval in milliseconds
const uint64_t RPC_TIMEOUT = 10000U * 1000U;   // RPC timeout in microseconds (10 seconds)
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
cd esp32-thingsboard-platformio-wokwi-client-rpc
```

### 3. ThingsBoard Configuration
1. Create a new device in ThingsBoard
2. Copy the device **Access Token**
3. Replace the `TOKEN` in `main.cpp`
4. Create a **Rule Chain** to handle `getCurrentTime` RPC method

### 4. Server-Side RPC Handler (ThingsBoard Rule Chain)
Add this JavaScript code in a **Script Node** in your Rule Chain:
```javascript
var rpcResponse;
if (msg.method === "getCurrentTime"){
   rpcResponse = new Date().getTime();
} else {
   rpcResponse = "Unknown RPC request method: " + msg.method;  
}
return {msg: rpcResponse, metadata: metadata, msgType: msgType};
```

### 5. Wokwi Simulation
1. Open the project in Wokwi
2. The `diagram.json` contains:
   - ESP32 DevKit C V4
3. Run the simulation
4. Monitor serial port for RPC calls and responses

## 🔧 How It Works

### Client-Side RPC Flow
1. **Connection**: ESP32 connects to WiFi and ThingsBoard
2. **Periodic Calls**: Every 10 seconds, device calls `getCurrentTime` RPC method
3. **Server Processing**: ThingsBoard Rule Chain processes the request and returns current timestamp
4. **Response Handling**: Device receives and displays the server response
5. **Timeout Management**: Handles cases where server doesn't respond within 10 seconds

### Hardware Components
- **ESP32**: Main microcontroller running the RPC client
- **Serial Monitor**: RPC calls, responses and debugging information

## 📊 ThingsBoard Integration

### Client-Side RPC Method
- **getCurrentTime**: Returns current server timestamp in milliseconds

### Device Behavior
- **Automatic Calls**: Makes RPC calls every 10 seconds automatically
- **Response Processing**: Displays server timestamp in serial monitor
- **Error Handling**: Shows timeout messages if server doesn't respond
- **Continuous Operation**: Maintains connection and continues making calls

## 🎮 Usage

1. **Power On**: Device connects to WiFi and ThingsBoard
2. **Automatic RPC**: Device starts making `getCurrentTime` calls every 10 seconds
3. **Monitor Serial**: Watch RPC calls and server responses in serial monitor
4. **Server Response**: See current timestamp from ThingsBoard server
5. **Continuous Operation**: Device maintains connection and continues RPC calls

### Expected Serial Output
```
Making client-side RPC call: getCurrentTime
RPC call sent successfully
=== CLIENT-SIDE RPC RESPONSE RECEIVED ===
Server current time: 1731337845000
=========================================
```

## �📄 License

This project is an open source educational template. Free to use and modify.


## 📞 Support

For questions or issues:
- Create an issue in the repository
- Review [ThingsBoard documentation](https://thingsboard.io/docs/devices-library/esp32-dev-kit-v1/)
- Check [Wokwi documentation](https://docs.wokwi.com/)

## 🔍 Troubleshooting

### Common Issues
- **"Failed to connect to ThingsBoard"**: Check device token and internet connection
- **"RPC timeout - no response from server"**: Rule Chain not configured or server issues
- **"Failed to send RPC call"**: Check MQTT connection and ThingsBoard status
- **"RPC call already in progress"**: Previous call hasn't completed (normal behavior)

### Serial Monitor Messages
- `Making client-side RPC call: getCurrentTime` - RPC call initiated
- `RPC call sent successfully` - Request sent to server
- `Server current time: [timestamp]` - Successful response received
- `Connected to ThingsBoard successfully!` - Device online and ready

---
**Author**: Mirutec - Roger Chung  
**Version**: 1.0 - Client-Side RPC  
**Date**: November 2025
