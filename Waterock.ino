
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

#define RX_PIN 4
#define TX_PIN 5

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

void setup() {

  Serial.begin(115200);
  ThingSpeak.begin(client);
  connectWiFi();
  startMillis = millis();
  rylr998_RRT.begin(9600);
}

void loop() {
  if (rylr998_RRT.available()) {
    if (rylr998_RRT.find("AT+RECV")) {
      SensorData datos;
      rylr998_RRT.readBytes((uint8_t*)&datos, sizeof(datos));

            Serial.println(datos.temperatura);

    }
  }

 if (millis() >= timerDuration + startMillis)
  {
    sendDataToThinkSpeak();
    delay(60000);
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
  ThingSpeak.setField(1,1);
  ThingSpeak.setField(2,1);
  ThingSpeak.setField(3,1);
  ThingSpeak.setField(4, data.temperatura);
  ThingSpeak.setField(5,1);
  ThingSpeak.setField(6,1);
  ThingSpeak.setField(7,1);
  ThingSpeak.setField(8,1);
  
  String status;
  ThingSpeak.setStatus(status);

  int code = ThingSpeak.writeFields(SECRET_CH_ID, SECRET_WRITE_APIKEY);
  if(code == 200){
    Serial.println("Canal thinkspeak actualizado.");
  } else {
    Serial.println("Hubo un problema al actualizar datos. ERROR HTTP: " +  String(code));
  }
 }
