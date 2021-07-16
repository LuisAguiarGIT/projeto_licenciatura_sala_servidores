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
long intervaloMedicao = 10000;
boolean isConnected;
float temperatura = 0;

dht DHT;

void setup() {
  Serial.begin(9600);
  //isConnected = conectaWifi();
  WiFi.persistent(false);
  Serial.println("Realizando montagem de sistema de ficheiros...");

  if (!LittleFS.begin()) {
    Serial.println("Falha na montagem do sistema de ficheiros!");
    return;
  }
 
  if (!loadConfig()) {
    Serial.println("Falha na configuração da rede");
  } else {
    Serial.println("Configuração carregada");
  }

  WiFi.begin(ssid, passwordRede);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  isConnected = true;
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
    } else {
      setup();
    }
  }
}

boolean loadConfig() {
  File ficheiroConfig = LittleFS.open("/config.json", "r");
  if (!ficheiroConfig) {
    Serial.println("Nao existe ficheiro config");
    return false;
  }

  size_t size = ficheiroConfig.size();
  if (size > 4096) {
    Serial.println("Ficheiro de configuração demasiado grande");
    return false;
  }

  std::unique_ptr<char[]> buf(new char[size]);
  ficheiroConfig.readBytes(buf.get(), size);

  StaticJsonDocument<4096> doc;

  auto error = deserializeJson(doc, buf.get());
  if (error) {
    Serial.println("Erro na analise do ficheiro json");
    return false;
  }
  
  String ipString = (const char*)doc["zabbix"]["ipZabbix"];
  ipZabbix.fromString(ipString.c_str());
  portaZabbix = (int)doc["zabbix"]["portaZabbix"];
  hostZabbix = (const char*)doc["zabbix"]["hostZabbix"];
  ssid = doc["wifi"]["ssid"];
  passwordRede = doc["wifi"]["passwordRede"];
    //Sensor 1
  String tipoSensorString       = doc["sensor1"]["tipoSensor"];
  String itemZabbixString       = doc["sensor1"]["itemZabbix"];
  tipoSensor1 = tipoSensorString;
  itemZabbix1 = itemZabbixString;
  String tipoSensorString2       = doc["sensor2"]["tipoSensor"];
  String itemZabbixString2      = doc["sensor2"]["itemZabbix"];
  tipoSensor2 = tipoSensorString2;
  itemZabbix2 = itemZabbixString2;
  String tipoSensorString3       = doc["sensor3"]["tipoSensor"];
  String itemZabbixString3       = doc["sensor3"]["itemZabbix"];
  tipoSensor3 = tipoSensorString3;
  itemZabbix3 = itemZabbixString3;
  String tipoSensorString4       = doc["sensor4"]["tipoSensor"];
  String itemZabbixString4       = doc["sensor4"]["itemZabbix"];
  tipoSensor4 = tipoSensorString4;
  itemZabbix4 = itemZabbixString4;
  String tipoSensorString5       = doc["sensor5"]["tipoSensor"];
  String itemZabbixString5       = doc["sensor5"]["itemZabbix"];
  tipoSensor5 = tipoSensorString5;
  itemZabbix5 = itemZabbixString5;
  String tipoSensorString6       = doc["sensor6"]["tipoSensor"];
  String itemZabbixString6       = doc["sensor6"]["itemZabbix"];
  tipoSensor6 = tipoSensorString6;
  itemZabbix6 = itemZabbixString6;
  String tipoSensorString7       = doc["sensor7"]["tipoSensor"];
  String itemZabbixString7       = doc["sensor7"]["itemZabbix"];
  tipoSensor7 = tipoSensorString7;
  itemZabbix7 = itemZabbixString7;
  String tipoSensorString8       = doc["sensor8"]["tipoSensor"];
  String itemZabbixString8       = doc["sensor8"]["itemZabbix"];
  tipoSensor8 = tipoSensorString8;
  itemZabbix8 = itemZabbixString8;
  pinSensor1        = (uint8_t)doc["sensor1"]["pinSensor"];
  medeTemperatura1  = (boolean)doc["sensor1"]["medeTemperatura"];
  medeHumidade1     = (boolean)doc["sensor1"]["medeHumidade"];
  intervaloMedicao1 = (long)doc["sensor1"]["intervaloMedicao"];
  //Sensor 2
  pinSensor2        = (uint8_t)doc["sensor2"]["pinSensor"];
  medeTemperatura2  = (boolean)doc["sensor2"]["medeTemperatura"];
  medeHumidade2     = (boolean)doc["sensor2"]["medeHumidade"];
  intervaloMedicao2 = (long)doc["sensor2"]["intervaloMedicao"];
  //Sensor 3
  pinSensor3        = (uint8_t)doc["sensor3"]["pinSensor"];
  medeTemperatura3  = (boolean)doc["sensor3"]["medeTemperatura"];
  medeHumidade3     = (boolean)doc["sensor3"]["medeHumidade"];
  intervaloMedicao3 = (long)doc["sensor3"]["intervaloMedicao"];
  //Sensor 4
  pinSensor4        = (uint8_t)doc["sensor4"]["pinSensor"];
  medeTemperatura4  = (boolean)doc["sensor4"]["medeTemperatura"];
  medeHumidade4     = (boolean)doc["sensor4"]["medeHumidade"];
  intervaloMedicao4 = (long)doc["sensor4"]["intervaloMedicao"];
  //Sensor 5
  pinSensor5        = (uint8_t)doc["sensor5"]["pinSensor"];
  medeTemperatura5  = (boolean)doc["sensor5"]["medeTemperatura"];
  medeHumidade5     = (boolean)doc["sensor5"]["medeHumidade"];
  intervaloMedicao5 = (long)doc["sensor5"]["intervaloMedicao"];
  //Sensor 6
  pinSensor6        = (uint8_t)doc["sensor6"]["pinSensor"];
  medeTemperatura6  = (boolean)doc["sensor6"]["medeTemperatura"];
  medeHumidade6     = (boolean)doc["sensor6"]["medeHumidade"];
  intervaloMedicao6 = (long)doc["sensor6"]["intervaloMedicao"];
  //Sensor 7
  pinSensor7        = (uint8_t)doc["sensor7"]["pinSensor"];
  medeTemperatura7  = (boolean)doc["sensor7"]["medeTemperatura"];
  medeHumidade7     = (boolean)doc["sensor7"]["medeHumidade"];
  intervaloMedicao7 = (long)doc["sensor7"]["intervaloMedicao"];
  //Sensor 8
  pinSensor8        = (uint8_t)doc["sensor8"]["pinSensor"];
  medeTemperatura8  = (boolean)doc["sensor8"]["medeTemperatura"];
  medeHumidade8     = (boolean)doc["sensor8"]["medeHumidade"];
  intervaloMedicao8 = (long)doc["sensor8"]["intervaloMedicao"];
  
  zSender.Init(ipZabbix, portaZabbix, hostZabbix);
  
  ficheiroConfig.close();
  return true;
}
