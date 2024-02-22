#define pinLecturaRojo A0
#define pinLecturaVerde A3
#define pinLecturaAzul A5
#define ledRojo 9
#define ledVerde 10
#define ledAzul 11
int lecturaRojo, lecturaVerde, lecturaAzul, mapeoRojo, mapeoVerde, mapeoAzul;

void setup() {
  Serial.begin(9600);
  pinMode(pinLecturaRojo, INPUT);
  pinMode(pinLecturaVerde, INPUT);
  pinMode(pinLecturaAzul, INPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  delay(1);
}

void loop() {
  lecturaRojo = analogRead(pinLecturaRojo);
  lecturaVerde = analogRead(pinLecturaVerde);
  lecturaAzul = analogRead(pinLecturaAzul);

  mapeoRojo = map(lecturaRojo, 350, 1000, 0, 255);
  mapeoVerde = map(lecturaVerde, 300, 950, 0, 255);
  mapeoAzul = map(lecturaAzul, 0, 1023, 0, 255);

  Serial.print("Fotorresistencia roja:\t");
  Serial.println(lecturaRojo);

  Serial.print("Fotorresistencia verde:\t");
  Serial.println(lecturaVerde);

  Serial.print("Lectura potenciómetro (azul):\t");
  Serial.println(lecturaAzul);

  delay(1000);
  Serial.println("");     // Deja una línea de separación

  analogWrite(ledRojo, mapeoRojo);
  analogWrite(ledVerde, mapeoVerde);
  analogWrite(ledAzul, mapeoAzul);
}
