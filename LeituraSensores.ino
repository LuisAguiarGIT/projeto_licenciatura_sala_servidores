void enviaDados(String tipoDeSensor, String itemZabbix, boolean medeTemperatura, boolean medeHumidade, uint8_t pinSensor) {
  String stringCopy  = itemZabbix;
  String appendTemp = "temp";
  String appendHum  = "humi";

  if (tipoDeSensor = "DHT11") {
    if (medeTemperatura && medeHumidade) {
      DHT.read11(pinSensor1);
      float temperatura = DHT.temperature;
      float humidade = DHT.humidity;

      String itemZabbixTemp = stringCopy + appendTemp;
      enviaDadosSensor(itemZabbixTemp, temperatura);

      String itemZabbixHumi = stringCopy + appendHum;
      enviaDadosSensor(itemZabbixHumi, humidade);
    }
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
