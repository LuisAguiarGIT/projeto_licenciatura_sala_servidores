boolean configuraSensores() {
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
  //Serial.println(buf.get());

  StaticJsonDocument<4096> doc;

  auto error = deserializeJson(doc, buf.get());
  if (error) {
    Serial.println("Erro na analise do ficheiro json");
    return false;
  }

  tipoSensor = (const char*)doc["sensor1"]["tipoSensor"];
  itemZabbix = (const char*)doc["sensor1"]["itemZabbix"];
  pinSensor  = (uint8_t)doc["sensor1"]["pinSensor"];
  medeTemperatura = (boolean)doc["sensor1"]["medeTemperatura"];
  medeHumidade = (boolean)doc["sensor1"]["medeHumidade"];
  intervaloMedicao = (long)doc["sensor1"]["intervaloMedicao"];

//  Serial.println(tipoSensor);
//  Serial.println(itemZabbix);
//  Serial.println(pinSensor);
//  Serial.println(medeTemperatura);
//  Serial.println(medeHumidade);
//  Serial.println(intervaloMedicao);

  ficheiroConfig.close();
  return true;
}

void leValorSensor(const char* tipoDeSensor, boolean medeTemperatura, boolean medeHumidade, uint8_t pinSensor) {
  if (tipoDeSensor = "DHT11") {
    float temperatura = 0;
    float humidade    = 0;
    DHT dht(pinSensor, DHTTYPE11);
    dht.begin();

    if (medeTemperatura && medeHumidade) {
      temperatura = dht.readTemperature();
      humidade    = dht.readHumidity();

      Serial.println(temperatura);
      Serial.println(humidade);
      enviaDadosSensor(itemZabbix, temperatura);
    } else if (medeTemperatura) {
      temperatura = dht.readTemperature();

      Serial.println(temperatura);
    } else if (medeHumidade) {
      humidade = dht.readHumidity();

      Serial.println(humidade);
    } else {
      Serial.println("Erro na configuração");
    }
  }

  if (tipoDeSensor = "DHT22") {
    float temperatura = 0;
    float humidade    = 0;
    DHT dht(pinSensor, DHTTYPE22);
    dht.begin();

    if (medeTemperatura && medeHumidade) {
      temperatura = dht.readTemperature();
      humidade    = dht.readHumidity();

      Serial.println(temperatura);
      Serial.println(humidade);
    } else if (medeTemperatura) {
      temperatura = dht.readTemperature();

      Serial.println(temperatura);
    } else if (medeHumidade) {
      humidade = dht.readHumidity();

      Serial.println(humidade);
    } else {
      Serial.println("Erro na configuração");
    }
  }

//  if (tipoDeSensor == "Reed") {
//    // TODO
//  }
}
