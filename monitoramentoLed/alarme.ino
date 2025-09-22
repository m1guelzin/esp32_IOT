void handleAlarme(AdafruitIO_Data *data){
  String valor = data -> toString();

  Serial.print(F("Valor recebido do feed: "));
  Serial.println(valor);

  if (valor == "true"){
    alarmeAtivo = true;
    Serial.println("Alarme ARMADO pelo dash / app!");

    // Amarelo aceso, verde apagado
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  }
  else{
    alarmeAtivo = false;
    Serial.println("Alarme DESARMADO pelo dash / app!");

    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }
}

void ativarAlerta(){
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
}

void desligarAlerta(){
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}
