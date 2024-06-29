#include "esp32-hal-adc.h"
struct SensorData {
    float temperatura;
    float humedad;
    float presion;
    float luz;
    float latitud;
    float longitud;     
    float altitud;
    float aceleracionX;
    float aceleracionY;
    float aceleracionZ;
    float NivelAgua = analogRead(34);
    bool DespegueCheck;
    bool EtapaCheck;
 

    String getAllSensorData() {
        return "Temperatura: " + String(temperatura) + " *C\n" +
               "Humedad: " + String(humedad) + " %\n" +
               "Presion: " + String(presion) + " hPa\n" +
               "Luz: " + String(luz) + " lux\n" +
               "GPS: " + "Lat: " + String(latitud) + " Long: " + String(longitud) + " Alt: " + String(altitud) + " m\n" +
               "Aceleracion: " + "X: " + String(aceleracionX) + " Y: " + String(aceleracionY) + " Z: " + String(aceleracionZ) + " m/s^2\n" +
               "Nivel del Agua : " + String(NivelAgua) + " cm\n" +
               "DespegueCheck : " + (DespegueCheck ? "True" : "False") + "\n"
               "Check de Etapa: " + (EtapaCheck ? "True" : "False") + "\n";
    }
};
