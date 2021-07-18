void enviaDados(String tipoDeSensor, String itemZabbix, boolean medeTemperatura, boolean medeHumidade, uint8_t pinSensor) {
  String stringCopy  = itemZabbix;
  String appendTemp = "temp";
  String appendHum  = "humi";
  String itemZabbixTemp = stringCopy + appendTemp;
  String itemZabbixHumi = stringCopy + appendHum;

  if (tipoDeSensor == "DHT11") {
    leituraDeDados(tipoDeSensor, pinSensor);
    
    if (medeTemperatura && medeHumidade) {
      
      enviaDadosSensorDHT(itemZabbixTemp, temperatura);
      enviaDadosSensorDHT(itemZabbixHumi, humidade);
      
    } else if (medeTemperatura && !medeHumidade) {
      
      enviaDadosSensorDHT(itemZabbixTemp, temperatura);
      
    } else if (medeHumidade && !medeTemperatura) {
      
      enviaDadosSensorDHT(itemZabbixHumi, humidade);
      
    } else {
      String mensagemErro = mensagemErroSensor + pinSensor;
      logErro("Sensor DHT11 mal configurado");
    }
  } else if (tipoDeSensor == "DHT22") {
    leituraDeDados(tipoDeSensor, pinSensor);
    
    if (medeTemperatura && medeHumidade) {

      enviaDadosSensorDHT(itemZabbixTemp, temperatura);
      enviaDadosSensorDHT(itemZabbixHumi, humidade);
      
    } else if (medeTemperatura && !medeHumidade) {

      enviaDadosSensorDHT(itemZabbixTemp, temperatura);
      
    } else if (medeHumidade && !medeTemperatura) {

      enviaDadosSensorDHT(itemZabbixHumi, humidade);
      
    } else {
      String mensagemErro = mensagemErroSensor + pinSensor;
      logErro("Sensor DHT11 mal configurado");
    }
  } else if (tipoDeSensor == "Reed") {
    pinMode(pinSensor, INPUT);

    int analogVal = analogRead(pinSensor);

    enviaDadosSensorReed(itemZabbix, analogVal);
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
  } else if (tipoDeSensor == "DHT22") {
    DHT dht = DHT(pinSensor,DHTTYPE22);
    dht.begin();

    temperatura = dht.readTemperature();
    humidade    = dht.readHumidity();  
  }
}
