#include <ESP8266ZabbixSender.h>
#include <ESP8266WiFi.h>
#include <dht.h>
//#include <DHT.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include "LittleFS.h"

//Constantes
#define INTERVALO 1000
#define DHTTYPE11 DHT11
#define DHTTYPE22 DHT22
ESP8266ZabbixSender zSender;

//Rede wifi
const char* ssid                = "aSuaRede";
const char* passwordRede        = "aSuaPasse";

//Ficheiros
const char* ficheiroConfig      = "/config.json";
const char* ficheiroDados       = "/DadosMedicao.txt";
const char* ficheiroLoggerErros = "/LoggerErros.txt";

//Sensores
  //Sensor 1
String tipoSensor1          = "tipoDeExemplo";
String itemZabbix1          = "umItemZabbix";
uint8_t pinSensor1               = 0;
boolean medeTemperatura1         = false;
boolean medeHumidade1            = false;
long intervaloMedicao1           = 0;
   //Sensor 2
String tipoSensor2          = "tipoDeExemplo";
String itemZabbix2          = "umItemZabbix";
uint8_t pinSensor2               = 0;
boolean medeTemperatura2         = false;
boolean medeHumidade2            = false;
long intervaloMedicao2           = 0;
  //Sensor 3
String tipoSensor3          = "tipoDeExemplo";
String itemZabbix3          = "umItemZabbix";
uint8_t pinSensor3               = 0;
boolean medeTemperatura3         = false;
boolean medeHumidade3            = false;
long intervaloMedicao3           = 0;
  //Sensor 4
String tipoSensor4          = "tipoDeExemplo";
String itemZabbix4          = "umItemZabbix";
uint8_t pinSensor4               = 0;
boolean medeTemperatura4         = false;
boolean medeHumidade4            = false;
long intervaloMedicao4           = 0;
  //Sensor 5
String tipoSensor5          = "tipoDeExemplo";
String itemZabbix5          = "umItemZabbix";
uint8_t pinSensor5               = 0;
boolean medeTemperatura5         = false;
boolean medeHumidade5            = false;
long intervaloMedicao5           = 0;
  //Sensor 6
String tipoSensor6          = "tipoDeExemplo";
String itemZabbix6          = "umItemZabbix";
uint8_t pinSensor6               = 0;
boolean medeTemperatura6         = false;
boolean medeHumidade6            = false;
long intervaloMedicao6           = 0;
  //Sensor 7
String tipoSensor7          = "tipoDeExemplo";
String itemZabbix7          = "umItemZabbix";
uint8_t pinSensor7               = 0;
boolean medeTemperatura7         = false;
boolean medeHumidade7            = false;
long intervaloMedicao7           = 0;
  //Sensor 8
String tipoSensor8          = "tipoDeExemplo";
String itemZabbix8          = "umItemZabbix";
uint8_t pinSensor8               = 0;
boolean medeTemperatura8         = false;
boolean medeHumidade8            = false;
long intervaloMedicao8           = 0;

// Zabbix
IPAddress ipZabbix;
int portaZabbix                 = 0;
const char* hostZabbix          = "hostDeExemplo";

//Variáveis
long previousMillis = 0;
long intervaloMedicao = 60000;
boolean isConnected;
boolean loadedConfig = false;
float temperatura = 0;

dht DHT;

void setup() {
  Serial.begin(9600);
  WiFi.persistent(false);
  isConnected = conectaWifi();
  Serial.println("Realizando montagem de sistema de ficheiros...");

  if (!LittleFS.begin()) {
    Serial.println("Falha na montagem do sistema de ficheiros!");
    return;
  }

  if (!loadedConfig) {
    if (!loadConfig()) {
      Serial.println("Falha na configuração");
      logErro("Ficheiro configuração mal configurado");
    } else {
      Serial.println("Configuração carregada");
      loadedConfig = true;
    }
  }

  WiFi.begin(ssid, passwordRede);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  isConnected = true;
  Serial.println("IP atribuido:");
  Serial.println(WiFi.localIP());
  
  leFicheiro(ficheiroDados);
  leFicheiro(ficheiroLoggerErros);

  LittleFS.end();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > intervaloMedicao) {
    previousMillis = currentMillis;
    if (isConnected) {
      enviaDados(tipoSensor1, itemZabbix1, medeTemperatura1, medeHumidade1, pinSensor1);
      enviaDados(tipoSensor2, itemZabbix2, medeTemperatura2, medeHumidade2, pinSensor2);
      enviaDados(tipoSensor3, itemZabbix3, medeTemperatura3, medeHumidade3, pinSensor3);
      enviaDados(tipoSensor4, itemZabbix4, medeTemperatura4, medeHumidade4, pinSensor4);
      enviaDados(tipoSensor5, itemZabbix5, medeTemperatura5, medeHumidade5, pinSensor5);
      enviaDados(tipoSensor6, itemZabbix6, medeTemperatura6, medeHumidade6, pinSensor6);
      enviaDados(tipoSensor7, itemZabbix7, medeTemperatura7, medeHumidade7, pinSensor7);
      enviaDados(tipoSensor8, itemZabbix8, medeTemperatura8, medeHumidade8, pinSensor8);
    } else {
      setup();
    }
  }
}
