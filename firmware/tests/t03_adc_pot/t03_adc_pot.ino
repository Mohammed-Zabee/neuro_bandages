void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(32, ADC_11db);
}
void loop() {
  int raw = analogRead(32);
  Serial.printf("raw=%d  V=%.2f\n", raw, raw / 4095.0 * 3.3);
  delay(200);
}
