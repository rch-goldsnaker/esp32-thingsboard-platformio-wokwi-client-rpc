#if defined(ESP8266)
#include <ESP8266WiFi.h>
#define THINGSBOARD_ENABLE_PROGMEM 0
#elif defined(ESP32) || defined(RASPBERRYPI_PICO) || defined(RASPBERRYPI_PICO_W)
#include <WiFi.h>
#endif

#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>

// WiFi and ThingsBoard configuration
constexpr char WIFI_SSID[] = "Wokwi-GUEST";
constexpr char WIFI_PASSWORD[] = "";
constexpr char TOKEN[] = "iAJldkfvCKwcvwUQsHnj";
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud";
constexpr uint16_t THINGSBOARD_PORT = 1883U;
constexpr uint32_t MAX_MESSAGE_SIZE = 256U;
constexpr uint32_t SERIAL_DEBUG_BAUD = 115200U;

// Telemetry interval (send data every 3 seconds)
constexpr uint32_t TELEMETRY_SEND_INTERVAL = 3000U;

WiFiClient wifiClient;
Arduino_MQTT_Client mqttClient(wifiClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);

uint32_t previousDataSend;

void InitWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

const bool reconnect() {
  const wl_status_t status = WiFi.status();
  if (status == WL_CONNECTED) {
    return true;
  }
  InitWiFi();
  return true;
}

// Function to generate random temperature values
float getRandomTemperature() {
  // Generate random temperature between 18.0 and 35.0 degrees Celsius
  return random(180, 351) / 10.0; // random(180, 351) gives 180-350, divided by 10 gives 18.0-35.0
}

void setup() {
  Serial.begin(SERIAL_DEBUG_BAUD);
  
  // Initialize random seed
  randomSeed(analogRead(0));
  
  Serial.println("ESP32 ThingsBoard Telemetry - Simple Version");
  
  delay(1000);
  InitWiFi();
}

void loop() {
  delay(100);

  // Check WiFi connection
  if (!reconnect()) {
    return;
  }

  // Connect to ThingsBoard if not connected
  if (!tb.connected()) {
    Serial.print("Connecting to ThingsBoard: ");
    Serial.println(THINGSBOARD_SERVER);
    
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
      Serial.println("Failed to connect to ThingsBoard!");
      return;
    }
    
    Serial.println("Connected to ThingsBoard successfully!");
  }

  // Send telemetry data at regular intervals
  if (millis() - previousDataSend > TELEMETRY_SEND_INTERVAL) {
    previousDataSend = millis();
    
    // Generate and send random temperature
    float temperature = getRandomTemperature();
    
    Serial.print("Sending telemetry - Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
    
    // Send temperature telemetry to ThingsBoard
    tb.sendTelemetryData("temperature", temperature);
  }

  // Process ThingsBoard messages
  tb.loop();
}
