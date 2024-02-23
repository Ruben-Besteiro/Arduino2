#define pinMotor 9

char accion;
int marchas = 0, marchaactual = 1, velocidad, entrada = 0, lectura;

void setup() {
  if (marchas == 0) {           // Con arreglo un bug por el cual la ejecución vuelve al setup y cambia el número de marchas
    Serial.begin(9600);         // aunque en realidad no funciona
    pinMode(pinMotor, OUTPUT);

    Serial.println("\nIntroduce cuántas marchas debe tener el motor");
    while (entrada == 0) {      // Si Serial.available es igual a 0, este bucle lo que hace es no hacer nada hasta que deje de serlo. Así forzamos que Serial.available sea utilizable
      entrada = Serial.available();
    }
      marchas = Serial.read();
      marchas -= '0';
      Serial.print("El motor tendrá ");
      Serial.print(marchas);
      Serial.println(" marchas");

      Serial.print("La marcha actual es la ");
      Serial.print(marchaactual);
      velocidad = map(marchaactual, 0, marchas, 0, 100);
      Serial.print("    La velocidad es un ");
      Serial.print(velocidad);
      Serial.println("%");
      analogWrite(pinMotor, map(marchaactual, 0, marchas, 0, 255));
  }
}

void loop() {
  if (marchas < 0) {
    setup();
  }

  if (Serial.available() > 0) {
    accion = Serial.read();
  }

  switch (accion) {
    case '+': marchaactual++;
    break;
    case '-': marchaactual--;
    break;
  }

  if (marchaactual < 0) {
    marchaactual = 0;
  } else if (marchaactual > marchas) {
    marchaactual = marchas;
  }

  if (accion == '+' || accion == '-') {     // Si el usuario introduce algún carácter no válido, esto se lo salta
    Serial.print("La marcha actual es la ");
    Serial.print(marchaactual);
    velocidad = map(marchaactual, 0, marchas, 0, 100);
    Serial.print("    La velocidad es un ");
    Serial.print(velocidad);
    Serial.println("%");
    analogWrite(pinMotor, map(marchaactual, 0, marchas, 0, 255));
  }
  accion = '\0';
}
