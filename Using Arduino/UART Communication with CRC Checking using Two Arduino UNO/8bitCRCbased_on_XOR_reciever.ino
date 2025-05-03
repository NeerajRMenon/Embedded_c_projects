void setup() {
  Serial.begin(9600);
  Serial.println("Ready to receive...");
}

uint8_t calculateCRC(const uint8_t *data, uint8_t len) {
  uint8_t crc = 0x00;
  for (uint8_t i = 0; i < len; i++) {
    crc ^= data[i];
  }
  return crc;
}

void loop() {
  if (Serial.available() >= 6) { // 5 chars + 1 CRC
    char buffer[5];
    uint8_t receivedCRC;

    for (int i = 0; i < 5; i++) {
      buffer[i] = Serial.read();
    }

    receivedCRC = Serial.read();
    uint8_t calcCRC = calculateCRC((uint8_t *)buffer, 5);

    if (calcCRC == receivedCRC) {
      Serial.print("Received: ");
      Serial.write(buffer, 5);
      Serial.println(" ✓ CRC OK");
    } else {
      Serial.println("CRC Mismatch ❌");
    }
  }
}
