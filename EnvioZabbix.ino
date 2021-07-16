void enviaDadosSensor(char* nomeItem, float valorSensor) {
  zSender.ClearItem();
  zSender.AddItem(nomeItem, valorSensor);
  zSender.Send() == EXIT_SUCCESS ? Serial.println("Item inviado") : logErro("Erro no envio ao Zabbix!");
}

bool configuraZabbix() {
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

  String ipString = (const char*)doc["zabbix"]["ipZabbix"];
  ipZabbix.fromString(ipString.c_str());
  portaZabbix = (int)doc["zabbix"]["portaZabbix"];
  hostZabbix = (const char*)doc["zabbix"]["hostZabbix"];

  ficheiroConfig.close();
  return true;
}
