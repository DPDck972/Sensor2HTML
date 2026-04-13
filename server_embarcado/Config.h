#ifndef CONFIG_H
#define CONFIG_H

// ========================================
// WiFi Configuration (Dual Mode: STA + AP)
// ========================================
// Station Mode (Connect to external WiFi for dashboard access)
extern const char* EXTERNAL_SSID;               // External WiFi network name
extern const char* EXTERNAL_PASSWORD;           // External WiFi password

// Access Point Mode (Host WiFi for sensor clients)
extern const char* AP_SSID;                     // AP name visible to clients
extern const char* AP_PASSWORD;                 // AP password for clients to connect
extern const char* AP_IP;                       // Default AP gateway IP

// ========================================
// Server Configuration
// ========================================
extern const uint16_t SERVER_PORT;
extern const int WIFI_CONNECT_TIMEOUT;

// ========================================
// Data Configuration
// ========================================
extern const unsigned long DATA_REFRESH_INTERVAL;

// ========================================
// Serial Configuration
// ========================================
extern const long BAUD_RATE;

#endif // CONFIG_H
