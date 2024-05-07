// Definicion de pines
const int pinMotor1 = 13; // 28BYJ48 - In1
const int pinMotor2 = 12; // 28BYJ48 - In2
const int pinMotor3 = 11; // 28BYJ48 - In3
const int pinMotor4 = 10; // 28BYJ48 - In4

// Retardo entre pasos (en microsegundos)
int retardo = 800; // Puedes ajustar este valor para cambiar la velocidad del motor

// Secuencia de pasos para el motor paso a paso 28BYJ48 en modo de medio paso
const int pasoSecuencia[8][4] = {
  {HIGH, LOW, LOW, LOW},
  {HIGH, HIGH, LOW, LOW},
  {LOW, HIGH, LOW, LOW},
  {LOW, HIGH, HIGH, LOW},
  {LOW, LOW, HIGH, LOW},
  {LOW, LOW, HIGH, HIGH},
  {LOW, LOW, LOW, HIGH},
  {HIGH, LOW, LOW, HIGH}
};

void setup() {
  // Declarar pines como salida
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotor3, OUTPUT);
  pinMode(pinMotor4, OUTPUT);
}

void loop() {
  // Girar en sentido horario una vuelta completa
  for (int i = 0; i < 512; i++) { // 512 pasos para una vuelta completa
    for (int j = 0; j < 8; j++) { // Itera sobre la secuencia de pasos
      for (int k = 0; k < 4; k++) { // Itera sobre los pines del motor
        digitalWrite(pinMotor1 - k, pasoSecuencia[j][k]);
      }
      delayMicroseconds(retardo);
    }
  }

  // Detener el motor
  for (int k = 0; k < 4; k++) {
    digitalWrite(pinMotor1 + k, LOW);
  }

  // Esperar un tiempo antes de volver a comenzar
  delay(0); // Un segundo de espera antes de comenzar el próximo ciclo
}