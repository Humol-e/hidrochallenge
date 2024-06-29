#include "esp32-hal-adc.h"
struct SensorData {
    float temperatura;
    float humedad;
    float presion;
    double latitud;
    double longitud;     
    double altitud;
    int estadoFC51;
    int luminosidad;
    float aceleracionX;
    float aceleracionY;
    float aceleracionZ;
    float NivelAgua;
    double giroX;
    double giroY;
    double giroZ;
  


    String getAllSensorData() {
        return "Temperatura: " + String(temperatura) + " *C\n" +
               "Humedad: " + String(humedad) + " %\n" +
               "Presion: " + String(presion) + " hPa\n" +
               "Luz: " + String(luz) + " lux\n" +
               "GPS: " + "Lat: " + String(latitud) + " Long: " + String(longitud) + " Alt: " + String(altitud) + " m\n" +
               "Aceleracion: " + "X: " + String(aceleracionX) + " Y: " + String(aceleracionY) + " Z: " + String(aceleracionZ) + " m/s^2\n" +
               "Nivel del Agua : " + String(NivelAgua) + " cm\n" +
               "Check de Etapa: " + (estadoFC51 ? "True" : "False") + "\n";
    }
};

