// มิชชัน 2: อ่านค่าโพเทนชิโอมิเตอร์
const int potPin = 36;   // ขาโพเทนชิโอมิเตอร์ (Analog ADC0)
 
int potValue = 0;
 
void setup() {
  Serial.begin(115200);
  delay(1000);
}
 
void loop() {
  potValue = analogRead(potPin);
  Serial.println(potValue);
  delay(500);
}
