void enviaDados(String tipoDeSensor, String itemZabbix, boolean medeTemperatura, boolean medeHumidade, uint8_t pinSensor) {
  String stringCopy  = itemZabbix;
  String appendTemp = "temp";
  String appendHum  = "humi";
  String itemZabbixTemp = stringCopy + appendTemp;
  String itemZabbixHumi = stringCopy + appendHum;

  if (tipoDeSensor == "DHT11") {
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
    }
  } else if (tipoDeSensor == "DHT22") {
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
