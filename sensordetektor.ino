/*

*/

void sensordetektor(void) {
  for (uint8_t i = 10; i < 160; i++) { // should be 0x76 or 0x77
    Wire.beginTransmission(i);
    int erg = Wire.endTransmission();
    if (erg == 0) {
      Serial.print("Device: 0x");
      Serial.print(i, HEX);

      Wire.beginTransmission(i);
      Wire.write(0xD0);
      Wire.endTransmission();
      Wire.requestFrom(i, 1);
      uint8_t id = Wire.read();
      uint8_t variant = 0;

      if (id == 0x61) { // BME680 | BME688?
        Wire.beginTransmission(i);
        Wire.write(0xF0);
        Wire.endTransmission();
        Wire.requestFrom(i, 1);
        variant = Wire.read();

        Serial.print(" Variant: 0x");
        Serial.print(variant, HEX);
      } else if (id == 0x00) { // bmp388, so much wisdom, change the id register...
        Wire.beginTransmission(i);
        Wire.write(0x00);
        Wire.endTransmission();
        Wire.requestFrom(i, 1);
        id = Wire.read();
      }

      Serial.print(" ID: 0x");
      Serial.print(id, HEX);

      switch (id) {
        case 0x50 :
          Serial.print(" = BMP388 TP");
          break;
        case 0x55 :
          Serial.print(" = BMP180 TP");
          break;
        case 0x58 :
          Serial.print(" = BMP280 TP");
          break;
        case 0x60 :
          Serial.print(" = BME280 TPH");
          break;
        case 0x61 :
          switch (variant) {
            case 0x00 :
              Serial.print(" = BME680 TPHQ");
              break;
            case 0x01 :
              Serial.print(" = BME688 TPHQ+AI");
              break;
          }
          break;
        default:
          Serial.print(" = unknown");
          break;
      }

      Serial.println();
    }
  }
}

/*

  BME680 TPHQ   0x61
  BME688 TPHQ   0x61  Variant-ID/0xf0 = 0x01
  Schnell geprüft mit folgendem Sketch:
*/
