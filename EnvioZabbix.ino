void enviaDadosSensor(String nomeItem, float valorSensor) {
  zSender.ClearItem();
  zSender.AddItem(nomeItem, valorSensor);
  zSender.Send() == EXIT_SUCCESS ? Serial.println("Item enviado") : Serial.println("Erro no envio dos dados");
}
