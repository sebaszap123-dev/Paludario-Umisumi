#include "IoT_umisumi.h"
void setup() {
  // Iniciar el Serial
  Serial.begin(115200);
  /*-----Inicar tareas de inicialización------*/
  tsk.setup_app();
}

void loop() {
  /*-----Actualizar siempre los millis a la clase Task------*/
  tsk.currentMillis = millis();
  /*-----Llama las tareas que estarán en loop------*/
  tsk.loop_app();
}
