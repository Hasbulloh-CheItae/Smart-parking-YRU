/*
2. ทดสอบ Serial Monitor
โค้ดนี้จะส่งข้อความไปที่ Serial Monitor

เปิด Serial Monitor (Ctrl + Shift + M) แล้วตั้ง Baud Rate เป็น 115200 เพื่อดูผลลัพธ์
*/

void setup() {
  Serial.begin(115200);  // เริ่มต้น Serial ที่ baud rate 115200
}

void loop() {
  Serial.println("ESP32 ทดสอบการส่งข้อมูลผ่าน Serial!");
  delay(1000);
}
