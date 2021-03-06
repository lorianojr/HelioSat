/* Incluindo a biblioteca */
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

struct package {
  int Temperatura;
  float Altitude;
  float Pressao;
  float CO;
  float Alcohol;
  float CO2;
  float NH4;
  float Acetona;
};

typedef struct package Package;
Package data;


/* Rádio entre o transmissor e receptor */
RF24 radio(9,10);  /* Certifique-se que estão conectados nos mesmos pinos */
const uint64_t pipes[2] = { 
  0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };


void setup()
{
  Serial.begin(9600); /* Na velocidade 9600 no Monitor Serial */
  radio.begin(); /* Inicia o NRF2L001 */
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening(); /* Rádio começa a receber */
}

void loop(void)
{
  if ( radio.available() ) /* Se o rádio estiver disponível irá substituir o valor de data antigo pelo novo */
  {
    bool done = false;
    while (!done)
    {
    done = radio.read( &data, sizeof(data) );
    }
      
    Serial.println(" ");
    Serial.println("         Resultados do HélioSat");
    Serial.println(" ------------------------------------");
    Serial.print("|  Temperatura: "); Serial.print(data.Temperatura);Serial.println("°C");
    Serial.print("|  Altitude: "); Serial.print(data.Altitude);Serial.println("m");
    Serial.print("|  Pressão Atmosférica: "); Serial.print(data.Pressao);Serial.println(" Pa");
    Serial.print("|  Monóxido de carbono: "); Serial.println(data.CO);
    Serial.print("|  Álcool: "); Serial.println(data.Alcohol);
    Serial.print("|  Dióxido de carbono: "); Serial.println(data.CO2 + 400);
    Serial.print("|  Amónio: "); Serial.println(data.NH4);
    Serial.print("|  Acetona: "); Serial.println(data.Acetona);
    Serial.println(" ------------------------------------");
    Serial.println(" ");
    delay(2000);
  }
}
