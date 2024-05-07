#define joystickX A3
#define joystickY A2
#define joystickBoton 2

void setup() {
  Serial.begin(9600);
  pinMode(joystickBoton, INPUT_PULLUP);
}

void loop() {
  Serial.print(analogRead(joystickX));
  Serial.print(" ");
  Serial.print(analogRead(joystickY));
  Serial.print(" ");
  Serial.println(digitalRead(joystickBoton));
  delay(1000);
}