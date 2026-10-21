#include <math.h>

const int analogPin = 34;  // Module AO
const int digitalPin = 4;  // Module DO

// Example thermistor settings; check these against your module.
const float seriesResistor = 10000.0;
const float nominalResistance = 10000.0;  // NTC resistance at 25°C
const float nominalTemperatureC = 25.0;
const float beta = 3950.0;

const int baselineSamples = 20;
const int spikeThreshold = 100;  // ADC counts from baseline
const int sampleIntervalMs = 100;

int readings[baselineSamples];
int readingIndex = 0;
long readingSum = 0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // ESP32 ADC range: 0–4095
  pinMode(digitalPin, INPUT);

  // Initialize the rolling baseline.
  for (int i = 0; i < baselineSamples; i++) {
    readings[i] = analogRead(analogPin);
    readingSum += readings[i];
    delay(10);
  }
}

void loop() {
  int adc = analogRead(analogPin);
  int digitalState = digitalRead(digitalPin);

  float baseline = (float)readingSum / baselineSamples;
  int deviation = abs(adc - (int)baseline);
  int spike = (deviation >= spikeThreshold) ? 1 : 0;

  // Assumes the module divider has the NTC toward 3.3 V
  // and its fixed resistor toward GND.
  float temperatureC = NAN;

  if (adc > 0 && adc < 4095) {
    float resistance = seriesResistor * (4095.0 / adc - 1.0);
    float temperatureK = 1.0 / (
      (1.0 / (nominalTemperatureC + 273.15)) +
      (1.0 / beta) * log(resistance / nominalResistance)
    );
    temperatureC = temperatureK - 273.15;
  }

  // Serial Plotter format: each trace is label:value.
  Serial.print("AO_ADC:");
  Serial.print(adc);
  Serial.print("\tBaseline:");
  Serial.print(baseline, 1);
  Serial.print("\tDeviation:");
  Serial.print(deviation);
  Serial.print("\tTemp_C:");
  if (isnan(temperatureC)) {
    Serial.print(0);
  } else {
    Serial.print(temperatureC, 1);
  }
  Serial.print("\tSpike:");
  Serial.print(spike);
  Serial.print("\tDO:");
  Serial.println(digitalState);

  // Update the rolling baseline.
  readingSum -= readings[readingIndex];
  readings[readingIndex] = adc;
  readingSum += adc;
  readingIndex = (readingIndex + 1) % baselineSamples;

  delay(sampleIntervalMs);
}