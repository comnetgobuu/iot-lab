#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"
 
const int buttonPin = 4;
const int ledPin = 5;
const int potPin = 36;
#define DHTPIN 16
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
const char* ssid = "ทีมกู้ภัย1";   // ตั้งชื่อทีม (ห้ามซ้ำกัน)
const char* password = "12345678";
 
WebServer server(80);
 
void handleRoot() {
  int buttonState = digitalRead(buttonPin);
  int potValue = analogRead(potPin);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
 
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='2'>";
  html += "<title>ภารกิจเฝ้าระวังภัยพิบัติ</title></head><body>";
  html += "<h1>ภารกิจเฝ้าระวังภัยพิบัติ</h1>";
  html += "<p>ปุ่มกด: " + String(buttonState == HIGH ? "กดอยู่" : "ไม่ได้กด") + "</p>";
  html += "<p>โพเทนชิโอมิเตอร์: " + String(potValue) + "</p>";
  html += "<p>อุณหภูมิ: " + String(temp) + " C</p>";
  html += "<p>ความชื้น: " + String(hum) + " %</p>";
  html += "</body></html>";
 
  server.send(200, "text/html", html);
}
 
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  dht.begin();
 
  WiFi.softAP(ssid, password);
  Serial.print("เข้าเว็บที่: http://");
  Serial.println(WiFi.softAPIP());
 
  server.on("/", handleRoot);
  server.begin();
}
 
void loop() {
  server.handleClient();
}
