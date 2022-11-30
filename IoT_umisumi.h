/**************************************************************
*                                                                            *
       NOMBRE:      Práctica #2.
       FECHA:       25 de Noviembre de 2022.
       VERSIÓN:     1.0.
*                                                                            *
       AUTOR:       Esli Castellanos Berján.
       E-MAIL:      esli_castellanos@ucol.mx.
       FACULTAD:    Telemática.
       CARRERA:     Ingeniería en Tecnologías de Internet.
       MATERIA:     Sistemas embebidos para el Internet de las cosas.
*                                                                            *
       MICROCONTROLADOR:          Xtensa® dual­core 32­bit LX7.
       MARCA COMERCIAL:           ESP32.
*                                                                            *
*                                                                            *
*******************************************************************
*                                                                            *
       DESCRIPCIÓN DEL PROGRAMA:
       .
*                                                                            *
       DETALLES:
       RTC:        .
       MicroSD:    Genérico.
*                                                                            *
**************************/

/*-----------RTC componente------------*/
#include <RTClib.h>
#include "RTC.h"
RTCDate RTC;
/*-----------WIFI------------*/

#include <WiFi.h>
WiFiClient ESP32_WIFI;
/*-----------PUB MQTT Client------------*/
#include <PubSubClient.h>
PubSubClient client(ESP32_WIFI);
/*-----------MQTT------------*/
#include "MQTT.h"
MQTT_ESP32 MQTT;
/*-----------WIFI DATE ------------*/
#include <NTPClient.h>
#include <WiFiUdp.h>
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
#include "WiFi_Time.h"
WifiTime waifu;

/*SENSORES (DTH11)*/
#include <DHT.h>

#define DHTPIN 4  // Digital pin connected to the DHT sensor

/*Definir el tipo de Sensor DHT.*/
#define DHTTYPE DHT11
/*Instancia del sensor de DHT11.*/
DHT dht(DHTPIN, DHTTYPE);
#include "DTH11.h"
/*Instancia de la clase SensorDth11.*/
SensorDth11 TH;


/*----------Display gestor-------------*/
#include "DISPLAY.h"
DisplayInfo DSP;

/*----------Actuadores-------------*/
#include "Actuadores.h"
Actuadores ACT;

/*~~~~~~~~~~~~Componentes de la microSD~~~~~~~~~~~~~~~~~~~~*/
#define MICROSD_PIN 5  // Pin de control de la microSD.
#include <SPI.h>       // Protocolo de comunicación SPI.
#include <SD.h>        // Librería de gestión de la MicroSD.
File MICROSD_FILE;
#define EXTENSION ".json" /*Definimos la extension que se usara para el archivo*/

#include "JSON.h"
mi_json JSON; /*Instancia de la clase mi_json.*/

#include "MicroSD.h"
MicroSD MSD;  /*Instancia de la clase MicroSD.*/

#include "Task.h"
Task tsk; /*Instancia de la clase Task.*/
