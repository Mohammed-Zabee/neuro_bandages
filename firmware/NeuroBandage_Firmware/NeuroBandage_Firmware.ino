#include "sensors.h"
#include "isr.h"
#include "model.h"

void setup() {
  Serial.begin(115200);
  initSensors();
  initWakeInterrupt();
}

void loop() {
  static uint32_t lastBeat = 0;
  if (eventTriggered || millis() - lastBeat > 1000) {
    eventTriggered = false;
    lastBeat = millis();

    float ph = readPH(), temp = readTemp(), imp = readImpedance();
    float risk = predictInfectionRisk(ph, imp, temp);
    const char* status = (risk >= 0.70) ? "CRITICAL_BIOFILM" : "NORMAL";

    Serial.print("{\"pH\":");            Serial.print(ph, 2);
    Serial.print(",\"impedance_kOhm\":"); Serial.print(imp, 2);
    Serial.print(",\"temp_C\":");        Serial.print(temp, 2);
    Serial.print(",\"risk_score\":");    Serial.print(risk, 2);
    Serial.print(",\"status\":\"");      Serial.print(status);
    Serial.println("\"}");
  }
}
