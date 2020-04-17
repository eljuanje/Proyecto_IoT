//Juan Jesús Gómez Sánchez
//GDS0152
//Proyecto Final IoT
//03-Abril-2020

//Libreria para comunicación de otros pines digitales
#include <SoftwareSerial.h>

//Libreria para usar el servomotor
#include <Servo.h>

//Variable Servo
Servo servo;


//Conexión de los pines de Transmisión (TX) y Recepeción (RX) del Bletooth
int pinBluetoothTX = 10;
int pinBluetoothRX = 11;

SoftwareSerial bluetooth(pinBluetoothTX, pinBluetoothRX);

//Conexión del servo
int pinServo = 9;

//Conexión del led
int led = 4;

//Variable para Almacenar la letra enviada por la aplicación
char letra;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

  //Asociación del servo con el pin 9
  servo.attach(pinServo);

  //Girar servo 140°
  servo.write(140);
  bluetooth.begin(9600);

  //Indicación de salida para el led
  pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Comprobar que el bluetooth esté disponible
  if(bluetooth.available() > 0){
    letra = bluetooth.read();
    Serial.println(letra);
  }

  //Controlar encendido de las luces ('E')
  if(letra == 'E'){
    Serial.println("Led Encendido");
    digitalWrite(led, HIGH);
  }
  
  //Controlar Apagado de las luces
  if(letra == 'A'){
    Serial.println("Luces Apagadas");
    digitalWrite(led, LOW);
  }

  //Controlar la puerta (Abrir)
  if(letra == 'O'){
    Serial.println("Puerta Abierta");
    servo.write(140);
  }

  //Controlar la puerta (Cerrar)
  if(letra == 'C'){
    Serial.println("Puerta Cerrada");
    servo.write(0);
  }

}
