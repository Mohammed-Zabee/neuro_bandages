#pragma once
#include <Arduino.h>
#include "sensors.h"

volatile bool eventTriggered = false;
volatile uint32_t lastIsrMs = 0;

void IRAM_ATTR handleWakeupSpike() {
  uint32_t now = millis();
  if (now - lastIsrMs > 500) {   // 500 ms debounce
    lastIsrMs = now;
    eventTriggered = true;
  }
}

inline void initWakeInterrupt() {
  pinMode(PIN_WAKE, INPUT);      // use INPUT_PULLDOWN if D0 floats
  attachInterrupt(digitalPinToInterrupt(PIN_WAKE), handleWakeupSpike, RISING); // FALLING if D0 is active-low
}
