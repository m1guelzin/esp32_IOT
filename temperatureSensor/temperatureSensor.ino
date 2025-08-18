#include <math.h>
#include "AdafruitIO_WiFi.h"

// //Configurações da rede WIFI
// #define WIFI_SSID ""
// #define WIFI_PASS ""

// //Autenticação Adafruit IO
// #define IO_USERNAME ""
// #define IO_KEY ""

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


#define pinNTC 34

//Controle de envio de dados
float temp_atual = 0;
float temp_anterior = -1;

//Variavel / ponteiro para referenciar o feed temperatura
AdafruitIO_Feed *temperatura = io.feed("temperature");



// --- Constantes do NTC ---
const float Rfixo = 10000.0;      // Resistor fixo do divisor de tensão (ohms)
const float Beta = 3950.0;        // Constante Beta do NTC (fornecida pelo fabricante)
const float R0 = 10000.0;         // Resistência nominal do NTC a 25°C (ohms)
const float T0_kelvin = 298.15;   // 25°C em Kelvin
const float Vcc = 3.3;            // Tensão de alimentação do divisor (ESP32 = 3,3V)

// --- Função para calcular temperatura com média de leituras ---
float lerTemperaturaNTC(int pino, int numLeituras) {
    long somaLeituras = 0;

    // Faz várias leituras para reduzir ruído
    for (int i = 0; i < numLeituras; i++) {
        somaLeituras += analogRead(pino);
        delay(5); // pequeno atraso para estabilizar
    }

    // Calcula média das leituras
    float leituraMedia = somaLeituras / (float)numLeituras;

    // Converte para tensão real (ESP32: ADC de 12 bits = 0 a 4095)
    float Vout = leituraMedia * (Vcc / 4095.0);

    // Calcula resistência do NTC pelo divisor de tensão
    float Rntc = Rfixo * ((Vcc / Vout) - 1.0);

    // Aplica equação Beta para calcular temperatura em Kelvin
    float tempK = 1.0 / ((1.0 / T0_kelvin) + (1.0 / Beta) * log(Rntc / R0));

    // Retorna temperatura em Celsius
    return tempK - 273.15;
}

void setup() {
  pinMode(pinNTC,INPUT);

  Serial.begin(115200);

  while(!Serial);
  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  delay(1000);
}

void loop() {
  
  //Manter a conexão com o adafruit IO ativa
  io.run();

  temp_atual = lerTemperaturaNTC(pinNTC, 10);

  if(temp_atual == temp_anterior){
    return;
  }

  Serial.print(F("Temperatura enviada: "));
  Serial.print(temp_atual, 2);
  Serial.println(F("°C"));

  // Serial.print("Temperatura Analogica: ");
  // Serial.println(analogRead(pinNTC));

  //Envio / registro no feed "temperature"
  temperatura -> save(temp_atual);

  temp_anterior = temp_atual;

  delay(3000);

}