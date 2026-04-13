// ========================================
// Sensor2HTML ESP8266 Server
// Main sketch file
// ========================================

#include <ESP8266WebServer.h>
#include "Config.h"
#include "WiFiManager.h"
#include "WebHandlers.h"

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
  
  // Connect to WiFi
  connectToWiFi();
  
  // Setup web server routes
  setupWebServer();
  
  // Print access information
  Serial.print("Access the server at: http://");
  Serial.println(WiFi.localIP());
  Serial.println("\nServer ready for connections!");
  Serial.println("POST counter initialized: 0\n");
}

// ========================================
// Main loop
// ========================================
void loop() {
  // Handle incoming client requests
  server.handleClient();
  delay(1);
}
