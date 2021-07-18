void enviaDadosSensorDHT(String nomeItem, float valorSensor) {
  zSender.ClearItem();
  zSender.AddItem(nomeItem, valorSensor);
  if (zSender.Send() == EXIT_SUCCESS) {
    Serial.println("Item enviado");
  } else {
    logErro("Falta de resposta da plataforma Zabbix");
  }
}

void enviaDadosSensorReed(String nomeItem, int valorSensor) {
  zSender.ClearItem();
  zSender.AddItem(nomeItem, valorSensor);
  if (zSender.Send() == EXIT_SUCCESS) {
    Serial.println("Item enviado");
  } else {
    logErro("Falta de resposta da plataforma Zabbix");
  }
}
