#include <Servo.h>
#include <DHT.h>
#include <LiquidCrystal.h>

//Sensores
#define pinFotorresistencia A5
#define pinTermistor A2
#define pinHumedad 7

//Actuadores
#define pinLuzVerde 2
#define pinLuzAzul 4
#define pinLEDLluvia 5
#define pinAlarma 3
#define RS 8
#define E 9
#define DB4 10
#define DB5 11
#define DB6 12
#define DB7 13
#define pinPulsador A0        // NUEVO

Servo motor;
DHT sensorHumedad(pinHumedad, DHT11);
LiquidCrystal pantalla(RS, E, DB4, DB5, DB6, DB7);

void Accion(int nubosidad, int viento, int lluvia);		// Esta función determina qué se muestra por pantalla
void ColorLED(int nubosidad);		// He hecho que todas las funciones sean voids para que el void sea más simple
void Ventilador(int viento);
void ParpadeoAzul(int lluvia);



void setup() {
  Serial.begin(9600);
  motor.attach(6);
  sensorHumedad.begin();
  pantalla.begin(16,2);
  
  pinMode(pinFotorresistencia, INPUT);
  pinMode(pinTermistor, INPUT);
  pinMode(pinHumedad, INPUT);
  pinMode(pinLuzVerde, OUTPUT);
  pinMode(pinLuzAzul, OUTPUT);
  pinMode(pinAlarma, OUTPUT);
  pinMode(pinLEDLluvia, OUTPUT);
  pinMode(pinPulsador, INPUT);      // NUEVO

  Serial.println("\nEstación meteorológica Untar la Manteca™");   // La línea de abajo es NUEVA
  Serial.println("Pulsa Q para activar la estación, W para activarla dentro de 5 segundos, E para activarla cuando se pulse el botón y R para volver a mostrar este mensaje en 5 segundos");
  motor.write(0);		// Calibra el motor
  delay(1);
}



void loop() {
  // Este bloque de acciones se ejecuta independientemente de la acción que escoja el usuario. Aquí se miden las variables
  
  pantalla.setCursor(0,0);

  char accionexamen;                              // NUEVO
  int valorpulsador = digitalRead(pinPulsador);   // NUEVO

  int nubosidad = map(analogRead(pinFotorresistencia), 200, 1023, 100, 0);	// Cuanta más luz, menos nubosidad
  if (nubosidad < 0) {		// Esto impide que haya valores fuera del rango
    nubosidad = 0;
  } else if (nubosidad > 100) {
    nubosidad = 100;
  }
  ColorLED(nubosidad);		// Determina el color del LED RGB según la nubosidad
  

  int temperatura = map(analogRead(pinTermistor), 450, 600, 0, 40);
  Ventilador(temperatura);
  

  float humedad = sensorHumedad.readHumidity();
  int lluvia;
  if (humedad < 67) {
    lluvia = 0;           // Si hay poca humedad, a lluvia se le asigna el valor 0 para impedir que dé algún valor negativo
  } else {
  	lluvia = map(humedad, 67, 100, 0, 50);
  }
  ParpadeoAzul(lluvia);
  

  if (Serial.available() > 0) {             // NUEVO
    accionexamen = Serial.read();           // Esta variable servirá para decir cuándo / cómo se iniciará la estación
  }

  switch (accionexamen) {                               // NUEVO
      case 'q':          // Si el usuario pulsa Q, no hace nada y la ejecución continúa sin más
        accionexamen = '0';                               // Con esto impido que se imprima el mensaje varias veces (aunque en realidad no funcione)
        Accion(nubosidad, temperatura, lluvia);
      break;
      case 'w':          // Si el usuario pulsa W, declara un contador y la ejecución continúa cuando llegue a 5000
        /*unsigned long contadorexamen0 = 0;
        contadorexamen0 = millis();
        if ((contadorexamen0 % 5000) < 10) {*/            // Esto no funcionaba, así que en realidad lo que he hecho es que espere 5 segundos
          accionexamen = '0';
          delay(5000);
          Accion(nubosidad, temperatura, lluvia);
        //}
      break;
      case 'e':        // Si pulsa E y está pulsando el pulsador, la ejecución continúa
        accionexamen = '0';
        if (valorpulsador == 1) {                       // El pulsador se tiene que mantener
          Accion(nubosidad, temperatura, lluvia);
        } else {
          Serial.println("Pulsa el pulsador");
        }
      break;
      case 'r':
        accionexamen = '0';
        delay(5000);
        Serial.println("Pulsa Q para activar la estación, W para activarla dentro de 5 segundos, E para activarla cuando se pulse el botón y R para volver a mostrar este mensaje en 5 segundos");
      break;
      default:
      break;
    }
  
  
  // Una vez se han medido la nubosidad, temperatura, etc., se le pregunta al usuario qué quiere ver en la pantalla LCD
  //Accion(nubosidad, temperatura, lluvia);
}



void Accion(int nubosidad, int temperatura, int lluvia) {
  Serial.println("Pulsa 1 para ver la nubosidad, 2 para ver la temperatura y 3 para ver si llueve");
  char numero;
  
  if (Serial.available() > 0) {         // Para introducir un número y luego otro, entre medias hay que volver a pulsar la letra que hayas pulsado, si no no va
    numero = Serial.read();
    
    switch (numero) {               // Según el número al que el usuario le dé en el teclado, la pantalla LCD muestra ...
    case '1':                           // ... la nubosidad ...
      pantalla.print("Hay un ");
      pantalla.print(nubosidad);
      pantalla.print("%     ");
      pantalla.setCursor(0,1);
      pantalla.print("de nubosidad    ");
      break;
    case '2':                       // ... la temperatura ...
      pantalla.print("La temperatura");
      pantalla.setCursor(0,1);
      pantalla.print("es de ");
      pantalla.print(temperatura);
      pantalla.print(" C       ");
      break;
    case '3':                       // ... o la lluvia
      if (lluvia <= 0) {
        pantalla.print("No llueve        ");
        pantalla.setCursor(0,1);
        pantalla.print("                ");
      } else {
        pantalla.print("Estan cayendo ");
        pantalla.setCursor(0,1);
        pantalla.print(lluvia);
        pantalla.print("nm/s de lluvia");
      }
      break;
    case '4':
      pantalla.setCursor(0,0);
      pantalla.print("                ");
      pantalla.setCursor(0,1);
      pantalla.print("                ");
    break;
    }
  }
}



void ColorLED(int nubosidad) {

  if (nubosidad < 50) {                 // Si hay pocas nubes...
    digitalWrite(pinLuzVerde, HIGH);    // ...el LED luce azul claro
    digitalWrite(pinLuzAzul, HIGH);
  } else {                              // De lo contrario...
    digitalWrite(pinLuzVerde, LOW);     // ...el LED se apaga
    digitalWrite(pinLuzAzul, LOW);
  }
}



void Ventilador(int temperatura) {
  unsigned long contador1 = 0;
  contador1 = millis();

  if (temperatura >= 30) {            // Si hace calor...
    contador1 = millis();
    digitalWrite(pinAlarma, HIGH);    // ...el LED hace un pequeño parpadeo para dar la alarma...
    if (contador1 == 300) {
      digitalWrite(pinAlarma, LOW);
    }
    if (contador1 == 600) {
      digitalWrite(pinAlarma, HIGH);
    }
    if (contador1 == 900) {
      digitalWrite(pinAlarma, LOW);
    }
      if ((contador1 % 500) < 10) {   // ...y el servomotor alterna entre 0 y 180 grados cada medio segundo
   	  motor.write(180);
      } else if ((contador1 % 1001) < 10) {   // Poniendo el < 10 le doy algo de margen de error
      motor.write(0);
      } 
    } else {                          // Si hace frío...
    motor.write(0);                   // ...el servomotor vuelve a su posición original...
    digitalWrite(pinAlarma, LOW);     // ...y el LED de alarma de apaga
  }
}

void ParpadeoAzul(int lluvia) {
  unsigned long contador2 = 0;
  contador2 = millis();
  if (lluvia > 0) {                                   // Si llueve, el LED parpadea
    if (contador2 % (-10 * lluvia + 600) < 5) {       // Cuanta más lluvia, menos tiempo pasa entre los parpadeos
    	digitalWrite(pinLEDLluvia, HIGH);
    }
    if (contador2 % (2 * (-10 * lluvia + 600)) < 5) {
    	digitalWrite(pinLEDLluvia, LOW);
    }
  } else {
    digitalWrite(pinLEDLluvia, LOW);                  // Si no llueve, el LED se apaga
  }
}