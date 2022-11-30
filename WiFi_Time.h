#include <WiFi.h>
#include <Arduino.h>

// Replace with credentials of wifi
const char* ssid = "POCOLoCo";
const char* password = "pochinski";
// Variables to save date and time
String timeStamp;

class WifiTime {
public:
  void setupWifi(void);// configuracion del wifi
  unsigned long getTime(void);// variable para guardar el tiempo actual
};


void WifiTime::setupWifi() {
  // Initialize Serial Monitor
  // Serial.begin(115200);
  Serial.print(F("Connecting for wifitime to "));
  Serial.println(ssid);// name wifi printed
  WiFi.begin(ssid, password); // inicia la coneccion con la red y la contraseña almacenada
  if (WiFi.status() != WL_CONNECTED) {
    delay(5000);// si el status de wiffi es diferente al WL_CONNECTED
    Serial.print(F("...."));
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println(F("WiFi connected."));// imprime que el wifi está conecctado
  Serial.println(F("IP address: ")); // string indicando que imprimirá la ip
  Serial.println(WiFi.localIP());// funcion que despliega la ip local

  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  // México = GMT -6
  timeClient.setTimeOffset(-21600);
}

unsigned long WifiTime::getTime(void) {
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // Extract date
  return timeClient.getEpochTime();
}
