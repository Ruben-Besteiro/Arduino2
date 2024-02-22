#define temperatura A1
/*const int led3 = 13;
const int led4 = 8;
const int led5 = 4;
const int temperatura1 = 15;
const int temperatura2 = 10;
const int temperatura3 = 20;*/
float sensibilidad;
float tension;
int lectura;
float temperaturaFinal;
void setup() {
 Serial.begin(9600); // Iniciar la comunicación serie

  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
lectura = analogRead(A0/*temperaturaFinal*/);
Serial.println(lectura);
tension = (lectura * 5.0) / 1024.0;
Serial.println(tension);
temperaturaFinal = lectura /50 + 12;
Serial.println(temperatura);
if (temperaturaFinal >= 15){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  } 
  
  if (temperaturaFinal >= 10){
    digitalWrite(8,HIGH);
  } else {
    digitalWrite(8,LOW);
  } 
  
  if (temperaturaFinal >= 20){
    digitalWrite(4,HIGH);
  } else {
    digitalWrite(4,LOW);
  }
  delay(1000);

}