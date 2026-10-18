volatile uint32_t edgeCount = 0;
void IRAM_ATTR onEdge() { edgeCount++; }

void setup() {
  Serial.begin(115200);
  pinMode(14, INPUT);
  attachInterrupt(digitalPinToInterrupt(14), onEdge, CHANGE);
}
void loop() {
  Serial.printf("D0=%d edges=%lu\n", digitalRead(14), edgeCount);
  delay(300);
}
