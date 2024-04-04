#define ENABLE 11
#define pin_1A 13
#define pin_2A 12

void setup() {
  Serial.begin(9600);
  /*pinMode(ENABLE,OUTPUT);
  pinMode(pin_1A,OUTPUT);
  pinMode(pin_2A,OUTPUT);
  digitalWrite(ENABLE, HIGH);*/
  digitalWrite(ENABLE, HIGH);
  digitalWrite(pin_1A, HIGH);
}

void loop() {
  /*Serial.println("XD");
  digitalWrite(pin_1A, HIGH);
  digitalWrite(pin_2A, LOW);
  delay(500);
  digitalWrite(pin_1A, LOW);
  digitalWrite(pin_2A, HIGH);
  delay(500);*/
}