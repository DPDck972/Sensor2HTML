#ifndef WEB_HANDLERS_H
#define WEB_HANDLERS_H

#include <ESP8266WebServer.h>
#include "Config.h"
#include "HtmlPage.h"

// ========================================
// Global Variables for Data
// ========================================
extern String sensorValue;
extern unsigned long lastDataTime;
extern uint32_t postCounter;

// ========================================
// Web Server Instance
// ========================================
extern ESP8266WebServer server;

// ========================================
// HTTP Request Handlers
// ========================================

/**
 * Handle root path - serves HTML page
 */
void handleRoot() {
  server.send(200, "text/html", HTML_PAGE);
}

/**
 * Handle GET /data - returns current sensor data as JSON
 */
void handleGetData() {
  String json = "{";
  json += "\"value\":\"" + sensorValue + "\",";
  json += "\"time\":" + String(lastDataTime / 1000) + ",";
  json += "\"counter\":" + String(postCounter);
  json += "}";
  server.send(200, "application/json", json);
}

/**
 * Handle POST /api/sensor - receives data from remote sensor
 * Expected format: plain text, JSON, or form data
 */
void handlePostData() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    
    // Store the received data
    sensorValue = body;
    lastDataTime = millis();
    
    // Increment post counter
    postCounter++;
    
    // Log to serial
    Serial.print("[POST #");
    Serial.print(postCounter);
    Serial.print("] Received data: ");
    Serial.println(body);
    
    // Send success response
    server.send(200, "application/json", "{\"status\":\"received\",\"count\":" + String(postCounter) + "}");
  } else {
    Serial.println("[POST] No data received");
    server.send(400, "application/json", "{\"error\":\"No data received\"}");
  }
}

/**
 * Handle 404 errors
 */
void handleNotFound() {
  String message = "404 - File Not Found\n\n";
  message += "URI: " + server.uri() + "\n";
  message += "Method: " + String((server.method() == HTTP_GET) ? "GET" : "POST") + "\n";
  
  Serial.print("[404] Not found: ");
  Serial.println(server.uri());
  
  server.send(404, "text/plain", message);
}

/**
 * Setup all web server routes
 */
void setupWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleGetData);
  server.on("/api/sensor", HTTP_POST, handlePostData);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started on port " + String(SERVER_PORT));
}

#endif // WEB_HANDLERS_H
