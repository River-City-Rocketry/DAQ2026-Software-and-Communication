const int outputPin1 = 35;
const int outputPin2 = 36;
const int analogPin = 41;

void setup() {
  Serial.begin(115200);

  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);

  digitalWrite(outputPin1, HIGH);
  digitalWrite(outputPin2, HIGH);

  analogReadResolution(10);  // 10-bit ADC (0-1023)
}

void loop() {
  int analogValue = analogRead(analogPin);

  // Assuming a 3.3V reference
  float voltage = analogValue * (3.3 / 1023.0);

  Serial.print("ADC: ");
  Serial.print(analogValue);
  Serial.print("   Voltage: ");
  Serial.print(voltage, 3);  // Print with 3 decimal places
  Serial.println(" V");

  delay(1000);
}
