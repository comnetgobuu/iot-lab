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

// ==== ตัวแปรสำหรับสลับ LED ====
bool ledState = false;
int lastButtonState = LOW;

void handleRoot() {
  int buttonState = digitalRead(buttonPin);
  int potValue = analogRead(potPin);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<title>ภารกิจเฝ้าระวังภัยพิบัติ</title></head><body>";
  html += "<h1>ภารกิจเฝ้าระวังภัยพิบัติ</h1>";
  html += "<p>ปุ่มกดจริง: " + String(buttonState == HIGH ? "กดอยู่" : "ไม่ได้กด") + "</p>";
  html += "<p>สถานะ LED: " + String(ledState ? "ติด" : "ดับ") + "</p>";

  // ==== ปุ่มบนเว็บ สั่งเปิด/ปิด LED ====
  html += "<p><a href='/toggle'><button style='font-size:24px;padding:10px 20px;'>";
  html += ledState ? "ปิด LED" : "เปิด LED";
  html += "</button></a></p>";

  html += "<p>โพเทนชิโอมิเตอร์: " + String(potValue) + "</p>";
  html += "<p>อุณหภูมิ: " + String(temp) + " C</p>";
  html += "<p>ความชื้น: " + String(hum) + " %</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// ==== ฟังก์ชันรับคำสั่งจากปุ่มบนเว็บ ====
void handleToggle() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  server.sendHeader("Location", "/");   // สั่งเบราว์เซอร์เด้งกลับหน้าแรกทันที
  server.send(303);
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
  server.on("/toggle", handleToggle);   // เส้นทางใหม่สำหรับปุ่มเว็บ
  server.begin();
}

void loop() {
  server.handleClient();

  // ==== ปุ่มกดจริงบนวงจร ก็ยังสลับ LED ได้เหมือนเดิม ====
  int currentButtonState = digitalRead(buttonPin);
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    delay(200);
  }
  lastButtonState = currentButtonState;
}