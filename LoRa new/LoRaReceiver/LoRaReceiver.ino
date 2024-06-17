#include <SPI.h>
#include <LoRa.h>

#define SCK 5     // GPIO5  -- SX1278's SCK
#define MISO 19   // GPIO19 -- SX1278's MISO
#define MOSI 27   // GPIO27 -- SX1278's MOSI
#define SS 18     // GPIO18 -- SX1278's CS
#define RST 14    // GPIO14 -- SX1278's RESET
#define DI0 26    // GPIO26 -- SX1278's IRQ(Interrupt Request)

void setup() {
  Serial.begin(9600);
  //while (!Serial);

  Serial.println("LoRa Receiver");
  LoRa.setPins(SS, RST, DI0);
    if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
