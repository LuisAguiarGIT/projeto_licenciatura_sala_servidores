void leFicheiro(const char* path) {
  Serial.println("\n--------------------------");
  Serial.printf("Ficheiro a ler: %s\r\n", path);
  File file = LittleFS.open(path, "r");

  if (!file) {
    Serial.println("Erro na abertura do ficheiro");
    return;
  } else {
    Serial.println("Ficheiro aberto com sucesso!");
  }

  Serial.println("\n--------------------------");
  Serial.println("Dados contidos no ficheiro:");
  while(file.available()) {
    Serial.write(file.read());
  }
  Serial.println("\n--------------------------");
  file.close();
}

void escreveDadosFicheiro(String tipoDeSensor, uint8_t pinSensor) {
  if (tipoDeSensor == "null") {
    return;
  }

  LittleFS.begin();
  
  const char* path = "/DadosMedicao.txt";
  File ficheiroDeDados = LittleFS.open(path, "a");
  if (ficheiroDeDados == NULL) {
    printf("Erro na abertura do ficheiro %s", ficheiroDados);
    return;
  }
  
  ficheiroDeDados.print(tipoDeSensor);
  ficheiroDeDados.print(" ");
  ficheiroDeDados.print("Pin: ");
  ficheiroDeDados.print(pinSensor);
  ficheiroDeDados.print(" ");
  ficheiroDeDados.print("T: ");
  ficheiroDeDados.print(temperatura);
  ficheiroDeDados.print(" ");
  ficheiroDeDados.print("H: ");
  ficheiroDeDados.println(humidade);

  ficheiroDeDados.close();
  LittleFS.end();
}

void logErro(char* mensagemDeErro) {
  LittleFS.begin();
  const char* path = "/LoggerErros.txt";
  File ficheiroLoggerErros = LittleFS.open(path, "a");

  if (ficheiroLoggerErros == NULL) {
    printf("Erro na localização do ficheiro %s", path);
    return;
  }

  ficheiroLoggerErros.println(mensagemDeErro);
  ficheiroLoggerErros.close();
  LittleFS.end();
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

  //Plataforma Zabbix
  String ipString = (const char*)doc["zabbix"]["ipZabbix"];
  ipZabbix.fromString(ipString.c_str());
  portaZabbix = (int)doc["zabbix"]["portaZabbix"];
  hostZabbix = (const char*)doc["zabbix"]["hostZabbix"];
  //Rede
  ssid              = doc["wifi"]["ssid"];
  passwordRede      = doc["wifi"]["passwordRede"];
  //Sensores
    //Sensor 2
  tipoSensor1       = (const char*)doc["sensor1"]["tipoSensor"];
  itemZabbix1       = (const char*)doc["sensor1"]["itemZabbix"];
  pinSensor1        = (uint8_t)doc["sensor1"]["pinSensor"];
  medeTemperatura1  = (boolean)doc["sensor1"]["medeTemperatura"];
  medeHumidade1     = (boolean)doc["sensor1"]["medeHumidade"];
  intervaloMedicao1 = (long)doc["sensor1"]["intervaloMedicao"];
    //Sensor 2
  tipoSensor2       = (const char*)doc["sensor2"]["tipoSensor"];
  itemZabbix2       = (const char*)doc["sensor2"]["itemZabbix"];
  pinSensor2        = (uint8_t)doc["sensor2"]["pinSensor"];
  medeTemperatura2  = (boolean)doc["sensor2"]["medeTemperatura"];
  medeHumidade2     = (boolean)doc["sensor2"]["medeHumidade"];
  intervaloMedicao2 = (long)doc["sensor2"]["intervaloMedicao"];
    //Sensor 3
  tipoSensor3       = (const char*)doc["sensor3"]["tipoSensor"];
  itemZabbix3       = (const char*)doc["sensor3"]["itemZabbix"];
  pinSensor3        = (uint8_t)doc["sensor3"]["pinSensor"];
  medeTemperatura3  = (boolean)doc["sensor3"]["medeTemperatura"];
  medeHumidade3     = (boolean)doc["sensor3"]["medeHumidade"];
  intervaloMedicao3 = (long)doc["sensor3"]["intervaloMedicao"];
    //Sensor 4
  tipoSensor4       = (const char*)doc["sensor4"]["tipoSensor"];
  itemZabbix4       = (const char*)doc["sensor4"]["itemZabbix"];
  pinSensor4        = (uint8_t)doc["sensor4"]["pinSensor"];
  medeTemperatura4  = (boolean)doc["sensor4"]["medeTemperatura"];
  medeHumidade4     = (boolean)doc["sensor4"]["medeHumidade"];
  intervaloMedicao4 = (long)doc["sensor4"]["intervaloMedicao"];
    //Sensor 5
  tipoSensor5       = (const char*)doc["sensor5"]["tipoSensor"];
  itemZabbix5       = (const char*)doc["sensor5"]["itemZabbix"];
  pinSensor5        = (uint8_t)doc["sensor5"]["pinSensor"];
  medeTemperatura5  = (boolean)doc["sensor5"]["medeTemperatura"];
  medeHumidade5     = (boolean)doc["sensor5"]["medeHumidade"];
  intervaloMedicao5 = (long)doc["sensor5"]["intervaloMedicao"];
    //Sensor 6
  tipoSensor6       = (const char*)doc["sensor6"]["tipoSensor"];
  itemZabbix6       = (const char*)doc["sensor6"]["itemZabbix"];
  pinSensor6        = (uint8_t)doc["sensor6"]["pinSensor"];
  medeTemperatura6  = (boolean)doc["sensor6"]["medeTemperatura"];
  medeHumidade6     = (boolean)doc["sensor6"]["medeHumidade"];
  intervaloMedicao6 = (long)doc["sensor6"]["intervaloMedicao"];
    //Sensor 7
  tipoSensor7       = (const char*)doc["sensor7"]["tipoSensor"];
  itemZabbix7       = (const char*)doc["sensor7"]["itemZabbix"];
  pinSensor7        = (uint8_t)doc["sensor7"]["pinSensor"];
  medeTemperatura7  = (boolean)doc["sensor7"]["medeTemperatura"];
  medeHumidade7     = (boolean)doc["sensor7"]["medeHumidade"];
  intervaloMedicao7 = (long)doc["sensor7"]["intervaloMedicao"];
    //Sensor 8
  tipoSensor8       = (const char*)doc["sensor8"]["tipoSensor"];
  itemZabbix8       = (const char*)doc["sensor8"]["itemZabbix"];
  pinSensor8        = (uint8_t)doc["sensor8"]["pinSensor"];
  medeTemperatura8  = (boolean)doc["sensor8"]["medeTemperatura"];
  medeHumidade8     = (boolean)doc["sensor8"]["medeHumidade"];
  intervaloMedicao8 = (long)doc["sensor8"]["intervaloMedicao"];
  
  zSender.Init(ipZabbix, portaZabbix, hostZabbix);
  
  ficheiroConfig.close();
  return true;
}
