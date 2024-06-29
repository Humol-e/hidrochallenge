#include <DHT.h>
#include <HTTPClient.h>
#include "secret.h"
#include <ThingSpeak.h>
#include "sensors.h"
#include <WiFi.h>

SensorData data;

const uint8_t BmePin = 3;

const char *ssid = SECRET_SSID;
const char *pass = SECRET_PASS;
WiFiClient client;
//TIMER 
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
  // put your setup code here, to run once:


  Serial.begin(115200);
  ThingSpeak.begin(client);
  connectWiFi();
  startMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:

 if (millis() >= timerDuration + startMillis)
  {

    apiTemperature = getTemperatureFromApi();

    Serial.println("Temperatura de la API: " + apiTemperature + "*C");   
    delay(50);
    sendDataToThinkSpeak();
    delay(60000);
    //reinico
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

  float Tempi = data.altitud;
  ThingSpeak.setField(1, Tempi);
  


  String status;



  ThingSpeak.setStatus(status);

  int code = ThingSpeak.writeFields(SECRET_CH_ID, SECRET_WRITE_APIKEY);
  if(code == 200){
    Serial.println("Canal thinkspeak actualizado.");
  } else {
    Serial.println("Hubo un problema al actualizar datos. ERROR HTTP: " +  String(code));
  }
 }

//-----------------------------------------------------------
 String getTemperatureFromApi()
 {
    if (WiFi.status() != WL_CONNECTED){
          Serial.println("No estas conectado a la red");
          connectWiFi();
        }

  HTTPClient http;

  http.begin(OPENWEATHER_REQUEST_PATH);
  String temperature;
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200){
      String payload = http.getString();

      //filtrar temp
      int index = payload.indexOf("\"temp\":");
      temperature = payload.substring(index + 7, payload.indexOf(",\"feels_"));

  } else {
    Serial.println("Peticion get fallo, codigo de Error");
    Serial.println(httpResponseCode);
    temperature = "0.0"; // debido a q fallo no tiene datos

  }
http.end();

return temperature;
 }
