#include <math.h>
#include "AdafruitIO_WiFi.h"

// // //Configurações da rede WIFI
// #define WIFI_SSID ""
// #define WIFI_PASS ""

// // //Autenticação Adafruit IO
// #define IO_USERNAME ""
// #define IO_KEY ""

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


#define pinNTC 34
#define pinLed 14

//Controle de envio de dados
float temp_atual = 0;
float temp_anterior = -1;

//Variavel / ponteiro para referenciar o feed temperatura
AdafruitIO_Feed *temperatura = io.feed("temperature");

// --- Constantes do NTC ---
const float Rfixo = 10000.0;     // Resistor fixo do divisor de tensão (ohms)
const float Beta = 3950.0;       // Constante Beta do NTC (fornecida pelo fabricante)
const float R0 = 10000.0;        // Resistência nominal do NTC a 25°C (ohms)
const float T0_kelvin = 298.15;  // 25°C em Kelvin
const float Vcc = 3.3;           // Tensão de alimentação do divisor (ESP32 = 3,3V)

void setup() {
  Serial.begin(115200);

  pinMode(pinNTC, INPUT);
  pinMode(pinLed, OUTPUT);

  while (!Serial)
    ;
  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  delay(1000);

  // // configuração do callback, quando o feed receber(atualiza) um valor
  temperatura -> onMessage(handleTemperatura);
  // // registra a função de callback
  // // ela será chamada sempre que o feed receber um novo dado
}

void loop() {

  //Manter a conexão com o adafruit IO ativa
  io.run();

  // publicacao(); //chamada da funçção publish

  //Envio / registro no feed "temperature"

  delay(3000);
}