#include "sensor.h"

// Inicializa a variável estática
Sensor* Sensor::sensorInstance = nullptr;

// ============ Handler de Interrupção ============
void ICACHE_RAM_ATTR Sensor::InterruptHandler() {
    if (sensorInstance != nullptr) {
        // Coleta estado atual do sensor
        sensorInstance->lastState = sensorInstance->currentState;
        // Lê novo estado via digitalRead em um pino
        sensorInstance->currentState = digitalRead(sensorInstance->pin);
        // Marca evento e timestamp do evento
        sensorInstance->eventDetected = true;
        sensorInstance->eventTimestamp = millis();
    }
}

// ============ Inicialização ============
void Sensor::Initialize(int mode) {
    pinMode(pin, INPUT);
    sensorInstance = this;
    
    // Lê o estado inicial
    currentState = digitalRead(pin);
    lastState = currentState;
    
    // Configura a interrupção de hardware
    // Para ESP8266/NodeMCU: D0-D8 podem ser usados como interrupção
    attachInterrupt(digitalPinToInterrupt(pin), InterruptHandler, mode);
}

// ============ Checagem de Evento ============
bool Sensor::CheckEvent() {
    return eventDetected;
}

void Sensor::ResetEvent() {
    eventDetected = false;
}

// ============ Leitura de Estado ============
int Sensor::GetCurrentState() const {
    return currentState;
}

int Sensor::GetLastState() const {
    return lastState;
}

// ============ POST de Evento ============
bool Sensor::PostEvent() const {
    if (!eventDetected) {
        return false;
    }
    
    // TODO: Implementar POST HTTP
    // Exemplo com HTTPClient:
    // HTTPClient http;
    // http.begin("http://seu_servidor/api/sensor");
    // http.addHeader("Content-Type", "application/json");
    // 
    // String state = currentState == HIGH ? "DETECTED" : "NOT_DETECTED";
    // String payload = "{\"sensor\":\"line_follower\",\"state\":\"" + state + 
    //                  "\",\"timestamp\":" + String(eventTimestamp) + "}";
    // 
    // int httpCode = http.POST(payload);
    // http.end();
    // return (httpCode == HTTP_CODE_OK);
    
    Serial.println("\nENVIO\n");

    return true;
}

// ============ Utilitários ============
unsigned long Sensor::GetEventTimestamp() const {
    return eventTimestamp;
}

void Sensor::PrintDebug() const {
    Serial.print("Pin: ");
    Serial.print(pin);
    Serial.print(" | Current State: ");
    Serial.print(currentState == HIGH ? "HIGH" : "LOW");
    Serial.print(" | Last State: ");
    Serial.print(lastState == HIGH ? "HIGH" : "LOW");
    Serial.print(" | Event: ");
    Serial.print(eventDetected ? "YES" : "NO");
    Serial.print(" | Timestamp: ");
    Serial.println(eventTimestamp);
}