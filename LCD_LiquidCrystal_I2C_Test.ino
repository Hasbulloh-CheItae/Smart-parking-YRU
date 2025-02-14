
#include <Wire.h> //->ไลบรารีสำหรับ I2C Communication (ใช้สื่อสารกับ LCD ผ่านโมดูล PCF8574)
#include <LiquidCrystal_I2C.h> //->ไลบรารีสำหรับควบคุมจอ LCD ผ่าน I2C (รองรับการใช้กับ ESP32)

// กำหนดที่อยู่ I2C ของจอ LCD (อาจเป็น 0x27 หรือ 0x3F)
#define I2C_ADDR 0x27 // กำหนด ที่อยู่ I2C ของจอ LCD 
#define LCD_COLUMNS 16 // จำนวน คอลัมน์ (แนวนอน) ของ LCD
#define LCD_ROWS 2 // จำนวน แถว (แนวตั้ง) ของ LCD

// สร้างอ็อบเจ็กต์ LCD
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

void setup() {
    // เริ่มต้น LCD
    lcd.init(); // เริ่มต้นการทำงานของ LCD
    lcd.backlight(); // เปิดแสงพื้นหลังของจอ LCD

    // แสดงข้อความบน LCD
    lcd.setCursor(0, 0); //  กำหนดตำแหน่งของข้อความ ที่จะแสดง (0 คือคอลัมน์แรก, 0 คือแถวแรก)
    lcd.print("Hello, ESP32!"); // แสดงข้อความ "Hello, ESP32!" ที่บรรทัดแรก
    lcd.setCursor(0, 1); // ย้ายไปแถวที่สอง (0 คือคอลัมน์แรก, 1 คือแถวที่สอง)
    lcd.print("LCD is working!"); // แสดงข้อความ "LCD is working!" ที่บรรทัดสอง
}

void loop() {
    // ทำให้ข้อความกระพริบ
    delay(1000);
    lcd.noBacklight(); // ปิดไฟพื้นหลัง LCD
    delay(1000);
    lcd.backlight(); // เปิดไฟพื้นหลัง LCD อีกครั้ง
}
