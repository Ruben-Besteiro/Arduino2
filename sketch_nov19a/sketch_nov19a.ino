int lectura;
#define pinLectura 2
#define rojo1 4
#define rojo2 8
#define verde 13

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode (pinLectura, INPUT);
pinMode (rojo1, OUTPUT);
pinMode (rojo2, OUTPUT);
pinMode (verde, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lectura = digitalRead(pinLectura);
  delay (1);
  Serial.println(lectura);

  if (lectura == 0) {
    digitalWrite (verde, HIGH);
    digitalWrite (rojo1, LOW);
    digitalWrite (rojo2, LOW);
  } else if (lectura == 1) {
    digitalWrite (verde, LOW);
    digitalWrite (rojo1, HIGH);
    digitalWrite (rojo2, LOW);
    delay (500);
    digitalWrite (rojo1, LOW);
    digitalWrite (rojo2, HIGH);
    delay (500);
  }
}
