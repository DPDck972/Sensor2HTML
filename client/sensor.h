#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include "config.h"

class Sensor {
private:
    // Pino do sensor
    const int pin;
    
    // Estado
    volatile int currentState;
    volatile int lastState;
    volatile bool eventDetected;
    unsigned long eventTimestamp;
    
    // Callback para interrupção
    static Sensor* sensorInstance;
    static void InterruptHandler();

public:
    // Construtor
    Sensor(int p) noexcept 
        : pin(p), currentState(LOW), lastState(LOW), 
          eventDetected(false), eventTimestamp(0) {}
    
    // Inicialização com interrupção
    void Initialize(int mode = CHANGE);
    
    // Checagem de evento
    bool CheckEvent();
    void ResetEvent();
    
    // Leitura do estado atual
    int GetCurrentState() const;
    int GetLastState() const;
    
    // POST de evento
    bool PostEvent() const;
    
    // Utilitários
    unsigned long GetEventTimestamp() const;
    void PrintDebug() const;
};

#endif