#include <SPI.h>
#include <LoRa.h>
#include "DHT.h"

#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const int trigpin = 4;
const int echo = 3;

long duration;
int distance;

int counter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22 example!"));
  dht.begin();
  
  pinMode(trigpin, OUTPUT);
  pinMode(echo, INPUT);

  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
digitalWrite(trigpin, LOW);
  delay(2);

  digitalWrite(trigpin, HIGH);
  delay(100);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration*0.0343/2;

  Serial.print("Sending packet: ");
  Serial.println(counter);

  String data = "Jarak air: " + String(distance) + " cm" + ", Kelembaban: " + String(humidity) + "%, Suhu: " + String(temperature) + " C";
  // send packet
  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();
  
  counter++;

  delay(3000);
}
