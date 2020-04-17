//Juan Jesús Gómez Sánchez
//GDS0152
//Proyecto Final IoT
//03-Abril-2020

//Libreria ESP32
#include <WiFi.h>

//Libreria FireBase
#include <FirebaseArduino.h>

//Libreria Sensor DHT11
#include <DHT.h>

//Dirección IP del Proyecto Desde FireBase
#define FIREBASE_HOST "https://domotica-f8192.firebaseio.com/"

//Key Secreta Generada por FireBase
#define FIREBASE_AUTH "0H6c4jIe6WtGh6w1OYdiV9WhPLsQQ7IadfHUTVoQ"

//Nombre de la Red WiFi (SSID)
#define WIFI_SSID "INFINITUMfbu8" 

//Contraseña de la Red WiFi
#define WIFI_PASSWORD "8B67GFBAD0"

//Pin en el que Estará Conectado el Sensor DHT11 
#define DHTPIN D4

//Tipo de Sensor
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);                                                     

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  delay(1000);

  //Conexión Con WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  //Imprimir el Nombre de la Red
  Serial.print("Conectando a: ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Conectado a: ");
  Serial.println(WIFI_SSID);

  //Imprimir la Dirección IP Local
  Serial.print("La dirección IP es : ");
  Serial.println(WiFi.localIP());

  //Conexión a FireBase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //Iniciar la Lectura con el Sensor DHT11
  dht.begin();
}

void loop() { 
  // put your main code here, to run repeatedly:
  
  //Lectura de la Humedad
  float h = dht.readHumidity();

  //Lectura de Temperatura en °C
  float t = dht.readTemperature();

  //Condición para Verificar que no Falle Alguna Lectura (En Caso de Fallar, lo Vuelve a Intentar)
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falla al leer los datos del sensor DHT11!"));
    return;
  }
  
  //Mostrar Humedad
  Serial.print("Humedad: ");  Serial.print(h);

  //Convertir la Humedad de Entero a Cadena
  String fireHumid = String(h) + String("%"); 
  
  //Mostrar Temperatura
  Serial.print("%  Temperatura: ");  Serial.print(t);  Serial.println("Â°C ");

  //Convertir la Temperatura de Entero a Cadena
  String fireTemp = String(t) + String("Â°C");
  delay(4000);

  //Configuración de las Rutas y Envío de las Lecturas
  Firebase.pushString("/domotica/Humedad", fireHumid);
  Firebase.pushString("/domotica/Temperatura", fireTemp);
   
}
