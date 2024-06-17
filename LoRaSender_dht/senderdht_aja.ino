#include <SPI.h>
#include <LoRa.h>
#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT22

//DHT dht(DHTPIN, DHTTYPE);

//int counter = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("DHT22 example!"));
  //dht.begin();

  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() 
{
  /*float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }*/
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("Humidity: ");
  //LoRa.print(F("Humidity: "));
  //LoRa.print(humidity);
  //LoRa.print(F("% Temperature: "));
  //LoRa.print(temperature);
  //LoRa.print(F("C "));
  LoRa.endPacket();
  
  //counter++;

  delay(1000);
}
