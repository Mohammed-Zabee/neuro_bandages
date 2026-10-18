#include "../../NeuroBandage_Firmware/sensors.h"
void setup() { Serial.begin(115200); initSensors(); }
void loop() {
  Serial.print("pH:");   Serial.print(readPH());
  Serial.print(",Temp:"); Serial.print(readTemp());
  Serial.print(",Imp:");  Serial.println(readImpedance());
  delay(200);
}
