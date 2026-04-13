#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <ESP8266WiFi.h>
#include "Config.h"

// ========================================
// WiFi Connection Management (Dual Mode)
// ========================================

void connectToWiFi() {
  Serial.println("\n========================================");
  Serial.println("Starting WiFi in Dual Mode (STA + AP)...");
  Serial.println("========================================\n");
  
  // Set WiFi mode to dual: Station + Access Point
  WiFi.mode(WIFI_AP_STA);
  
  // ====== START ACCESS POINT ======
  Serial.println("1. Starting Access Point for clients...");
  WiFi.softAP(AP_SSID, AP_PASSWORD, 1, false, 4);
  delay(500);
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("   AP SSID: ");
  Serial.println(AP_SSID);
  Serial.print("   AP Password: ");
  Serial.println(AP_PASSWORD);
  Serial.print("   AP IP: ");
  Serial.println(apIP);
  
  // ====== CONNECT TO EXTERNAL WiFi ======
  Serial.println("\n2. Connecting to external WiFi...");
  Serial.print("   Connecting to: ");
  Serial.println(EXTERNAL_SSID);
  
  WiFi.begin(EXTERNAL_SSID, EXTERNAL_PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("   ✓ External WiFi connected successfully!");
    Serial.print("   Station IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("   Subnet Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("   Gateway: ");
    Serial.println(WiFi.gatewayIP());
  } else {
    Serial.println("   ✗ Failed to connect to external WiFi");
    Serial.println("   (Continuing with AP-only mode for sensor connections)");
  }
  
  Serial.print("   MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("========================================\n");
}

void printWiFiStatus() {
  Serial.println("\n--- WiFi Status (Dual Mode) ---");
  
  Serial.println("Station Mode (External WiFi):");
  if (WiFi.isConnected()) {
    Serial.print("  SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("  IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("  Signal: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("  Status: Disconnected");
  }
  
  Serial.println("Access Point Mode (For clients):");
  Serial.print("  SSID: ");
  Serial.println(AP_SSID);
  Serial.print("  AP IP: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("  Connected clients: ");
  Serial.println(WiFi.softAPgetStationNum());
  
  Serial.println("-------------------\n");
}

#endif // WIFI_MANAGER_H
