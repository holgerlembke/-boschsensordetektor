#include <Wire.h>

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Bosch Sensor Detektor");

  Wire.begin();
}

void loop() {
  sensordetektor();
  delay(5000);
}
