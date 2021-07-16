bool configuraWifi() {
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

  ssid = doc["wifi"]["ssid"];
  passwordRede = doc["wifi"]["passwordRede"];

  ficheiroConfig.close();
  return true;
}

//boolean conectaWifi() {
//  int conta = 0;
//  Serial.print("Aguardando conexão Wifi");
//  while (conta < 300) {
//    if (WiFi.status() == WL_CONNECTED) {
//      Serial.println();
//      Serial.println("Conectado!");
//      Serial.print("Endereço atribuido: ");
//      Serial.println(WiFi.localIP());
//      Serial.println();
//      return true;
//    }
//    delay(INTERVALO/2);
//    Serial.print(".");
//    conta++;
//  }
//  Serial.println("Timeout!");
//  logErro("Erro na conexão Wifi");
//  return false;
//}
