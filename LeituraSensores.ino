void enviaDados(String tipoDeSensor, String itemZabbix, boolean medeTemperatura, boolean medeHumidade, uint8_t pinSensor) {
  String stringCopy  = itemZabbix;
  String appendTemp = "temp";
  String appendHum  = "humi";
  String itemZabbixTemp = stringCopy + appendTemp;
  String itemZabbixHumi = stringCopy + appendHum;

  if (tipoDeSensor = "DHT11") {
    DHT.read11(pinSensor);
    if (medeTemperatura && medeHumidade) {
      float temperatura = DHT.temperature;
      float humidade = DHT.humidity;

      enviaDadosSensor(itemZabbixTemp, temperatura);
      enviaDadosSensor(itemZabbixHumi, humidade);
    } else if (medeTemperatura && !medeHumidade) {
      float temperatura = DHT.temperature;

      enviaDadosSensor(itemZabbixTemp, temperatura);
    } else if (medeHumidade && !medeTemperatura) {
      float humidade = DHT.humidity;

      enviaDadosSensor(itemZabbixHumi, temperatura);
    } else {
      Serial.println("Erro na configuração do sensor DHT11");
    }
  } else if (tipoDeSensor = "DHT22") {
    DHT.read22(pinSensor);
    if (medeTemperatura && medeHumidade) {
      float temperatura = DHT.temperature;
      float humidade = DHT.humidity;

      enviaDadosSensor(itemZabbixTemp, temperatura);
      enviaDadosSensor(itemZabbixHumi, humidade);
    } else if (medeTemperatura && !medeHumidade) {
      float temperatura = DHT.temperature;

      enviaDadosSensor(itemZabbixTemp, temperatura);
    } else if (medeHumidade && !medeTemperatura) {
      float humidade = DHT.humidity;

      enviaDadosSensor(itemZabbixHumi, temperatura);
    } else {
      Serial.println("Erro na configuração do sensor DHT11");
    }
  } else if (tipoDeSensor = "Reed") {
    return;
  }

}

//void verificaIntervalo(long currentMillis, long intervaloMedicao, const char* tipoDeSensor, boolean medeTemperatura, boolean medeHumidade, uint8_t pinSensor, const char* itemZabbix) {
//  if (currentMillis - previousMillis > intervaloMedicao) {
//    previousMillis = currentMillis;
//    if (isConnected) {
//      enviaDados(tipoDeSensor, medeTemperatura, medeHumidade, pinSensor, itemZabbix);
//    } else {
//      setup();
//    }
//  }
//}

//void enviaDados(const char* tipoDeSensor, boolean medeTemperatura, boolean medeHumidade, uint8_t pinSensor, const char* itemZabbix) {
//  float temperatura       = 0;
//  float humidade          = 0;
//  const char* appendTemp  = "temp";
//  const char* appendHum   = "humi";
//  //const char* itemZabbixCopy = itemZabbix;
//  char buf[30] = {0};
//  
//  if (tipoDeSensor = "DHT11") {
//    DHT dht(pinSensor, DHTTYPE11);
//    dht.begin();
//
//    if (medeTemperatura && medeHumidade) {
//      temperatura = dht.readTemperature();
//      humidade    = dht.readHumidity();
//
////      Serial.println(itemZabbixCopy);
////      strcpy(buf, itemZabbixCopy);
////      strcat(buf, appendTemp);
//      
//      enviaDadosSensor(itemZabbix, temperatura);
//
////      strcpy(buf, itemZabbixCopy);
////      strcat(buf, appendHum);
////      
////      enviaDadosSensor(buf, humidade);
//    } else if (medeTemperatura && !medeHumidade) {
//      temperatura = dht.readTemperature();
//
//      //strcpy(buf, itemZabbixCopy);
//      //strcat(buf, appendTemp);
//      
//      enviaDadosSensor(buf, temperatura);
//    } else if (medeHumidade && !medeTemperatura) {
//      humidade = dht.readHumidity();
//      
//      //strcpy(buf, itemZabbixCopy);
//      //strcat(buf, appendHum);
//      
//      enviaDadosSensor(buf, humidade);
//    } else {
//      Serial.print("Erro na configuração do sensor DHT11 no pino:");
//      Serial.println(pinSensor);
//    }
//  }
//
//  else if (tipoDeSensor = "DHT22") {
//    DHT dht(pinSensor, DHTTYPE22);
//    dht.begin();
//
//    if (medeTemperatura && medeHumidade) {
//      temperatura = dht.readTemperature();
//      humidade    = dht.readHumidity();
//      
//      //strcpy(buf, itemZabbixCopy);
//      //strcat(buf, appendTemp);
//      
//      enviaDadosSensor(buf, temperatura);
//   
//      //strcpy(buf, itemZabbixCopy);
//      //strcat(buf, appendHum);
//      
//      enviaDadosSensor(buf, humidade);
//    } else if (medeTemperatura && !medeHumidade) {
//      temperatura = dht.readTemperature();
//
//      //strcpy(buf, itemZabbixCopy);
//      //strcat(buf, appendTemp);
//      
//      //enviaDadosSensor(buf, temperatura);
//    } else if (medeHumidade && !medeTemperatura) {
//      humidade = dht.readHumidity();
//    
//     // strcpy(buf, itemZabbixCopy);
//     // strcat(buf, appendHum);
//      
//     // enviaDadosSensor(buf, humidade);
//    } else {
//      Serial.print("Erro na configuração do sensor DHT22 no pino:");
//      Serial.println(pinSensor);
//    }
//  } else {
//    Serial.println("Sensor introduzido não é possível avaliar");
//  }

//  if (tipoDeSensor == "Reed") {
//    // TODO
//  }
//}
