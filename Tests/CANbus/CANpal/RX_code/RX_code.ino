#include <FlexCAN_T4.h>

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;

void canRx(const CAN_message_t &msg) {
  for (uint8_t i = 0; i < msg.len; i++) {
    if (msg.buf[i] < 0x10) Serial.print("0");
    Serial.print(msg.buf[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2000) {}

  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);   // only if your CAN Pal enable pin is wired here

  Can0.begin();
  Can0.setBaudRate(1000000);

  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(canRx);

  Serial.println("CAN3 transceiver node online");
}

void loop() {
  // Process incoming CAN frames
  Can0.events();

  // Periodic transmit (heartbeat)
  static uint32_t lastTx = 0;
  if (millis() - lastTx >= 500) {
    CAN_message_t msg;
    memset(&msg, 0, sizeof(msg));

    msg.id = 0x321;
    msg.len = 2;
    msg.flags.extended = 0;
    msg.buf[0] = 0xAA;
    msg.buf[1] = 0x55;

    Can0.write(msg);
    lastTx = millis();
  }
}