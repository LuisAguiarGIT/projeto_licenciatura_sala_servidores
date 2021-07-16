void leFicheiro(const char* path) {
  Serial.println("\n--------------------------");
  Serial.printf("Ficheiro a ler: %s\r\n", path);
  File file = LittleFS.open(path, "r");

  if (!file) {
    Serial.println("Erro na abertura do ficheiro");
    return;
  } else {
    Serial.println("Ficheiro aberto com sucesso!");
  }

  Serial.println("\n--------------------------");
  Serial.println("Dados contidos no ficheiro:");
  while(file.available()) {
    Serial.write(file.read());
  }
  Serial.println("\n--------------------------");
  file.close();
}

void logErro(char* mensagemDeErro) {
  const char* path = "/LoggerErros.txt";
  File ficheiroLoggerErros = LittleFS.open(path, "a");

  if (ficheiroLoggerErros == NULL) {
    printf("Erro na localização do ficheiro %s", path);
    return;
  }

  ficheiroLoggerErros.println(mensagemDeErro);
  ficheiroLoggerErros.close();
}
