#define LED_PIN 13

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // เปิด LED
  delay(1000); // รอ 1 วินาที
  digitalWrite(LED_PIN, LOW); // ปิด LED
  delay(1000); // รอ 1 วินาที
}
