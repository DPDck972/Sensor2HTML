#ifndef CONFIG_H
#define CONFIG_H

// ========================================
// WiFi Configuration
// ========================================
const char* SSID = "***";         
const char* PASSWORD = "***";   

// ========================================
// Server Configuration
// ========================================
const uint16_t SERVER_PORT = 80;
const int WIFI_CONNECT_TIMEOUT = 20;  

// ========================================
// Data Configuration
// ========================================
const unsigned long DATA_REFRESH_INTERVAL = 5000;

// ========================================
// Serial Configuration
// ========================================
const long BAUD_RATE = 9600;

#endif // CONFIG_H
