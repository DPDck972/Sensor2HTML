#include "sensor.h"

// Sensor na porta GPIO5 (D1 do NodeMCU)
Sensor lineFollower(5);

void setup() {
    Serial.begin(9600);
    lineFollower.Initialize(RISING);
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