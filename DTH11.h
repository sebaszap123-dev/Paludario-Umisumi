class SensorDth11 {
public:
  void setupSensor(void);
  float getHum(void);
  float getTemp(void);
};

void SensorDth11::setupSensor(void) {
  dht.begin();
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  // float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  //   // Compute heat index in Fahrenheit (the default)
  // float hif = dht.computeHeatIndex(f, h);
  // // Compute heat index in Celsius (isFahreheit = false)
  // float hic = dht.computeHeatIndex(t, h, false);
}

float SensorDth11::getHum(void) {
  // declaramos h con el detectar calor y llamamos a leer humedad
  float h = dht.readHumidity();
  return h;
}

float SensorDth11::getTemp(void) {
  // utilizando detectar calor leemos la temperatura
  float t = dht.readTemperature();
  return t;
}
