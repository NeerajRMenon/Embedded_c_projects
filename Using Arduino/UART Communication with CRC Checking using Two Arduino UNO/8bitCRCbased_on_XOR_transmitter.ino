void setup() {
  Serial.begin(9600);
  delay(1000);
}

uint8_t calculateCRC(const uint8_t *data, uint8_t len) {
  uint8_t crc = 0x00;
  for (uint8_t i = 0; i < len; i++) {
    crc ^= data[i];
  }
  return crc;
}

void loop() {
  const char message[] = "Hi";
  uint8_t len = sizeof(message) - 1; // excluding null terminator
  uint8_t crc = calculateCRC((uint8_t *)message, len);

  Serial.write(message, len); // Send message
  Serial.write(crc);          // Send CRC

  delay(2000);
}
