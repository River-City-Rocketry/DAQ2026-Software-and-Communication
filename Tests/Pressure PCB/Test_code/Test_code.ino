const int outputPin1 = 35;
const int outputPin2 = 36;
const int analogPin = 41;

void setup() {
  Serial.begin(115200);

  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);

  digitalWrite(outputPin1, HIGH);
  digitalWrite(outputPin2, HIGH);
}

void loop() {
  int analogValue = analogRead(analogPin);

  Serial.print("Analog value: ");
  Serial.println(analogValue);

  delay(1000);
}