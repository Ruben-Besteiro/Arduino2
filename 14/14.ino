#include <LiquidCrystal.h>
#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define echo 10
#define trig 11

int entrada = 0;
int periodo;

LiquidCrystal pantalla(RS, E, D4, D5, D6, D7);

void setup() {
  Serial.begin(9600);
  pantalla.begin(16,2);
  pinMode(RS, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  unsigned long contador = millis();

  if (contador % 250 < 5) {
    pantalla.setCursor(0,0);
    pantalla.print("                ");
    pantalla.setCursor(0,0);
    
    ultra();
  }
}

void ultra() {
  unsigned long tiempoPulso;
  float distanciaCm;

  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  tiempoPulso = pulseIn(echo, HIGH);
  Serial.println(tiempoPulso);
  distanciaCm = (tiempoPulso*343.0/2.0)/10000.0;
  pantalla.print(distanciaCm);
}
