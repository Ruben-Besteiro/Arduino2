char letra = 'w';

void setup() {
  pinMode (2, OUTPUT);
  digitalWrite (2, LOW);
  Serial.begin(9600);
  Serial.println("Introduce la letra 'a' para encender el led y la letra 'z' para apagarlo");
}

void loop() {
  if(Serial.available()>0) {
    letra = Serial.read();

    if (letra == 'a') {
      digitalWrite (2, HIGH);
      Serial.println("Led encendido");
   } else if (letra == 'z') {
      digitalWrite (2, LOW);
      Serial.println("Led apagado");
    }
  }
}

// const int ledPin = 1; // Define el pin del LED

/*void setup() {
  Serial.begin(9600); // Inicializa la comunicación serie a 9600 baudios
  pinMode('1', OUTPUT); // Configura el pin del LED como salida
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read(); // Lee el carácter recibido
    
    if (receivedChar == 'a') {
      digitalWrite('1', HIGH); // Enciende el LED
      Serial.println("LED encendido");
    } else if (receivedChar == 'z') {
      digitalWrite('1', LOW); // Apaga el LED
      Serial.println("LED apagado");
    }
  }
}*/