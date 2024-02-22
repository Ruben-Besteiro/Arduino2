int XD = 0;

void setup() {
  Serial.begin(500);
}

void loop() {
  delay(500);
  Serial.println("Hola mundo");
  XD++;

  if (XD >= 5) {
    printf("XD");
  }
}