#define pinLectura A0
#define theremin 13
int lectura, frecuencia;

void setup() {
  Serial.begin(9600);
  pinMode(pinLectura, INPUT);
}

void loop() {
  lectura = analogRead(pinLectura);
  Serial.println(lectura);
  
  frecuencia = map(lectura, 0, 1023, 20, 20000);
  
  if (lectura < 900) {
    tone(theremin, frecuencia);
  } else {
    tone(theremin, 500, 250);
    delay(500);               // Esto no funciona porque al delay(500) se le suman los 500 del tono anterior (?)
    tone(theremin, 500, 250);
    delay(500);
    tone(theremin, 500, 250);
    delay(500);
    tone(theremin, 500, 1000);
    delay(500);
    tone(theremin, 500, 1000);
    delay(500);
    tone(theremin, 500, 1000);
    delay(500);
    tone(theremin, 500, 250);
    delay(500);
    tone(theremin, 500, 250);
    delay(500);
    tone(theremin, 500, 250);
    delay(1000);
  }
}