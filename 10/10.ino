#include <LiquidCrystal.h>
LiquidCrystal pantalla(2, 4, 5, 6, 7, 9);
int inclinacion = 0;
long contador;

void setup() {
  Serial.begin(9600);
  pantalla.begin(16, 2);    // 16 columnas, 2 filas
}

void loop() {
  inclinacion = digitalRead(8);

  contador = millis();
  //Serial.println(contador);
  if (contador % 1000 == 0) {
    pantalla.print(inclinacion);
    Serial.println(inclinacion);
  }

  if (contador % 32000 == 0) {
    pantalla.setCursor(0,0);
  }
}
