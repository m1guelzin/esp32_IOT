// #include "WiFi.h"
#include "AdafruitIO_WiFi.h"
#include "NewPing.h"

// // Configurações da sua conta Adafruit IO
// #define IO_USERNAME  ""
// #define IO_KEY       ""

// // Configurações de rede Wi-Fi
// #define WIFI_SSID    ""
// #define WIFI_PASS    ""

// // Cria objeto de conexão
// AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// // Cria referência ao feed
// AdafruitIO_Feed *botaoLED = io.feed("botaoled");

// Define o pino do LED
#define LED_PIN 13  // geralmente o pino 2 da ESP32 tem LED onboard
#define BUZZER_PIN 27
#define BOTAO_FISICO 26
#define TRIG_PIN 12
#define ECHO_PIN 14

// Configuração do ultrassonico
#define MAX_DISTANCE 100
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  // Inicializa comunicação serial
  Serial.begin(115200);

  // Configura o pino do LED e pino BUZZER como saída
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BOTAO_FISICO, INPUT);
  

  while(!Serial)
  ;

  delay(1000);

  // // Conecta ao Adafruit IO
  // Serial.print("Conectando ao Adafruit IO");
  // io.connect();

  // // Registra função callback quando o feed receber dados
  // botaoLED->onMessage(handleBotaoLed);

  // // Aguarda conexão
  // while(io.status() < AIO_CONNECTED) {
  //   Serial.print(".");
  //   delay(1000);
  // }

  // Serial.println("Conectado!");
}

void loop() {
  Serial.print(F("Distancia Lida: "));
  Serial.println(sonar.ping_cm());
  delay(500);







//   // Mantém conexão ativa
//   io.run();
// }

// // Função chamada sempre que houver alteração no feed
// void handleBotaoLed(AdafruitIO_Data *data) {
//   String valor = data->toString();
//   Serial.print("Recebido do feed: ");
//   Serial.println(valor);

//   if (valor == "true") {
//     digitalWrite(LED_PIN, HIGH);
//     Serial.println("LED LIGADO");
//   } else {
//     digitalWrite(LED_PIN, LOW);
//     Serial.println("LED DESLIGADO");
//   }
}
