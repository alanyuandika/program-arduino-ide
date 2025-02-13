#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define DHTTYPE DHT22
#define DHTPIN 13

DHT dht(DHTPIN, DHTTYPE);

int counter = 0;

float humidity;
float temp;    
 
char ssid[] = "Galaxy M32FE2F";
char pass[] = "laper2kali"; // Jika tidak menggunakan password kosongkan ""

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  dht.begin();
  
  while (WiFi.status() !=WL_CONNECTED){
    delay(1000);
    Serial.println("menghubungkan...");
  }

  Serial.print("IP Node ini adalah:");
  Serial.println(WiFi.localIP());
}

void loop()
{
  gettemperature();
  postHttp();
}

void gettemperature() {
  
    humidity = dht.readHumidity();        
    temp = dht.readTemperature(); 

    if (isnan(humidity) || isnan(temp)) {
      Serial.println("Sensor Tidak Terbaca");
      return;
    }
}

void postHttp(){
  String url = "http://192.168.67.105/api/environment";
  WiFiClient client;
  HTTPClient http;
  String response;
  
  StaticJsonDocument<200> buff;
  String Json;
  buff["id_node"] = 2;
  buff["id_message"] = counter;
  buff["suhu"] = round(temp * 10) / 10.0;
  buff["kelembaban"] = round(humidity * 10) / 10.0;

  serializeJson(buff, Json);
  Serial.println(Json);

  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.POST(Json);
  response = http.getString();
  Serial.println(response);
  delay(600000);
  counter++;
  if (counter > 255 ) {
    counter = 0;
  }
}
                                                                                                                                                                                 