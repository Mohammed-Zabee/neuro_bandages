#pragma once
#include <Arduino.h>

#define PIN_WAKE 14
#define PIN_PH   34
#define PIN_TEMP 35
#define PIN_IMP  32

inline void initSensors() {
  analogReadResolution(12);
  analogSetPinAttenuation(PIN_PH,   ADC_11db);
  analogSetPinAttenuation(PIN_TEMP, ADC_11db);
  analogSetPinAttenuation(PIN_IMP,  ADC_11db);
}

inline float readVoltage(int pin, int samples = 16) {
  uint32_t sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delayMicroseconds(200);
  }
  return ((sum / (float)samples) / 4095.0f) * 3.3f;
}

// TODO: replace with calibrated values after Day 11 solution tests
inline float readPH()        { return (3.5f * readVoltage(PIN_PH)) + 1.2f; }
inline float readTemp()      { return 25.0f + (readVoltage(PIN_TEMP) * 6.5f); }
inline float readImpedance() { return (readVoltage(PIN_IMP) / 3.3f) * 10.0f; }
