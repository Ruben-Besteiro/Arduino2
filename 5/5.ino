#define pinLectura A0
#define led1 2
#define led2 3
#define led3 4
int lectura;
float voltaje, temperatura;

void setup() {
  Serial.begin(9600);
  pinMode(pinLectura, INPUT);
}

void loop() {
  voltaje = lectura * 5.0 / 1023.0;
  temperatura = (voltaje - 0.5) * 10.0 ;

  delay(500);
  lectura = analogRead(pinLectura);
  Serial.print("Lectura:\t");
  Serial.print(lectura);
  Serial.print("\tVoltaje:\t");
  Serial.print(voltaje);
  Serial.print("\tTemperatura:\t");
  Serial.println(temperatura);

  if (temperatura < 23) {
    digitalWrite(2, LOW);
  } else {
    digitalWrite(2, HIGH);
  }

  if (temperatura < 25) {
    digitalWrite(3, LOW);
  } else {
    digitalWrite(3, HIGH);
  }

  if (temperatura < 27) {
    digitalWrite(4, LOW);
  } else {
    digitalWrite(4, HIGH);
  }

  if (temperatura > 30) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    delay(200);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    delay(200);
  }
}