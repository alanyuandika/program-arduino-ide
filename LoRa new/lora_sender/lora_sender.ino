#include <SPI.h>
#include <LoRa.h>

int counter = 0;
float distance = 100;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
    // Kirim data melalui LoRa
    sendMessage();
}

void sendMessage() {
  Serial.print("Sending packet: ");
  Serial.println(distance);

  LoRa.beginPacket();
  LoRa.print(distance);
  LoRa.endPacket();

  delay(1000);
}
