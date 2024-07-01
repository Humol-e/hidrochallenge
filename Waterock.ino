#include <HTTPClient.h>
#include "secret.h"
#include <ThingSpeak.h>
#include "sensors.h"
#include <WiFi.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#define RX_PIN 16
#define TX_PIN 17


SoftwareSerial rylr998_RRT(RX_PIN, TX_PIN);

SensorData data;

const uint8_t BmePin = 3;

const char *ssid = SECRET_SSID;
const char *pass = SECRET_PASS;
WiFiClient client;
//Temporizador de envío a thingspeak 
uint8_t startMillis;
const uint16_t timerDuration = 20000;
float temperatureData;

String apiTemperature;
String serverPath = OPENWEATHER_REQUEST_PATH;


//thingspeak
uint32_t channelNumber = SECRET_CH_ID;
const char *writeAPIKey = SECRET_WRITE_APIKEY;
float temperaturaaa = 3;


void sendCmd(String cmd)
{
  Serial2.println(cmd);  // Enviar string cmd a módulo LoRa
  delay(100);  // Esperar 500ms a que el módulo reciba el comando
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));  // Si hay respuesta imprimirla en el monitor serial 
  }
}


void setup() {

  ThingSpeak.begin(client);
  connectWiFi();
  startMillis = millis();
  Serial.begin(115200);  // Iniciar el monitor serial a 115200 baudios
  Serial2.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);  // Iniciar el Serial2 a 115200
  delay(3000);
  Serial.println("Configurando parámetros antena LoRa");
  delay(1000);
  sendCmd("AT+ADDRESS=2");  // Configurar el address a 2
  delay(1000);
  sendCmd("AT+NETWORKID=5");  // Configurar el Network ID a 5
  delay(1000);
  sendCmd("AT+BAND?");  // Leer la frecuencia configurada
  delay(1000);
  sendCmd("AT+PARAMETER?");  // Leer los parámetros configurados
  delay(1000);
  sendCmd("AT+MODE?");  // Leer el modo configurado
  delay(1000);
}

void loop() {
  if (rylr998_RRT.available()) {
    if (rylr998_RRT.find("AT+RECV")) {
      SensorData datos;
      rylr998_RRT.readBytes((uint8_t*)&datos, sizeof(datos));
       Serial.println(datos.temperatura);
       Serial.println(data.saludo);

    }
  }

 if (millis() >= timerDuration + startMillis)
  {
    sendDataToThinkSpeak();
    delay(30000);
    //reinicio
    startMillis = millis();
  }
}

 void connectWiFi(){

  WiFi.begin(ssid, pass);
  Serial.println("Conectando al internet. . .");
  while (WiFi.status() != WL_CONNECTED) 
  {
  Serial.print(".");
  delay(500);
  }
  Serial.println();
  Serial.print("Conectado a: " + (String)ssid + " con la direccion IP de: " + WiFi.localIP());
 }

 
 void sendDataToThinkSpeak(){
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("No hay conexion a Internet");
    connectWiFi();
  } 
  Serial.print("Temperatura: ");
  Serial.println(data.temperatura);

  ThingSpeak.setField(1,data.temperatura);
  ThingSpeak.setField(2,data.humedad);
  ThingSpeak.setField(3,data.presion);
  ThingSpeak.setField(4, data.luminosidad);
  ThingSpeak.setField(5,data.longitud);
  ThingSpeak.setField(6,data.latitud);
  ThingSpeak.setField(7,data.aceleracionX);
  ThingSpeak.setField(8,data.aceleracionY);

  String status;
  ThingSpeak.setStatus(status);

  int code = ThingSpeak.writeFields(SECRET_CH_ID, SECRET_WRITE_APIKEY);
  if(code == 200){
    Serial.println("Canal thinkspeak actualizado.");
  } else {
    Serial.println("Hubo un problema al actualizar datos. ERROR HTTP: " +  String(code));
  }
 }
