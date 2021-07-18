boolean conectaWifi() {
  int conta = 0;
  Serial.print("Aguardando conexão Wifi");
  while (conta < 300) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println();
      Serial.println("Conectado!");
      Serial.print("Endereço atribuido: ");
      Serial.println(WiFi.localIP());
      Serial.println();
      intervaloMedicao = 60000;
      return true;
    }
    delay(INTERVALO/2);
    Serial.print(".");
    conta++;
  }
  Serial.println("Timeout!");
  intervaloMedicao = 300000;
  logErro("Erro na conexão Wifi - Timeout!");
  return false;
}
