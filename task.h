#define _2 2000
#define _5 5000
#define _6 6000
#define _10 10000
#define _20 20000
#define _30 30000
#define _5m 300000

uint8_t melodyToPlay = 0; // melodia 0 a tocar
uint8_t tempoToPlay = 4; // tempo en el que va sonar la cancion

class Task {

  public:
    unsigned long currentMillis = 0,
                  time_2s = 0,
                  time_5s = 0,
                  time_6s = 0,
                  time_10s = 0,
                  time_20s = 0,
                  time_30s = 0,
                  time_5m = 0; //intervalos de tiempo

  public:
    void task_2s(void);
    void task_5s(void);
    void task_6s(void);
    void task_10s(void);
    void task_20s(void);
    void task_30s(void);
    void task_5m(void);//
    void setup_app(void);// setup de la app (ésta)
    void loop_app(void);// loopeamos app
};

void Task ::setup_app(void) {
  waifu.setupWifi(); // wifi secundario = waifu se conecta al cliente y inicia la antena para conectar el wifi
  MQTT.MQTT_setup_WIFI();//se inicia el wifi al servidor mqtt
  MQTT.MQTT_setserver();// se inicia el server
  if (WiFi.status() == WL_CONNECTED) {
    DSP.initLCD(true);// si el wifi esta conectado inicializamos la LCD
    RTC.setupDate(waifu.getTime());// se ajusta la fecha usando el waifu (servidor con wifi)
  } else {
    DSP.initLCD(false); // se inicia la lcd sin el internet
    RTC.setupDate(0);// se ajusta la fecha del RTC a 0
  }
  // setup sensor humedad temp
  ACT.setup_act(); // inicializamos actuadores
  TH.setupSensor();// inicialisamos los sensores temperatura y humedad
  MSD.MicroSD_init();// inicialisamos la micro SD
}

void Task ::task_2s(void) {
  if (currentMillis - time_2s >= _2) {
    time_2s = currentMillis;//toma los milisegundos actuales en la variable
  }
}

void Task ::task_5s(void) {

  if (currentMillis - time_5s >= _5) {//imprime la fecha y la hora en el display usando RTC
    DSP.printDateHour(RTC._dayOfWeek, RTC._date, RTC._time);
    if (WiFi.status() == WL_CONNECTED) {
      MQTT.MQTT_reconnect();// si el wifi esta conectado, intentamos reconectar el servidor
    }
    time_5s = currentMillis; // se establecen los milisegundos actuales
  }
}

void Task ::task_6s(void) {
  if (currentMillis - time_6s >= _6) {
    DSP.printSensor(String(TH.getTemp()), String(TH.getHum()));
    time_6s = currentMillis;// imprimimos la temperatura y guardamos los milisegundos actuales
  }
}

void Task ::task_10s(void) {

  if (currentMillis - time_10s >= _10) {
    // Serial.println(JSON.CreateJson());
    ACT.active_luces();//si la fotoresistencia detecta ausencia de luz enciende los leds
    MSD.MicroSD_save();
    if (WiFi.status() == WL_CONNECTED) {
      if (ACT._fotoResistencia || ACT._ventilador) {
        MQTT.MQTT_publish(JSON.CreateJson());
        MQTT.MQTT_publish(JSON.CreateJsonAct());
        Serial.println(F("Se ha publicado un mensaje"));
      }
    }
    time_10s = currentMillis;// guarda milisegundos actuales
  }
}
void Task ::task_20s(void) {
  if (currentMillis - time_20s >= _20) {
    ACT.active_vent();//activa los ventilladores dependiendo de la temperatura actual,
    time_20s = currentMillis;//guarda milisegundos
  }
}
void Task ::task_30s(void) {
  if (currentMillis - time_30s >= _30) {
    ACT.music(music);// activa la musica
    time_30s = currentMillis;// guarda milisegundos
  }
}
void Task ::task_5m(void) {
  if (currentMillis - time_5m >= _5m) {
    if (WiFi.status() == WL_CONNECTED) {
      setup_app();// si tiene conexion wifi vuelve a iniciar la aplicación
    }
    time_5m = currentMillis;// guardamos el tiempo actual
  }
}
void Task ::loop_app(void) {
  task_2s(); // Tarea de dos segundos
  task_5s(); // Tarea de cinco segundos
  task_6s();// Tarea de seis segundos
  task_10s();// Tarea de diez segundos
  task_20s();// Tarea de veinte segundos
  task_30s();// Tarea de treinta segundos
  task_5m();// Tarea de cinco minutos
}
