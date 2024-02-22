#include <Servo.h>
#define pinLectura A0
#define pinMotor 9
Servo motor;
int lectura, mapeo, rotacion;

void setup() {
  Serial.begin(9600);
  pinMode(pinLectura, INPUT);
  pinMode(pinMotor, OUTPUT);
  motor.write(0);
  motor.attach(9);
}

void loop() {
  lectura = analogRead(pinLectura);

  Serial.print("Lectura:\t");
  Serial.println(lectura);
  delay(500);

  //mapeo = map(lectura, 0, 1023, 0, 255);              Usando un potenciómetro
  mapeo = map(lectura, 500, 625, 0, 255);            // Usando un termistor
  analogWrite(pinMotor, mapeo);

  Serial.print("Mapeo:\t\t");
  Serial.println(mapeo);
  Serial.println();

  rotacion = map(mapeo, 0, 255, 0, 180);
  motor.write(rotacion);
}
