#include <WiFi.h>
#include <Arduino_MQTT_Client.h>
#include <ThingsBoard.h>
#include <Client_Side_RPC.h>
#include <RPC_Request_Callback.h>

// WiFi Configuration
constexpr char WIFI_SSID[] = "Wokwi-GUEST";
constexpr char WIFI_PASSWORD[] = "";

// ThingsBoard Configuration
constexpr char TOKEN[] = "qrXSMGvV47EJHBq4BkDm";
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud";
constexpr uint16_t THINGSBOARD_PORT = 1883U;

// ThingsBoard Objects
WiFiClient wifiClient;
Arduino_MQTT_Client mqttClient(wifiClient);
Client_Side_RPC<5U> client_rpc;

const std::array<IAPI_Implementation *, 1U> apis = {
    &client_rpc
};

ThingsBoard tb(mqttClient, 1024U, Default_Max_Stack_Size, apis);

// Client-side RPC Variables
unsigned long lastRpcCall = 0;
const unsigned long RPC_INTERVAL = 10000; // Call RPC every 10 seconds
bool rpcInProgress = false;

// RPC Callback Functions
void rpcResponseCallback(const JsonDocument &data) {
  Serial.println("=== CLIENT-SIDE RPC RESPONSE RECEIVED ===");
  
  if (data.is<long long>()) {
    long long serverTime = data.as<long long>();
    Serial.print("Server current time: ");
    Serial.println(serverTime);
  } else if (data.is<const char*>()) {
    Serial.print("Server response: ");
    Serial.println(data.as<const char*>());
  } else {
    Serial.print("Server response: ");
    String output;
    serializeJson(data, output);
    Serial.println(output);
  }
  
  rpcInProgress = false;
  Serial.println("=========================================");
}

void rpcTimeoutCallback() {
  Serial.println("RPC timeout - no response from server");
  rpcInProgress = false;
}

void makeRpcCall() {
  if (rpcInProgress) {
    Serial.println("RPC call already in progress, skipping...");
    return;
  }
  
  Serial.println("Making client-side RPC call: getCurrentTime");
  
  // Create RPC callback with 10 seconds timeout
  RPC_Request_Callback callback("getCurrentTime", rpcResponseCallback, nullptr, 10000U * 1000U, rpcTimeoutCallback);
  
  // Make the RPC call
  if (client_rpc.RPC_Request(callback)) {
    Serial.println("RPC call sent successfully");
    rpcInProgress = true;
  } else {
    Serial.println("Failed to send RPC call");
  }
}

// WiFi Functions
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

// Arduino Setup and Main Loop
void setup() {
  Serial.begin(115200);
  InitWiFi();
}

void loop() {
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
  
  // Make RPC call at regular intervals
  if (millis() - lastRpcCall >= RPC_INTERVAL) {
    lastRpcCall = millis();
    makeRpcCall();
  }
  
  // Process ThingsBoard messages
  tb.loop();
  
  delay(200);
}
