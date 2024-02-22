#define pinLectura A0
#define led1 2
#define led2 4
#define led3 7
#define led4 8
#define led5 12
int lectura = 0;
float tension = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinLectura, INPUT);
  delay(1);
}

void loop() {
  lectura = analogRead(pinLectura);
  tension = lectura / 1024.0 * 5.0;

  Serial.print("Lectura:\t");
  Serial.print(lectura);
  Serial.print("\tTensión:\t");
  Serial.println(tension);
  delay(500);

  if (tension < 0.5) {
    digitalWrite(led1, LOW);
  } else {
    digitalWrite(led1, HIGH);
  }

  if (tension < 1.5) {
    digitalWrite(led2, LOW);
  } else {
    digitalWrite(led2, HIGH);
  }

  if (tension < 2.5) {
    digitalWrite(led3, LOW);
  } else {
    digitalWrite(led3, HIGH);
  }

  if (tension < 3.5) {
    digitalWrite(led4, LOW);
  } else {
    digitalWrite(led4, HIGH);
  }

  if (tension < 4.5) {
    digitalWrite(led5, LOW);
  } else {
    digitalWrite (led5, HIGH);
  }
}
