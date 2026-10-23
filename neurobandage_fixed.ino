/*
  NeuroBandage review 1 - fixed sketch
  ESP32 + NTC thermistor module (LM393)

  Wiring:
    Module VCC -> 3V3, GND -> GND
    Module AO  -> GPIO 34 (analog)
    Module DO  -> GPIO 4  (comparator output)

  Idea: an NTC's resistance FALLS when warm, so AO usually falls too.
  A "spike" is any quick change away from the resting level, up or down.
  Then a leaky integrate-and-fire neuron collects the spikes.
*/

const int AO_PIN = 34;
const int DO_PIN = 4;

// ---- Spike detection ----
const int   SPIKE_THRESHOLD = 25;     // ADC counts away from baseline = spike
const float BASELINE_SPEED  = 0.02;   // how slowly the baseline follows (smaller = slower)
float baseline = 0;

// ---- Neuron ----
float v = 0;
const float LEAK      = 0.95;   // keep 95% each step
const float WEIGHT    = 1.0;    // one spike adds this
const float THRESHOLD = 5.0;    // alert at this level

int lastDO = 0;

void setup() {
  Serial.begin(115200);
  pinMode(DO_PIN, INPUT);
  analogSetPinAttenuation(AO_PIN, ADC_11db);   // better range near 3 V

  // Start the baseline at the resting reading (don't touch the sensor now)
  long sum = 0;
  for (int i = 0; i < 20; i++) { sum += analogRead(AO_PIN); delay(50); }
  baseline = sum / 20.0;
  lastDO = digitalRead(DO_PIN);
}

void loop() {
  int adc = analogRead(AO_PIN);
  int deviation = adc - baseline;          // negative when warming, positive when cooling

  // Spike from the analog signal (works in either direction)
  int spike = (abs(deviation) > SPIKE_THRESHOLD) ? 1 : 0;

  // Spike from the comparator: DO changing state also counts
  int doNow = digitalRead(DO_PIN);
  int doEdge = (doNow != lastDO) ? 1 : 0;
  lastDO = doNow;

  // Baseline follows slowly, only while there is no spike
  if (!spike) baseline += BASELINE_SPEED * (adc - baseline);

  // Neuron
  int n = spike || doEdge;
  v = v * LEAK + WEIGHT * n;
  int alert = 0;
  if (v >= THRESHOLD) { alert = 100; v = 0; }

  // Plotter-friendly output
  Serial.print("AO_ADC:");   Serial.print(adc);
  Serial.print("\tBaseline:"); Serial.print(baseline, 1);
  Serial.print("\tDeviation:"); Serial.print(deviation);
  Serial.print("\tSpike:");    Serial.print(spike * 50);
  Serial.print("\tDO:");       Serial.print(doNow * 50);
  Serial.print("\tNeuron:");   Serial.print(v * 10, 1);
  Serial.print("\tAlert:");    Serial.println(alert);

  delay(100);
}
