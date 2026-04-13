#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h>
#include "config.h"

// ========================================
// WiFi Connection Management
// ========================================

void connectToWiFi() {
  Serial.print("\nConnecting to WiFi: ");
  Serial.println(SSID);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < WIFI_CONNECT_TIMEOUT) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected successfully!");
    Serial.print("Client IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Server IP address: ");
    Serial.println(SERVER_IP);
    Serial.print("MAC address: ");
    Serial.println(WiFi.macAddress());
  } else {
    Serial.println("Failed to connect to WiFi");
    Serial.println("Make sure the server is broadcasting the AP:");
    Serial.print("  SSID: ");
    Serial.println(SSID);
  }
}

void printWiFiStatus() {
  Serial.println("\n--- WiFi Status (Client Mode) ---");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("Client IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal strength: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  Serial.println("-------------------\n");
}

#endif // WIFI_MANAGER_H
