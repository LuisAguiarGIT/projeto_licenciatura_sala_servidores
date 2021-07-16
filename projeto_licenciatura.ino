#include <ESP8266ZabbixSender.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
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
const char* tipoSensor          = "tipoDeExemplo";
const char* itemZabbix          = "umItemZabbix";
uint8_t pinSensor               = 0;
boolean medeTemperatura         = false;
boolean medeHumidade            = false;
long intervaloMedicao           = 0;

// Zabbix
IPAddress ipZabbix;
int portaZabbix                 = 0;
const char* hostZabbix          = "hostDeExemplo";

//Variáveis
long milisAnteriores = 0;
boolean isConnected;

void setup() {
  Serial.begin(9600);
  //isConnected = conectaWifi();
  WiFi.persistent(false);
  Serial.println("Realizando montagem de sistema de ficheiros...");

  if (!LittleFS.begin()) {
    Serial.println("Falha na montagem do sistema de ficheiros!");
    return;
  }
 
  if (!configuraWifi()) {
    Serial.println("Falha na configuração da rede");
  } else {
    Serial.println("Configuração carregada");
  }

  Serial.println(ssid);
  Serial.println(passwordRede);
  WiFi.begin(ssid, passwordRede);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("IP atribuido:");
  Serial.println(WiFi.localIP());

  if (!configuraSensores()) {
      Serial.println("Falha na configuracao dos sensores");
  } else {
      Serial.println("Sensores configurados");
  }

  if (!configuraZabbix()) {
      Serial.println("Falha na configuracao do Zabbix");
  } else {
      Serial.println("Zabbix configurado");
  }

  zSender.Init(ipZabbix, portaZabbix, hostZabbix);
  
//  leFicheiro(ficheiroDados);
//  logErro("Too bad again");
//  leFicheiro(ficheiroLoggerErros);
  LittleFS.end();
}

void loop() {
  leValorSensor(tipoSensor, medeTemperatura, medeHumidade, pinSensor);
}
