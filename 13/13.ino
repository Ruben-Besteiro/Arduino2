#define pinPulsador1 13
#define pinPulsador2 12
#define pinMotor 9

bool pulsador1, pulsador2, pulsador1ant, pulsador2ant;
int marchas = 9, marchaactual = 1, velocidad;
int entrada = 0, motor = 0, frecuencia;

void setup() {
  Serial.begin(9600);
  pinMode(pinPulsador1, INPUT);
  pinMode(pinPulsador2, INPUT);

  Serial.println("Introduce cuántas marchas debe tener el motor");
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

void loop() {
  unsigned long int contador = millis();
  unsigned long int contador2 = 0;

  pulsador1 = digitalRead(pinPulsador1);
  pulsador2 = digitalRead(pinPulsador2);

  if (pulsador1 && !pulsador1ant && marchaactual < marchas /*&& contador2 - contador < 100*/) {
    contador2 = contador;
    marchaactual++;
    Serial.print("Último cambio: ");
    Serial.print(contador2);
    Serial.println("ms");
    Serial.print("La marcha actual es la ");
    Serial.print(marchaactual);
    velocidad = map(marchaactual, 0, marchas, 0, 100);
    Serial.print("    La velocidad es un ");
    Serial.print(velocidad);
    Serial.println("%");
    analogWrite(pinMotor, map(marchaactual, 0, marchas, 0, 255));
  }

  if (pulsador2 && !pulsador2ant && marchaactual > 1 /*&& contador2 - contador < 100*/) {
    contador2 = contador;
    marchaactual--;
    Serial.print("Último cambio: ");
    Serial.print(contador2);
    Serial.println("ms");
    Serial.print("La marcha actual es la ");
    Serial.print(marchaactual);
    velocidad = map(marchaactual, 0, marchas, 0, 100);
    Serial.print("    La velocidad es un ");
    Serial.print(velocidad);
    Serial.println("%");
    analogWrite(3, map(marchaactual, 0, marchas, 0, 255));
  }

  pulsador1ant = pulsador1;
  pulsador2ant = pulsador2;
}
