#include <FlexCAN_T4.h>

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {}

  pinMode(6, OUTPUT);
  digitalWrite(6, LOW); // only if your transceiver enable is wired and LOW = enabled

  Can0.begin();
  Can0.setBaudRate(1000000);

  // Optional but fine:
  Can0.setMaxMB(16);
  Can0.enableFIFO();
}

void loop() {
  static uint32_t last = 0;
  if (millis() - last >= 200) {
    CAN_message_t msg;
    memset(&msg, 0, sizeof(msg));   // good practice

    msg.id = 0x123;                 // fixed standard ID
    msg.len = 8;                    // <-- REQUIRED
    msg.flags.extended = 0;         // standard 11-bit ID

    memcpy(msg.buf, "CAN TEST", 8);

    Can0.write(msg);

    // Optional debug so you know it's sending
    Serial.println("sent 0x123");
    last = millis();
  }
}