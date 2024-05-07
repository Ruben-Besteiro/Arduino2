int sumando1, sumando1_bit0, sumando1_bit1, sumando1_bit2, sumando1_bit3;
int sumando2, sumando2_bit_0, sumando2_bit1, sumando2_bit2, sumando2_bit3;
int resultado, resultado_bit0, resultado_bit1, resultado_bit2, resultado_bit3;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Serial.print(Serial.available());
  while (Serial.available() == 0) {
  }
  Serial.print("Introduce el primer sumando: ");
  sumando1 = Serial.read();

  while(Serial.available() == 0) {
  }
  Serial.print("Introduce el segundo sumando: ");
  sumando2 = Serial.read();

  if (sumando1 % 2 == 0) {
    sumando1_bit0 = 0;
  } else {
    sumando1_bit0 = 1;
  }
  if (sumando1 % 4 < 2) {
    sumando1_bit1 = 0;
  } else {
    sumando1_bit1 = 1;
  }
  if (sumando1 % 8 < 4) {
    sumando1_bit2 = 0;
  } else {
    sumando1_bit2 = 1;
  }
  if (sumando1 % 16 < 8>) {
    sumando1_bit3 = 0;
  } else {
    sumando1_bit3 = 1;
  }
  print("El primer sumando en binario es " + sumando1_bit3 + sumando1_bit2 + sumando1_bit1 + sumando1_bit0);
}