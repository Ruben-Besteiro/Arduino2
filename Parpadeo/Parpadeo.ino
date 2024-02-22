void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  delay (1000);
  digitalWrite(2, HIGH);
  Serial.println("Led encendido");
  delay (1000);
  digitalWrite(2, LOW);
  Serial.println("Led apagado");
}