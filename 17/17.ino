#define s A0
#define led 2

#include <IRremote.h>

long datoIR;
int datoCom;
bool estado_LED;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(s);
  pinMode(led, OUTPUT);
  Serial.println("La ejecución ha comenzado");
}

void loop() {
  if (IrReceiver.decode() == 1){
    datoIR = IrReceiver.decodedIRData.decodedRawData; 
    datoCom = IrReceiver.decodedIRData.command; 

    Serial.print("Número pulsado: ");
    switch (datoCom) {
        case 22: Serial.println("0");   // Aquí se podría usar un registro de desplazamiento
        digitalWrite(11, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        break;
        case 12: Serial.println("1");
        digitalWrite(11, LOW);
        digitalWrite(10, HIGH);
        digitalWrite(9, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        break;
        case 24: Serial.println("2");
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, HIGH);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        break;
        case 94: Serial.println("3");
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        break;
        case 8: Serial.println("4");
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        break;
        case 28: Serial.println("5");
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        break;
        case 90: Serial.println("6");
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        break;
        case 66: Serial.println("7");
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        break;
        case 82: Serial.println("8");
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(2, LOW);
        break;
        case 74: Serial.println("9");
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, HIGH);
        break;
        default: Serial.println(datoCom);
    }
    /*Serial.print("Comando: ");
    Serial.println(datoCom);*/

    if (datoCom == 9){
      digitalWrite(led, HIGH);
    }
    if(datoCom == 7){
      digitalWrite(led, LOW);
    }
  } 
  IrReceiver.resume();
}

/*#include <IRremote.h>

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(A0);
}

void loop() {
  delay(500);
  //Serial.println(IrReceiver.decode());
  long variable = IrReceiver.decodedIRData.command;
  Serial.println(variable);
  IrReceiver.resume();
}*/
