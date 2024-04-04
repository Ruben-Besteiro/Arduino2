void setup() {
  Serial.begin(9600);
}

void loop() {
  randomSeed(analogRead(A0));
  unsigned long contador = millis();
  byte numero;

  if (contador % 1000 == 0) {
    numero = (byte) random(1,7);
    Serial.println(numero);

    switch(numero) {
     case 1:
       digitalWrite(2, LOW);
       digitalWrite(3, LOW);
       digitalWrite(4, HIGH);
       digitalWrite(5, LOW);
       digitalWrite(6, HIGH);
       digitalWrite(7, LOW);
       digitalWrite(8, LOW);
       digitalWrite(9, LOW);
     break;
     case 2:
       digitalWrite(2, HIGH);
       digitalWrite(3, HIGH);
       digitalWrite(4, LOW);
       digitalWrite(5, LOW);
       digitalWrite(6, HIGH);
       digitalWrite(7, HIGH);
       digitalWrite(8, LOW);
       digitalWrite(9, HIGH);
    break;
    case 3:
       digitalWrite(2, LOW);
       digitalWrite(3, HIGH);
       digitalWrite(4, HIGH);
       digitalWrite(5, LOW);
       digitalWrite(6, HIGH);
       digitalWrite(7, HIGH);
       digitalWrite(8, LOW);
       digitalWrite(9, HIGH);
     break;
     case 4:
       digitalWrite(2, LOW);
       digitalWrite(3, LOW);
       digitalWrite(4, HIGH);
       digitalWrite(5, LOW);
       digitalWrite(6, HIGH);
       digitalWrite(7, LOW);
       digitalWrite(8, HIGH);
       digitalWrite(9, HIGH);
     break;
     case 5:
       digitalWrite(2, LOW);
       digitalWrite(3, HIGH);
       digitalWrite(4, HIGH);
       digitalWrite(5, LOW);
       digitalWrite(6, LOW);
       digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
       digitalWrite(9, HIGH);
      break;
      case 6:
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
       digitalWrite(8, HIGH);
       digitalWrite(9, HIGH);
    }
  }
}
