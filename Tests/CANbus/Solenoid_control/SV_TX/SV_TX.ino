#include <FlexCAN_T4.h>

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;

CAN_message_t msg;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Can0.begin();
  Can0.setBaudRate(500000);
  msg.id= 0x100;
  msg.len = 1;
  Serial.println("1. Close solenoid 1");
  Serial.println("2. Open solenoid 1");
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Select an option");
  while (Serial.available() == 0)
    {
      //stays in loop until input
    }
      char choice = Serial.read();
      switch (choice)
      {
        case '1':
          msg.buf[0] = 1;
          Can0.write(msg);
          Serial.println("Open command sent");
          break;
        case '2':
        Serial.println("two");
          msg.buf[0] = 2;
          Can0.write(msg);
          Serial.println("Close command sent");
          break;
        
        default:
        Serial.println("Invalid option");
      }
}
