/*
===================== ไลบรารี่ =====================
LiquidCrystal I2C by Frank de Brabander
ESP32Servo by Kevin Harrington,John K. Bennett
==================================================


*/

#include <LiquidCrystal_I2C.h>  //->ไลบรารีสำหรับควบคุมจอ LCD ผ่าน I2C (รองรับการใช้กับ ESP32)
#include <ESP32Servo.h>         //->ใช้ไลบรารีสำหรับ ESP32

#define IR1_PIN 23
#define IR2_PIN 19

#define LED_RED_PIN 13
#define LED_GREEN_PIN 14
// กำหนดที่อยู่ I2C ของจอ LCD (อาจเป็น 0x27 หรือ 0x3F)
#define I2C_ADDR 0x27   // กำหนด ที่อยู่ I2C ของจอ LCD
#define LCD_COLUMNS 16  // จำนวน คอลัมน์ (แนวนอน) ของ LCD
#define LCD_ROWS 2      // จำนวน แถว (แนวตั้ง) ของ LCD
// กำหนดค่าระยะทางขั้นต่ำในการตรวจจับวัตถุ (หน่วยเป็นเซนติเมตร)
#define Object_DETECTED 0
#define SERVO_PIN 18
#define MAX_CAR_PARKING 5

// สร้างอ็อบเจ็กต์ LCD
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);
Servo myServo;

int IR1_value;
int IR2_value;
unsigned int num_car_entered = 0, num_car_leaves = 0;
bool objectDetected = false;

void setup() {
  Serial.begin(115200);  // เริ่มต้น Serial Monitor
  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);

  // เริ่มต้น LCD
  lcd.init();       // เริ่มต้นการทำงานของ LCD
  lcd.backlight();  // เปิดแสงพื้นหลังของจอ LCD

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  // แสดงข้อความบน LCD
  lcd.setCursor(0, 0);                                             //  กำหนดตำแหน่งของข้อความ ที่จะแสดง (0 คือคอลัมน์แรก, 0 คือแถวแรก)
  lcd.print("PARKING");                                            // แสดงข้อความ "Hello, ESP32!" ที่บรรทัดแรก
  lcd.setCursor(0, 1);                                             // ย้ายไปแถวที่สอง (0 คือคอลัมน์แรก, 1 คือแถวที่สอง)
  lcd.print("NUM: " + String(MAX_CAR_PARKING - num_car_entered));  // แสดงข้อความ "LCD is working!" ที่บรรทัดสอง
  delay(1000);
  myServo.attach(SERVO_PIN);
}

void loop() {
  // IR 1
  IR1_value = digitalRead(IR1_PIN);
  Serial.print("IR1_value = ");
  Serial.println(IR1_value);
  // ----------------------------------------------
  // IR 2
  IR2_value = digitalRead(IR2_PIN);
  Serial.print("IR2_value = ");
  Serial.println(IR2_value);
  // ----------------------------------------------
  // ตรวจจับวัตถุที่ผ่านเซนเซอร์
  if (IR1_value == Object_DETECTED || IR2_value == Object_DETECTED) {

    if (!objectDetected) {
      objectDetected = true;
      // แสดงข้อความบน LCD
      if (IR1_value == Object_DETECTED && num_car_entered < MAX_CAR_PARKING) {
        // เสียงแจ้งเตือน
        num_car_entered++;
        digitalWrite(LED_GREEN_PIN, HIGH);
        delay(500);
        digitalWrite(LED_GREEN_PIN, LOW);

        lcd.noBacklight();
        lcd.setCursor(0, 0);
        lcd.print("PARKING");
        lcd.setCursor(0, 1);
        lcd.print("NUM: " + String(MAX_CAR_PARKING - num_car_entered));
        lcd.backlight();
        delay(1000);

        Serial.println("Opening gate...");
        myServo.write(90);
        delay(3000);
        myServo.write(0);
        delay(1000);
        Serial.println("Closing gate...");
      }
      if (IR1_value == Object_DETECTED && num_car_entered == MAX_CAR_PARKING) {
        digitalWrite(LED_RED_PIN, HIGH);
        lcd.noBacklight();
        lcd.setCursor(0, 0);
        lcd.print("PARKING");
        lcd.setCursor(0, 1);
        lcd.print("NUM: MAX");
        lcd.backlight();
        delay(1000);
      }

      if (IR2_value == Object_DETECTED && num_car_entered > 0) {
        // เสียงแจ้งเตือน
        num_car_entered--;
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(LED_GREEN_PIN, HIGH);
        delay(500);
        digitalWrite(LED_GREEN_PIN, LOW);

        lcd.noBacklight();
        lcd.setCursor(0, 0);
        lcd.print("PARKING");
        lcd.setCursor(0, 1);
        lcd.print("NUM: " + String(MAX_CAR_PARKING - num_car_entered) + "  ");
        lcd.backlight();
        delay(1000);

        Serial.println("Opening gate...");
        myServo.write(90);
        delay(3000);
        myServo.write(0);
        delay(1000);
        Serial.println("Closing gate...");
      }
    }
  } else {
    objectDetected = false;
  }
}
