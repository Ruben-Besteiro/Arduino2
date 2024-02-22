#include <DHT.h>

#define pinHumedad 7

DHT sensorHumedad(pinHumedad, DHT11);

void setup() {
  Serial.begin(9600);
  sensorHumedad.begin();
}

void loop() {
  float humedad = sensorHumedad.readHumidity();
  Serial.println(humedad);
}
