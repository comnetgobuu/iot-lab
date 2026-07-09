#include "DHT.h"
 
#define DHTPIN 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  Serial.begin(115200);
  dht.begin();
}
 
void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
 
  Serial.print("อุณหภูมิ: "); Serial.print(temp);
  Serial.print(" C  ความชื้น: "); Serial.print(hum);
  Serial.println(" %");
 
  delay(2000);
}
