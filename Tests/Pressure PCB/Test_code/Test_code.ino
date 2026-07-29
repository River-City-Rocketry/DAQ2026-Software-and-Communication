const int outputPin1 = 35;   // MUX Select S0
const int outputPin2 = 36;   // MUX Select S1
const int analogPin  = 41;   // ADC input from MUX

const float VREF = 3.3;
const float R1 = 3.3;   // kΩ (top resistor)
const float R2 = 10.0;  // kΩ (bottom resistor)

int channel = 0;

void setup() {
  Serial.begin(115200);

  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);

  analogReadResolution(10);   // ADC range: 0-1023
}

void loop() {
  // Select MUX channel
  digitalWrite(outputPin1, channel & 0x01);          // S0
  digitalWrite(outputPin2, (channel >> 1) & 0x01);   // S1

  // Allow the MUX output to settle
  delayMicroseconds(10);

  // Read ADC
  int analogValue = analogRead(analogPin);

  // Voltage at the ADC pin
  float adcVoltage = analogValue * (VREF / 1023.0);

  // Calculate original input voltage before the divider
  float inputVoltage = adcVoltage * ((R1 + R2) / R2);

  // Print results
  Serial.print("Channel ");
  Serial.print(channel);
  Serial.print(" | ADC: ");
  Serial.print(analogValue);
  Serial.print(" | ADC Voltage: ");
  Serial.print(adcVoltage, 3);
  Serial.print(" V | Input Voltage: ");
  Serial.print(inputVoltage, 3);
  Serial.println(" V");

  // Next channel (0 → 1 → 2 → 3 → 0)
  channel = (channel + 1) % 4;


  delay(100);
}