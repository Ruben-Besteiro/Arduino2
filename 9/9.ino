#include <DHT.h>
#include <Servo.h>
#define pinEntrada 11
#define pinRojo 0
#define pinVerde 3
#define pinAzul 2
#define pinMotor 6
DHT sensorHumedad(pinEntrada, DHT11);
Servo smotor;
float temperatura, humedad;

void setup() {
  Serial.begin(9600);
  sensorHumedad.begin();
  smotor.attach(6);
  delay(1);
}

void loop() {
  temperatura = (sensorHumedad.readTemperature(true) - 32) * 5 / 9;
  humedad = sensorHumedad.readHumidity(true);

  Serial.print("Temperatura:\t");
  Serial.print(temperatura);
  Serial.print("\tHumedad:\t");
  Serial.println(humedad);
  delay(1000);

  led();          // Gestiona el color del LED según la humedad
  motor();        // Lo mismo pero con la velocidad del motor
}

void led() {
  if (humedad < 45) {
    digitalWrite(pinRojo, HIGH);
  } else {
    digitalWrite(pinRojo, LOW);
  }

  if (humedad >= 45 && humedad < 60) {
    digitalWrite(pinVerde, HIGH);
  } else {
    digitalWrite(pinVerde, LOW);
  }

  if (humedad >= 60) {
    digitalWrite(pinAzul, HIGH);
  } else {
    digitalWrite(pinAzul, LOW);
  }
}

void motor() {
  smotor.write(0);
  float angulo = map(humedad, 45, 70, 0, 360);
  smotor.write(angulo);
}