class MicroSD {

public:
  String filename = "";

public:
  void MicroSD_init(void);
  void MicroSD_save(void);
  void FileID(void);
};

void MicroSD ::MicroSD_init(void) {
// iniciamos SD en el pin indicado para el modulo de la micro SD
  while (!SD.begin(MICROSD_PIN)) {

    Serial.println(F("Error en la detección de la memoria, Revisar conexiones"));
    delay(2000);
  }

  Serial.println(F("Se ha detectado el módulo MicroSD exitosamente."));
}

void MicroSD ::MicroSD_save(void) {

  FileID(); 
  MICROSD_FILE = SD.open(filename, FILE_APPEND); // abrimos un archivo de la sd y adjuntamos un file 

  if (MICROSD_FILE) {

    MICROSD_FILE.println("Saving...");// imprimimos que está guardando el archivo
    MICROSD_FILE.println(JSON.CreateJson());// crea el Json
    MICROSD_FILE.close();// cerramos el archivo
    // json sensores
    Serial.println(F("Se ha almacenado correctamente la información"));

  }

  else {
    Serial.println(F("Error contacta a un ingeniero! "));
  }
}

void MicroSD ::FileID(void) {

  filename = "/";
  RTC.get_time();
  RTC.format_date('-');
  filename += RTC._date;
  filename += EXTENSION;
}
