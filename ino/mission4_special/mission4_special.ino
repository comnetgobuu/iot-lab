// เกม: กดให้ไว ก่อนภัยมา
const int buttonPin = 4;
const int ledPin = 5;
 
int minWait = 2000;   // เวลารอต่ำสุดก่อนไฟติด (ms)
int maxWait = 5000;   // เวลารอสูงสุดก่อนไฟติด (ms)
int scoreFast = 300;  // เกณฑ์ "เร็วมาก" (ms)
int scoreGood = 600;  // เกณฑ์ "เร็วดี" (ms)
 
unsigned long startTime;
 
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("=== เกม: กดให้ไว ก่อนภัยมา ===");
  Serial.println("กดปุ่มเพื่อเริ่ม...");
}
 
void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    delay(200);
    Serial.println("[กดปุ่มแล้ว] เตรียมตัว...");
    int waitTime = random(minWait, maxWait);
    delay(waitTime);
 
    digitalWrite(ledPin, HIGH);
    Serial.println("ไฟติดแล้ว! กดเดี๋ยวนี้!");
    startTime = millis();
 
    while (digitalRead(buttonPin) == LOW) {
      // วนรอจนกว่าจะกด
    }
 
    unsigned long reactionTime = millis() - startTime;
    digitalWrite(ledPin, LOW);
 
    Serial.print("ผลลัพธ์: เวลาปฏิกิริยา = ");
    Serial.print(reactionTime);
    Serial.println(" ms");
 
    if (reactionTime < scoreFast) {
      Serial.println("ระดับ: เร็วมาก!");
      for (int i = 0; i < 3; i++) {
        digitalWrite(ledPin, HIGH); delay(100);
        digitalWrite(ledPin, LOW);  delay(100);
      }
    } else if (reactionTime < scoreGood) {
      Serial.println("ระดับ: เร็วดี");
      for (int i = 0; i < 2; i++) {
        digitalWrite(ledPin, HIGH); delay(300);
        digitalWrite(ledPin, LOW);  delay(300);
      }
    } else {
      Serial.println("ระดับ: ลองใหม่นะ");
      digitalWrite(ledPin, HIGH); delay(1000);
      digitalWrite(ledPin, LOW);
    }
 
    delay(200);
    Serial.println();
    Serial.println("กดปุ่มเพื่อเล่นรอบใหม่...");
  }
}
