//#include <stdlib.h>
#include <IRremote.h>
#include <Servo.h>

#define trig 8
#define echo 9
#define pinIR A5
#define termistor A4
#define joystickBoton 2
#define joystickX A3
#define joystickY A2
#define fotorres A1

#define theremin 4
#define pinMotor1 13
#define pinMotor2 12
#define pinMotor3 11
#define pinMotor4 10
#define pinServo A0

enum {
  inicial, espera, ultrason, temp, tiem
} estado;
Servo servo;

int determinarEstado();
void accion(int estado);

void ultrasonidos();
void temperatura();
void tiempo();

void setup() {
  estado = inicial;		// Estado finito
  
  Serial.begin(9600);
  IrReceiver.begin(pinIR);
  servo.attach(pinServo);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(joystickBoton, INPUT_PULLUP);
  pinMode(joystickX, INPUT);
  pinMode(joystickY, INPUT);
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotor3, OUTPUT);
  pinMode(pinMotor4, OUTPUT);
  pinMode(pinServo, OUTPUT);

  delay(1);
  servo.write(0);
}

void loop() {
  Serial.println("\nPulsa alguno de los botones del mando para consultar información");

  if (estado == inicial) {      // Esto solo se mostrará una vez, cuando se ejecute el programa
    Serial.println("0 = Distancia al animal");
    Serial.println("1 = Temperatura dentro del habitat");
    Serial.println("2 = Tiempo que hace en el habitat");
  }

  estado = determinarEstado(estado);
  accion(estado);
}

int determinarEstado(int estado) {		// Arduino no deja hacer que la función devuelva un enum, así que pongo int (que en realidad es lo mismo)

  while (!IrReceiver.decode()) {		// No hace nada y espera hasta que le demos a un botón
  }
  
  if (IrReceiver.decode()) {
  	int opcion = IrReceiver.decodedIRData.command;
    
    switch (opcion) {
      case 22:
      	Serial.println("Has elegido consultar la distancia");
      	estado = ultrason;
      break;
      case 12:
      	Serial.println("Has elegido consultar la temperatura");
      	estado = temp;
      break;
      case 24:
      	Serial.println("Has elegido consultar el tiempo que hace");
      	estado = tiem;
      break;
      case 94:
      case 8:
      case 28:
      case 90:
      case 66:
      case 82:
      case 74:
        Serial.println("Opcion no implementada");
      break;
    }
      IrReceiver.resume();
  }
  
  return estado;
}

void accion(int estado) {    // Esta función determina a dónde va a ir la ejecución una vez que el estado ya ha sido determinado
  switch (estado) {
    case ultrason:
      ultrasonidos();
      break;
    case temp:
      temperatura();
      break;
    case tiem:
      tiempo();
  }
  estado = espera;
}

void ultrasonidos() {
  long tiempo = 0;
  float distancia = 0;
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  tiempo = pulseIn(echo, HIGH);  
  distancia = (tiempo * 343 / 2 ) / 10000;
 	
  Serial.print("La distancia al animal es ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia < 10 && distancia > 5) {
    Serial.println("Se recomienda alejarse");
    tone(theremin, 200, 1000);
    delay(1000);
  } else if (distancia < 5) {
    Serial.println("Se recomienda encarecidamente alejarse");
    tone(theremin, 400, 1000);
    delay(1000);
  } else {
    noTone(theremin);
  }

  estado = espera;
}

void temperatura() {
  float gradosC = map(analogRead(termistor), 500, 650, 10, 50);/*analogRead(termistor);*/
  Serial.print("La temperatura es ");
  Serial.println(gradosC);

  if (gradosC >= 35) {
    Serial.println("Hace calor");
    Serial.println("Pulsa el botón del joystick para activar el ventilador");
    Serial.println("Mueve el joystick en cualquier dirección para no activarlo");

    while (digitalRead(joystickBoton) && analogRead(joystickX) > 400 && analogRead(joystickX) < 600 && analogRead(joystickY) > 400 && analogRead(joystickY < 600)) {   // No hace nada hasta que se pulse el botón o mueva el joystick
      if (!digitalRead(joystickBoton)) {
        unsigned long contador = millis();
        Serial.println(digitalRead(2));

        const int pasoSecuencia[8][4] = {   //  El código para controlar el motor PaP fue sacado del Tinkercad que hiciste
        {HIGH, LOW, LOW, LOW},
        {HIGH, HIGH, LOW, LOW},
        {LOW, HIGH, LOW, LOW},
        {LOW, HIGH, HIGH, LOW},
        {LOW, LOW, HIGH, LOW},
        {LOW, LOW, HIGH, HIGH},
        {LOW, LOW, LOW, HIGH},
        {HIGH, LOW, LOW, HIGH}
        };

        for (int i = 0; i < 2048; i++) {
          for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 4; k++) {
              digitalWrite(pinMotor1 - k, pasoSecuencia[j][k]);
            }
            delayMicroseconds(800);
          }
        }

        for (int k = 0; k < 4; k++) {
          digitalWrite(pinMotor1 + k, LOW);
        }
      }

      if (analogRead(joystickX) < 400 || analogRead(joystickX) > 600 || analogRead(joystickY) < 400 || analogRead(joystickY > 600)) {
        estado = espera;
      }
    }
  } else {
    Serial.println("No hace calor");
    Serial.println("No es necesario activar el ventilador");
  }
}

void tiempo() {
  bool preguntarAlUsuario = false;

  if (analogRead(fotorres) > 900) {
    Serial.println("Hace sol");
    Serial.println("Activando el riego...");
  }

  if (analogRead(fotorres) < 900 && analogRead(fotorres) > 600) {
    Serial.println("El cielo esta nublado");
    Serial.println("Pulsa el botón del joystick para activar el ventilador");
    Serial.println("Mueve el joystick en cualquier dirección para no activarlo");
    preguntarAlUsuario = true;
  }

  if (analogRead(fotorres) < 600) {
    Serial.println("El cielo esta encapotado, por lo que es probable que llueva");
    Serial.println("No es necesario activar el riego");
    estado = espera;    // Con esto me salto la función de activar el riego y vuelvo al loop
  }

  while (digitalRead(joystickBoton) && analogRead(joystickX) > 400 && analogRead(joystickX) < 600 && analogRead(joystickY) > 400 && analogRead(joystickY < 600) && preguntarAlUsuario) {   // Si no está encapotado, no hace nada hasta que se pulse el botón o mueva el joystick
      if (!digitalRead(joystickBoton)) {    // Joystick pulsado
        break;          // El estado no cambia
      }

      if (analogRead(joystickX) < 400 || analogRead(joystickX) > 600 || analogRead(joystickY) < 400 || analogRead(joystickY) > 600) {   // Joystick movido
        estado = espera;
      }
    }

  if (estado != espera) {               // Esto ocurre cuando el usuario decide activar el ventilador
    for (int i = 0; i < 4; i++) {
      servo.write(180);
      delay(500);
      servo.write(0);
      delay(500);
    }
    estado = espera;
  }
}