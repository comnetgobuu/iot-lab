// เกมจบ: หมุนให้ตรงค่า
const int potPin = 36;
 
int targetValue = 2048;
int tolerance = 50;
int roundTime = 10000;
 
unsigned long startTime;
bool roundActive = false;
int bestDiff = 9999;
 
void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  Serial.println("=== เกม: หมุนให้ตรงค่า ===");
  printNewTarget();
}
 
void loop() {
  if (!roundActive) {
    roundActive = true;
    startTime = millis();
    bestDiff = 9999;
  }
 
  int potValue = analogRead(potPin);
  int diff = abs(potValue - targetValue);
  if (diff < bestDiff) bestDiff = diff;
 
  Serial.print("ค่าปัจจุบัน: "); Serial.print(potValue);
  if (diff <= tolerance) {
    Serial.println("  --> ตรงเป้า!");
  } else if (diff <= tolerance * 3) {
    Serial.println("  --> ใกล้แล้ว!");
  } else {
    Serial.println("  --> ยังไกลอยู่");
  }
 
  if (millis() - startTime >= roundTime) {
    Serial.println("=== หมดเวลา! ===");
    Serial.print("ระยะห่างที่ใกล้ที่สุด: "); Serial.println(bestDiff);
    delay(2000);
    printNewTarget();
    roundActive = false;
  }
  delay(200);
}
 
void printNewTarget() {
  targetValue = random(500, 3595);
  Serial.print("เป้าหมายใหม่: "); Serial.println(targetValue);
}
