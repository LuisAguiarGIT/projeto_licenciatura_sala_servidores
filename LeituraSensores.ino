//void enviaDados(String tipoDeSensor, String itemZabbix, boolean medeTemperatura, boolean medeHumidade, uint8_t pinSensor) {
//  String stringCopy  = itemZabbix;
//  String appendTemp = "temp";
//  String appendHum  = "humi";
//  String itemZabbixTemp = stringCopy + appendTemp;
//  String itemZabbixHumi = stringCopy + appendHum;
//
//  if (tipoDeSensor == "DHT11") {
//    DHT dht = DHT(pinSensor,DHTTYPE11);
//    dht.begin();
//    
//    if (medeTemperatura && medeHumidade) {
//      float temperatura = dht.readTemperature();
//      float humidade = dht.readHumidity();
//
//      enviaDadosSensor(itemZabbixTemp, temperatura);
//      enviaDadosSensor(itemZabbixHumi, humidade);
//    } else if (medeTemperatura && !medeHumidade) {
//      float temperatura = dht.readTemperature();
//
//      enviaDadosSensor(itemZabbixTemp, temperatura);
//    } else if (medeHumidade && !medeTemperatura) {
//      float humidade = dht.readHumidity();
//
//      enviaDadosSensor(itemZabbixHumi, humidade);
//    } else {logErro(}
//  } else if (tipoDeSensor == "DHT22") {
//    DHT dht = DHT(pinSensor,DHTTYPE22);
//    dht.begin();
//    if (medeTemperatura && medeHumidade) {
//      float temperatura = dht.readTemperature();
//      float humidade = dht.readHumidity();
//
//      enviaDadosSensor(itemZabbixTemp, temperatura);
//      enviaDadosSensor(itemZabbixHumi, humidade);
//    } else if (medeTemperatura && !medeHumidade) {
//      float temperatura = dht.readTemperature();
//
//      enviaDadosSensor(itemZabbixTemp, temperatura);
//    } else if (medeHumidade && !medeTemperatura) {
//      float humidade = dht.readHumidity();
//
//      enviaDadosSensor(itemZabbixHumi, humidade);
//    }
//  } else if (tipoDeSensor == "Reed") {
//    pinMode(pinSensor, INPUT);
//
//    int analogVal = analogRead(pinSensor);
//
//    enviaDadosSensor(itemZabbix, analogVal);
//  } else {
//    if (tipoDeSensor == "null") {
//      return;
//    }
//    logErro("Este tipo de sensor foi mal configurado ou não é suportado");
//    return;
//  }
//}

void enviaDados(String tipoDeSensor, String itemZabbix, boolean medeTemperatura, boolean medeHumidade, uint8_t pinSensor) {
  String stringCopy  = itemZabbix;
  String appendTemp = "temp";
  String appendHum  = "humi";
  String itemZabbixTemp = stringCopy + appendTemp;
  String itemZabbixHumi = stringCopy + appendHum;

  if (tipoDeSensor == "DHT11") {
    leituraDeDados(tipoDeSensor, pinSensor);
    
    if (medeTemperatura && medeHumidade) {
      
      enviaDadosSensor(itemZabbixTemp, temperatura);
      enviaDadosSensor(itemZabbixHumi, humidade);
      
    } else if (medeTemperatura && !medeHumidade) {
      
      enviaDadosSensor(itemZabbixTemp, temperatura);
      
    } else if (medeHumidade && !medeTemperatura) {
      
      enviaDadosSensor(itemZabbixHumi, humidade);
      
    }
  } else if (tipoDeSensor == "DHT22") {
    leituraDeDados(tipoDeSensor, pinSensor);
    
    if (medeTemperatura && medeHumidade) {

      enviaDadosSensor(itemZabbixTemp, temperatura);
      enviaDadosSensor(itemZabbixHumi, humidade);
      
    } else if (medeTemperatura && !medeHumidade) {

      enviaDadosSensor(itemZabbixTemp, temperatura);
      
    } else if (medeHumidade && !medeTemperatura) {

      enviaDadosSensor(itemZabbixHumi, humidade);
      
    }
  } else if (tipoDeSensor == "Reed") {
    pinMode(pinSensor, INPUT);

    int analogVal = analogRead(pinSensor);

    enviaDadosSensor(itemZabbix, analogVal);
  } else {
    if (tipoDeSensor == "null") {
      return;
    }
    logErro("Este tipo de sensor foi mal configurado ou não é suportado");
    return;
  }
}

void leituraDeDados(String tipoDeSensor, uint8_t pinSensor){
  if (tipoDeSensor == "DHT11") {
    DHT dht = DHT(pinSensor,DHTTYPE11);
    dht.begin();
    
    temperatura = dht.readTemperature();
    humidade    = dht.readHumidity();
    Serial.println(temperatura);    
  } else if (tipoDeSensor == "DHT22") {
    DHT dht = DHT(pinSensor,DHTTYPE22);
    dht.begin();

    temperatura = dht.readTemperature();
    humidade    = dht.readHumidity();  
  }
}
