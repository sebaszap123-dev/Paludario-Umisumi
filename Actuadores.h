#define OUTPIN_VENT 26 //puerto de salida del ventilador
#define OUTPIN_LIGHT 25// puerto de salida de la luz
#define POTPIN 34//ping análogo de la fotocelda

// const int PIN = 27;

class Actuadores {
    // variables públicas en donde declaremos como false o desactivado la foto, el ventilador y el estado de las luces y el estado temporal
  public:
    bool _fotoResistencia = false;
    bool _ventilador = false;
    String _estadoLuces = "desactivado", _estadoTemp = "desactivado";
  public:
    // variables públicas donde declaramos el setup del actuador, las ventilas activas, las luces activas y la música
    void setup_act(void);
    void active_vent(void);
    void active_luces(void);
    void music(bool);
  private:
    // declaramos el pin de la fotocelda para revisar si está activo o desactivada
    bool fotocell(void);
};

void Actuadores::setup_act() {
  // pinmode configura los puertos de entrada  y de salida
  // configuramos el el pin de entrada = el pin de salida del ventilador y salida = output
  pinMode(OUTPIN_VENT, OUTPUT);
  // configuramos el el pin de entrada = el pin de salida de la luz y salida = output
  pinMode(OUTPIN_LIGHT, OUTPUT);
}

void Actuadores::active_luces(void) {
  // declaramos valor boleano isActive cómo la funcion fotocell
  bool isActive = fotocell();
  // si el estado de el actuador está activado
  if (isActive == true) {
    // imprimimos en el puerto serial que las luces (actuadores) están encendidas
    Serial.print(F("luces encendidas"));
    // Establecemos que el valor de las fotoresistencias es true = encendido
    _fotoResistencia = true;
    // Establecemos que las luces están activas
    _estadoLuces = "activado";
  } else {
    // Apagamos las luces
    digitalWrite(OUTPIN_LIGHT, LOW);
    // Imprime en el puerto serial que las luces están apagadas
    Serial.print(F("luces apagadas"));
    // Declaramos a la foto resistencia como false = apagada
    _fotoResistencia = false;
    // Declaramos el estádo de las luces como desactivado = aoagadas
    _estadoLuces = "desactivado";
  }
}
void Actuadores::active_vent(void) {
  // si la temperatura de la temperatura y la humedad excede a los 24 grados
  if (TH.getTemp() > 24) {
    // Encender ventiladores algo si esta muy caliente (24 grados celsius)
    digitalWrite(OUTPIN_VENT, HIGH);
    // Imprimimos en el puerto serial que el ventilador está apagado
    Serial.print(F("ventilador encendido"));
    // Establecemos que el ventilado está prendido = true
    _ventilador = true;
    // Establecemos que el estado del ventilador es el activado
    _estadoTemp = "activado";
  } else {
    // Apagar ventiladores si esta muy caliente (24 grados celsius)
    digitalWrite(OUTPIN_VENT, LOW);
    // Imprimimos datos en el puerto serial que el ventilador esta apagado.
    Serial.print(F("ventilador apagado"));
    // establesemos que el ventilador está apagado = false
    _ventilador = false;
    // establecemos que el estado de este es el desactivado
    _estadoTemp = "desactivado";
  }
}
/*-----Verificar si hay presencia de luz------*/
bool Actuadores::fotocell(void) {
  /*-----Obtenemos la lectura analoga de la fotocelda------*/
  int potValue = analogRead(POTPIN);
  // Cuando le da luz retorna 0 entonces apagar si es mayor a 0
  /*-------Estados observables 0 y 4095-------*/
  if (potValue < 1) {
    /* Apagar si el valor es menor a 1 (a) (es de día)*/
    digitalWrite(OUTPIN_LIGHT, LOW);
    return false;
  } else {
    /* Encender si el valor es menor a 1 (a) (es de día)*/
    digitalWrite(OUTPIN_LIGHT, HIGH);
    return true;
  }
}
/*😂Encender o apagar la música (Si funcionara con el pin verdad)😂*/
void Actuadores::music(bool value) {
  if (value == false) {
    //si el valor es falso escribe un valor bajo al pin digital de la variable
    digitalWrite(PIN, LOW);
    // imprime en el serial
    Serial.println("music low");
  } else {
    // en caso de ser verdadero escribe el valor alto en el pin digital de la variable
    digitalWrite(PIN, HIGH);
    // imprime en el serial
    Serial.println("music high");
  }
}
