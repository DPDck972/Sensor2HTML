#include "sensor.h"
#include "WiFiManager.h"

// ========================================
// Global Configuration Values
// ========================================
const char* SSID = "Sensor2HTML_Server";        // Server's AP SSID
const char* PASSWORD = "sensor2html123";        // Server's AP password
const char* SERVER_IP = "192.168.4.1";          // Server's AP gateway IP
const uint16_t SERVER_PORT = 80;                // Server port
const long BAUD_RATE = 9600;                    // Serial baud rate
const int WIFI_CONNECT_TIMEOUT = 20;            // WiFi connection timeout in seconds

// Sensor na porta GPIO5 (D1 do NodeMCU)
Sensor lineFollower(5);

void setup() {
    Serial.begin(BAUD_RATE);
    delay(1000);
    
    Serial.println("\n\n================================");
    Serial.println("   Sensor2HTML Client (Sensor)");
    Serial.println("================================\n");
    
    // Connect to server's WiFi Access Point
    connectToWiFi();
    
    // Initialize line follower sensor
    lineFollower.Initialize(RISING);
    Serial.println("Line follower sensor initialized on GPIO5 (D1)");
}

void loop() {
    // Verifica se um evento foi detectado
    if (lineFollower.CheckEvent()) {
        Serial.print("Evento detectado! Estado: ");
        Serial.println(lineFollower.GetCurrentState() == HIGH ? "LINHA DETECTADA" : "SEM LINHA");
        
        // Envia para o servidor
        lineFollower.PostEvent();
        
        // Reseta o flag de evento
        lineFollower.ResetEvent();
        
        lineFollower.PrintDebug();
    }
    
    delay(10);
}