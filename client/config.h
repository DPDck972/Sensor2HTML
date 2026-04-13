#ifndef CONFIG_H
#define CONFIG_H

// ========================================
// WiFi Configuration (Client Mode)
// ========================================
extern const char* SSID;                        // Server's AP SSID
extern const char* PASSWORD;                    // Server's AP password
extern const char* SERVER_IP;                   // Server's AP gateway IP
extern const uint16_t SERVER_PORT;              // Server port

// ========================================
// Serial Configuration
// ========================================
extern const long BAUD_RATE;

// ========================================
// WiFi Connection Settings
// ========================================
extern const int WIFI_CONNECT_TIMEOUT;          // Timeout in seconds

#endif // CONFIG_H
