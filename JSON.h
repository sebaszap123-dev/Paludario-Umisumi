#include <ArduinoJson.h>// libreria de jason
class mi_json {
  public:


  public:
    /*✈ se dividio en dos ya que el broker no admitia un mensaje tan largo ✈*/
    String CreateJson();
    String CreateJsonAct();
};

String mi_json ::CreateJson() {

  String TempJson;
  DynamicJsonDocument doc(1024);  // Creamos una instancia de un documento JSON.
  // Aquí colocarían las variables de sus sensores.
  // Aquí colocarían las variables del tiempo global.
  /*----Obtener el tiempo del RTC----*/
  RTC.get_time();
  /*----Formatear el tiempo del RTC----*/
  RTC.format_date('/');
  RTC.format_time();
  RTC.getDayWeekMonth();
  doc["fecha"] = RTC._date;
  doc["dia"] = RTC._dayOfWeek;
  doc["tiempo"] = RTC._time;
  // Aquí colocarían las variables de sus actuadores, es preferible almacenar la fecha y hora del momento en que se activó.
  doc["sensor"] = "DTH11";
  JsonArray data = doc.createNestedArray("dth11");
  data.add("temperatura");
  data.add(String(TH.getTemp()));
  data.add("humedad");
  data.add(String(TH.getHum()));
  // doc["buzzer"] = "03:41:25";

  serializeJsonPretty(doc, TempJson);  // Transformamos el objeto en un string.

  return TempJson;
}
String mi_json ::CreateJsonAct() {
  String TempJson;
  DynamicJsonDocument doc(1024);  // Creamos una instancia de un documento JSON.
  // Aquí colocarían las variables de sus sensores.
  // Aquí colocarían las variables del tiempo global.
  doc["ventilador"] = ACT._estadoTemp;
  doc["luces"] = ACT._estadoLuces;
  serializeJsonPretty(doc, TempJson);  // Transformamos el objeto en un string.

  return TempJson;
}
