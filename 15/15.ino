#define pinReloj 4
#define latch 2
#define datos 6

void setup() {
  Serial.begin(9600);
  pinMode(pinReloj, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(datos, OUTPUT);
}

void loop() {
 
    digitalWrite(latch, LOW);

  shiftOut(6, pinReloj, MSBFIRST, 0);
  digitalWrite(latch, HIGH);
  delay(1000);
  digitalWrite(latch, LOW);
  shiftOut(6, pinReloj, MSBFIRST, 255);
  digitalWrite(latch, HIGH);
  delay(500);
}
