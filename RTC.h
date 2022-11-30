// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h" // libreria RTC
#include <Arduino.h>// libreria arduino
RTC_DS1307 rtc; // // declaramos los pines como rtc

class RTCDate {
public:
  String _date = "", _time = "", _dayOfWeek = ""; // string con el tiempo y el dia de la semana
  uint8_t _day = 0, _month = 0, _second = 0, _minute = 0, _hour = 0;// dia, mes, segundos y minutos
  uint16_t _year = 0; // el año

public:
  void setupDate(unsigned long); // asignamos la fecha
  void getDayWeekMonth(void);// variable publica consiguiendo el dia y semana del mes 
  void get_time(void);// obtener el tiempo
  void format_date(char);// formateo de la fecha
  void format_time(void);//formateo del tiempo
};

void RTCDate::setupDate(unsigned long datetime) {
// mientras que el reloj éste encendido
  while (!rtc.begin()) {
// imprimimos datos en el puerto serial como texto
    Serial.println(F("Revisa que el reloj esté conectado correctamente"));
    delay(500); 
  }
  if(datetime == 0){
    return;
  }
  if (!rtc.isrunning()) {// si rtc esta corriendo, pedir que se ajuste la hora
    Serial.println(F("RTC is NOT running, let's set the time!"));
    rtc.adjust(DateTime(datetime)); //colocamos la fecha con Datetime y usando el ajuste dentro del rtc
  }
  // rtc.adjust(DateTime(datetime));
}

void RTCDate::getDayWeekMonth(void) {
  DateTime now = rtc.now(); //hora actual
  String myDate;// string con futura fecha
  // Days
  char daysOfTheWeek[7][12] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
  _dayOfWeek = daysOfTheWeek[now.dayOfTheWeek()];//guardamos el dia de la semana
}

void RTCDate ::get_time(void) {

  DateTime now = rtc.now(); // hora actual
  _year = now.year(); // año  actual
  _month = now.month(); // mes actual
  _day = now.day(); // dia actual
  _hour = now.hour(); // hora actual
  _minute = now.minute(); // minutos de la hora actual
  _second = now.second(); // los segundos de la hora actual
}

void RTCDate ::format_time(void) {

  _time = "";
  if (_hour < 10) _time += '0';
  _time += _hour;
  _time += ':'; // formateamos la hora para que se vea bonito (un cero al inicio) si es menor que 10

  if (_minute < 10) _time += '0';
  _time += _minute;//formato con un cero al inicio si los minutos son menores que 10
  // _time += ':';

  //  if ( _second < 10)  _time += '0';
  // _time += _second;//formato de segundos con un cero al inicio
}

void RTCDate::format_date(char character) {

  _date = "";
  if (_day < 10) _date += '0';
  _date += _day;// formateo de fecha con un 0 al inicio si el dia es menor a 10
  _date += character;

  if (_month < 10) _date += '0';
  _date += _month;// añade un  0 al inicio del mes si el mes es menor que 10
  _date += character;

  //if ( _year < 10)  _date += '0';
  _date += _year; // añade un 0 al inicio del año si es menor que 10
}
