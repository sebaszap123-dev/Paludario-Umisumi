#include <Wire.h> // Libreria wire
#include <LiquidCrystal_I2C.h> //Libreria liquid crystal
#include <Arduino.h> // La confiable libreria de arduino

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
// grade to display 35 °C write(0)
byte grade[8] = {
  0b01111,
  0b01001,
  0b01001,
  0b01111,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
// Heart for init of display write(1)
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};
// Porcent to display
byte porcent[8] = {
  B00000,
  B11001,
  B11011,
  B00110,
  B01100,
  B11011,
  B10011,
  B00000
};

class DisplayInfo {
public:
  void initLCD(bool); // imprime el valor de LCD
  void initMessage(void); // imprime el valor  inicial del mensaje
  void wifiOffMessage(void); // imprime el valor del wifi, si está activo o no
  void printSensor(String, String); // imprimir el sensor
  void printDateHour(String, String, String); // Imprimir la fecha y la hora
};

void DisplayInfo::initLCD(bool value) {
  Wire.begin(); // iniciaalizamos wire
  lcd.begin(lcdColumns, lcdRows); // inicializamos lcd, declaramos las columnas y las filas
  lcd.init(); // iniciamos lcd
  lcd.clear(); // limpiamos lcd
  // define chart in 0 pos
  lcd.createChar(0, heart);
  // define chart in 1 pos
  lcd.createChar(1, grade);
  lcd.home();
  // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  if (value == true) {
    initMessage();
  } else {
    wifiOffMessage();
  }
}
void DisplayInfo::initMessage(void) {
  lcd.setCursor(0, 0);  // nos colocamos al inicio del lcd
  lcd.print("IOT 5 semestre"); // imprimimos en el lcd
  lcd.setCursor(0, 1);// ahora nos colocamos un espacio despues
  lcd.print("software ");// imprimimos software
  lcd.write(0);// llamamos al caracter declarado en la posicion 0
  lcd.print(" 2022");//imprimimos 2022
}
void DisplayInfo::wifiOffMessage(void) {
  lcd.setCursor(0, 0);// nos colocamos al inicio del lcd
  lcd.print("IOT 5 semestre"); // imprimimos en el lcd
  lcd.setCursor(0, 1);// ahora nos colocamos un espacio despues
  lcd.print("WIFI apagado reiniciar para reconectar");// imprimimos wifi
  lcd.write(0);// llamamos al caracter declarado en la posicion 0
}

void DisplayInfo::printSensor(String temp, String hum) {
  lcd.clear(); //limpiamos la lcd
  lcd.setCursor(0, 0); // nos colocamos al inicio de lcd
  lcd.print("temp: ");//immprimimos el string temp
  lcd.print(temp);// imprimimos la variable temp
  lcd.write(1);// llamamos al caracter declarado en la posicion 1
  lcd.print("C");//imprimimos c
  lcd.setCursor(0, 1);// colocamos el cursor un espacio adelante
  lcd.print("humedad:");// imprimimos humedad
  lcd.print(hum);// imprimimos el contenido de la variable hum
  lcd.print("%");// imprimimos %
}

void DisplayInfo::printDateHour(String day, String date, String hour) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(day);
  lcd.print(" ");
  lcd.print(date);
  lcd.setCursor(0, 1);
  lcd.print(hour);
}