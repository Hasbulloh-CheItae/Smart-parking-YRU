/*
โค้ดนี้เป็นโปรแกรมสำหรับ ควบคุม MH-FMD Piezo Buzzer Module โดยใช้ Arduino IDE
ซึ่งทำงานโดยการเปิดเสียงที่ความถี่ 2000 Hz เป็นเวลา 500 มิลลิวินาที และรอ 5 วินาทีก่อนที่จะทำซ้ำอีกครั้ง
VCC (3.3V)
*/
const int BUZZER_PIN = 23;  // กำหนดให้ขา 23 เป็นตัวแปรชื่อ BUZZER_PIN

void setup() {

  pinMode(BUZZER_PIN, OUTPUT);  // กำหนดขา BUZZER_PIN เป็นขา OUTPUT (เอาท์พุต)
}


void loop() {
  tone(BUZZER_PIN, 2000, 500);  // เปิดเสียงที่ความถี่ 2000 Hz เป็นเวลา 500 มิลลิวินาที
  delay(5000);
}