const char* AP_NAME = "POCOLoCo"; // el nombre de la red wifi
const char* AP_PWD = "pochinski"; // la contraseña
const char* MQTT_SERVER = "broker.emqx.io"; // declaramos el broker del servidor MQTT
const char* MQTT_CLIENT = "mqttx_ba543f98";// declaramos el cliente
#define MQTT_PORT 1883 // definimos el puerto que va a ocupar el MQTT
const char* MQTT_TOPIC_CONFIG = "/UMI/PAL/IN"; //
const char* MQTT_TOPIC_PUBLISH = "/UMI/PAL";

/*Para la musiquita chida*/
bool music = false;
/*-------Obtiene la trama entrante y muestra el mensaje en el puerto Serial------*/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  /* --------Si recibe 1 encender la musica-------- */
  if ((char)payload[0] == '1') {
    Serial.println(payload[0]);
    Serial.println("encender musica");
    music = true;
  } else {
    /* --------Apagar la musica-------- */
    Serial.println("apagar musica");
    music = false;
  }
}


class MQTT_ESP32 {

  public:
    /*-----Suscribirse al topic------*/
    void MQTT_subscribe(void);
    /*-----Publicar al topic------*/
    void MQTT_publish(String);
    /*-----Conectarse al wifi------*/
    void MQTT_setup_WIFI(void);
    /*-----Conectarse broker mqtt------*/
    void MQTT_setserver(void);
    /*-----Reconectarse al topic------*/
    void MQTT_reconnect(void);
};


void MQTT_ESP32 ::MQTT_subscribe(void) {
  client.subscribe(MQTT_TOPIC_CONFIG);
}

void MQTT_ESP32 ::MQTT_publish(String message) {

  client.publish(MQTT_TOPIC_PUBLISH, message.c_str());
}

void MQTT_ESP32 ::MQTT_setserver(void) {
  /*-----Definir el puerto y server a conectarse------*/
  client.setServer(MQTT_SERVER, MQTT_PORT);
  /*-----Definir que hará cuando reciba un callback del broker------*/
  client.setCallback(callback);
}

void MQTT_ESP32 ::MQTT_setup_WIFI(void) {

  delay(10);
  Serial.print(F("Conectando a "));
  Serial.print(AP_NAME);
  Serial.print(" ");
  /*-----Iniciar y configurar el wifi------*/
  WiFi.begin(AP_NAME, AP_PWD);
  if (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(F("...."));
  }

  Serial.print(F("Se ha conectado de manera exitosa al APcon la dirección "));
  Serial.println(WiFi.localIP());
}

void MQTT_ESP32 ::MQTT_reconnect() {

  if (!client.connected()) {
    while (!client.connected()) {
      Serial.println(F("Conectando al servidor MQTT "));
      Serial.print(MQTT_SERVER);
      /*-----Crear cliente random para conectarse al broker------*/
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      if (client.connect(clientId.c_str())) {

        Serial.println(F("Se ha suscrito a "));
        Serial.println(F(MQTT_TOPIC_CONFIG));
        MQTT_subscribe();

      } else {
        Serial.print(F("Revisar configuraciones, llama a el equipo umisumi!"));
        Serial.print(client.state());
        Serial.println(F("Intentando nuevamente"));
      }
    }
  }
  /*-----Ciclo para escuchar recibir datos y enviar------*/
  client.loop();
}
