// ========================================
// Sensor2HTML ESP8266 Server
// Main sketch file
// ========================================

#include <ESP8266WebServer.h>
#include "Config.h"
#include "WiFiManager.h"
#include "WebHandlers.h"

// ========================================
// Global Configuration Values
// ========================================
const char* EXTERNAL_SSID = "*******";    // External WiFi network name
const char* EXTERNAL_PASSWORD = "*******";     // External WiFi password
const char* AP_SSID = "Sensor2HTML_Server";     // AP name visible to clients
const char* AP_PASSWORD = "sensor2html123";     // AP password for clients to connect
const char* AP_IP = "192.168.4.1";              // Default AP gateway IP
const uint16_t SERVER_PORT = 80;
const int WIFI_CONNECT_TIMEOUT = 20;
const unsigned long DATA_REFRESH_INTERVAL = 5000;
const long BAUD_RATE = 9600;

// ========================================
// Global Variables
// ========================================
String sensorValue = "";
unsigned long lastDataTime = 0;
uint32_t postCounter = 0;
ESP8266WebServer server(SERVER_PORT);

// ========================================
// Setup function
// ========================================
void setup() {
  Serial.begin(BAUD_RATE);
  delay(100);
  
  // Print startup banner
  Serial.println("\n\n");
  Serial.println("================================");
  Serial.println("   Sensor2HTML ESP8266 Server");
  Serial.println("================================");
  Serial.println("Version: 1.0 (Refactored)");
  Serial.println("================================\n");
  
  // Connect to WiFi (dual mode)
  connectToWiFi();
  
  // Setup web server routes
  setupWebServer();
  
  // Print access information
  Serial.println("================================");
  Serial.println("   SERVER READY");
  Serial.println("================================\n");
  Serial.println("Dashboard Access (External Network):");
  Serial.print("  http://");
  Serial.println(WiFi.localIP());
  Serial.println("\nSensor Connections (Hosted AP):");
  Serial.print("  WiFi network: ");
  Serial.println(AP_SSID);
  Serial.print("  Password: ");
  Serial.println(AP_PASSWORD);
  Serial.print("  Server URL: http://");
  Serial.print(WiFi.softAPIP());
  Serial.println("/api/sensor");
  Serial.println("\nPOST counter initialized: 0");
  Serial.println("================================\n");
}

// ========================================
// Main loop
// ========================================
void loop() {
  // Handle incoming client requests
  server.handleClient();
  delay(1);
}
