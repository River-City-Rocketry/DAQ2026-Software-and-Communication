#include <FlexCAN_T4.h>

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can0;

CAN_message_t inmsg;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  Can0.begin();
  Can0.setBaudRate(500000);
  Serial.println("CAN Receiver Started");
}

void loop() 
{
  if (Can0.read(inmsg))
  {
    Serial.println("Recieved: ");
    Serial.print(inmsg.buf[0]);

    if(inmsg.buf[0] == 2)
    {
      digitalWrite(2, HIGH);
    }
    else if(inmsg.buf[0] == 1)
    {
      digitalWrite(2,LOW);
    }
  }

}
