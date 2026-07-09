// มิชชัน 1: ปุ่มกดคุม LED
const int buttonPin = 4;   // ขาปุ่มกด
const int ledPin = 5;      // ขา LED
 
int buttonState = 0;
 
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}
 
void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
 
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
