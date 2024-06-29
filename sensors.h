#include "esp32-hal-adc.h"
struct SensorData {
    float temperatura;
    float humedad;
    float presion;
    float latitud;
    float longitud;     
    float altitud;
    int estadoFC51;
    int luminosidad;
    float aceleracionX;
    float aceleracionY;
    float aceleracionZ;
    float NivelAgua;
    float giroX;
    float giroY;
    float giroZ;
  


    String getAllSensorData() {
        return "Temperatura: " + String(temperatura) + " *C\n" +
               "Humedad: " + String(humedad) + " %\n" +
               "Presion: " + String(presion) + " hPa\n" +
               "Luz: " + String(luminosidad) + " lux\n" +
               "GPS: " + "Lat: " + String(latitud) + " Long: " + String(longitud) + " Alt: " + String(altitud) + " m\n" +
               "Aceleracion: " + "X: " + String(aceleracionX) + " Y: " + String(aceleracionY) + " Z: " + String(aceleracionZ) + " m/s^2\n" +
               "Nivel del Agua : " + String(NivelAgua) + " cm\n" +
               "Check de Etapa: " + (estadoFC51 ? "True" : "False") + "\n";
    }
};

