/////////////////////////////////////////////////////////////////////////////////////////
// Smart Car Parking @Yala Rajahat University                                          //
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// ESP32 TB NODE WITHOUT SDK
// -------------------------------------------------------------------------------------
// Developer: PGAS TEAM
//            406559002@yru.ac.th
// Dedicated to Yala Rajabhat University Demonstration School.
// -------------------------------------------------------------------------------------
// Libraries
// - LiquidCrystal I2C | 1.1.2 | by Frank de Brabander
// - ESP32Servo | 3.0.6 | by Kevin Harrington,John K. Bennett
/////////////////////////////////////////////////////////////////////////////////////////

/****************************************************************************************
 * ESP-WROVER-32
 * Tools->Board:"ESP32-WROOM-DA Module"
 * Preferences->Additional boards manager URLs:"https://dl.espressif.com/dl/package_esp32_index.json"
 * Boards manager:"esp32 | 3.1.1 | by Espressif Systems"
 ****************************************************************************************
 * ใช้เป็น Input Only
 * -> VP/36                 = ADC1_CH0 (Analog Input)
 * -> VN/39                 = ADC1_CH3 (Analog Input)
 * -> D34/34                = ADC1_CH6 (Analog Input)
 * -> D35/35                = ADC1_CH7 (Analog Input)
 * ใช้เป็น Digital/Analog ได้
 * -> D32/32                = GPIO, ADC1_CH4, Touch8
 * -> D33/33                = GPIO, ADC1_CH5, Touch9
 * -> D25/25                = GPIO, DAC1, ADC2_CH8
 * -> D26/26                = GPIO, DAC2, ADC2_CH9
 * -> D27/27                = GPIO, ADC2_CH7, Touch7
 * -> D14/14                = GPIO, ADC2_CH6, Touch6, SPI SCK
 * -> D12/12                = GPIO, ADC2_CH5, Touch5, SPI MISO (🚨 ห้ามดึง HIGH ตอนบูต)
 * -> D13/13                = GPIO, ADC2_CH4, Touch4, SPI MOSI
 * -> D4/4                  = GPIO, ADC2_CH0, Touch0
 * -> D15/15                = GPIO, ADC2_CH3, Touch3           (🚨 ห้ามดึง HIGH ตอนบูต)
 * ใช้เป็น Digital ได้
 * -> D23/23                = GPIO, SPI MOSI
 * -> D22/22                = GPIO, I2C SCL
 * -> D21/21                = GPIO, I2C SDA
 * -> D19/19                = GPIO, SPI MISO
 * -> D18/18                = GPIO, SPI SCK
 * -> D5/5	                = GPIO, SPI CS
 * GND                      = Ground
 * 3V3                      = Power 3.3V จ่ายไฟให้โหลด
 * VIN                      = Power Input (5V) ใช้จ่ายไฟเข้า ESP32 หรือ จ่ายไฟให้โหลด
 * ไม่ควรใช้
 * -> D0/0                  = GPIO, ADC2_CH1, Touch1           (🚨 มีผลต่อ Boot Mode)
 * -> D2/2                  = GPIO, ADC2_CH2, Touch2           (🚨 ต้องระวัง มี LED บนบอร์ด)
 * -> RX0/3                 = UART0 RX                         (🚨 ใช้สำหรับ Debug Serial)
 * -> TX0/1                 = UART0 TX                         (🚨 ใช้สำหรับ Debug Serial)
 ****************************************************************************************/

//=======================================================================================
// Ultrasonic sensor HY-SRF05 ตัวที่ 1
//=======================================================================================
// VCC   = +5V DC
// Trig  = ส่งคลื่นเสียงอัลตราโซนิกออกไป
// Echo  = รับคลื่นเสียงที่สะท้อนกลับมา
// GND   = ขั้วลบไฟ(-)
//=======================================================================================
// Transmitter (Trig Pin) = 23
//=======================================================================================
// Receiver (Echo Pin)    = 19
//=======================================================================================

//=======================================================================================
// Ultrasonic sensor HY-SRF05 ตัวที่ 2
//=======================================================================================
// VCC   = +5V DC
// Trig  = ส่งคลื่นเสียงอัลตราโซนิกออกไป
// Echo  = รับคลื่นเสียงที่สะท้อนกลับมา
// GND   = ขั้วลบไฟ(-)
//=======================================================================================
// Transmitter (Trig Pin) = 32
//=======================================================================================
// Receiver (Echo Pin)    = 33
//=======================================================================================

//=======================================================================================
// Servo SG90
//=======================================================================================
// VCC(สายสีแดง)        = +4.8V..+6V DC
// Signal(สายสีเหลือง)   = สัญญาณ
// GND(สายสีน้ำตาล)      = ขั้วลบไฟ(-)
//=======================================================================================
// Data(สายสีเหลือง) = 4
//=======================================================================================

//=======================================================================================
// LCD (Blue Screen) 16x2 พร้อม I2C Interface
//=======================================================================================
// VCC            = +5V DC
// SDA            = Serial Data Line
// SCL            = Serial Clock Line
// GND            = ขั้วลบไฟ(-)
// I2C Address    = 0X27
//=======================================================================================
// SDA = 21
//=======================================================================================
// SCL = 22
//=======================================================================================


/////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
/////////////////////////////////////////////////////////////////////////////////////////
#include <LiquidCrystal_I2C.h>  //->ไลบรารีสำหรับควบคุมจอ LCD ผ่าน I2C (รองรับการใช้กับ ESP32)
#include <ESP32Servo.h>         //->ใช้ไลบรารีสำหรับ servo (รองรับการใช้กับ ESP32)
/////////////////////////////////////////////////////////////////////////////////////////
// DEFINES
/////////////////////////////////////////////////////////////////////////////////////////

//=======================================================================================
// Initialize hardware setup : Ultrasonic sensor HY-SRF05
//=======================================================================================
#define TrigPin_Un1 23
#define EchoPin_Un1 19
#define TrigPin_Un2 32
#define EchoPin_Un2 33
//=======================================================================================
// End of hardware setup : Ultrasonic sensor HY-SRF05
//=======================================================================================

//=======================================================================================
// Initialize hardware setup : LED
//=======================================================================================
#define LED_RED_PIN 13
#define LED_GREEN_PIN 14
//=======================================================================================
// End of hardware setup : LED
//=======================================================================================

//=======================================================================================
// Initialize hardware setup : LCD
//=======================================================================================
#define I2C_ADDR 0x27   // กำหนด ที่อยู่ I2C ของจอ LCD
#define LCD_COLUMNS 16  // จำนวน คอลัมน์ (แนวนอน) ของ LCD
#define LCD_ROWS 2      // จำนวน แถว (แนวตั้ง) ของ LCD
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);
//=======================================================================================
// End of hardware setup : LCD
//=======================================================================================

//=======================================================================================
// Initialize hardware setup : SERVO
//=======================================================================================
#define SERVO_IN_PIN 4
#define SERVO_OUT_PIN 27
Servo myServo_In;  // สร้างอ็อบเจ็กต์ servo
Servo myServo_Out;  // สร้างอ็อบเจ็กต์ servo
//=======================================================================================
// End of hardware setup : SERVO
//=======================================================================================

/////////////////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
/////////////////////////////////////////////////////////////////////////////////////////
// Ultrasonic sensor
int duration_Un1;  // ระยะเวลาคลื่นเสียงอัลตราโซนิก
int duration_Un2;
float distance_Un1;  // ระยะทาง
float distance_Un2;
// จำนวนที่จอดรถที่ว่าง
unsigned int number_car = 0;
// สถานะเพื่อตรวจสอบว่าเป็นรถคันเดิมไหม
bool objectDetected = false;
// กำหนดค่าระยะทางขั้นต่ำในการตรวจจับวัตถุ (หน่วยเป็นเซนติเมตร)
const int OBJECT_THRESHOLD = 20;
// จำนวนรถที่รองรับได้
const int MAX_CAR_PARKING = 5;

/////////////////////////////////////////////////////////////////////////////////////////
// SETUP ตั้งค่าเริ่มให้อุปกรณ์ต่างๆ
/////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // เริ่มต้น Serial Monitor ที่ความเร็ว 115200
  Serial.begin(115200);
  pinMode(TrigPin_Un1, OUTPUT);  // ส่งสัญญาณ
  pinMode(EchoPin_Un1, INPUT);   // รับสัญญาณ
  pinMode(TrigPin_Un2, OUTPUT);
  pinMode(EchoPin_Un2, INPUT);

  // เริ่มต้น LCD
  lcd.init();       // เริ่มต้นการทำงานของ LCD
  lcd.backlight();  // เปิดแสงพื้นหลังของจอ LCD

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  // แสดงข้อความบน LCD
  lcd.setCursor(0, 0);                                          //  กำหนดตำแหน่งของข้อความ ที่จะแสดง (0 คือคอลัมน์แรก, 0 คือแถวแรก)
  lcd.print("SMART PARKING");                                   // แสดงข้อความที่บรรทัดแรก
  lcd.setCursor(0, 1);                                          // ย้ายไปแถวที่สอง (0 คือคอลัมน์แรก, 1 คือแถวที่สอง)
  lcd.print("EMPTY: " + String(MAX_CAR_PARKING - number_car));  // แสดงข้อความที่บรรทัดสอง
  delay(1000);

  myServo_In.attach(SERVO_IN_PIN);
}
/////////////////////////////////////////////////////////////////////////////////////////
// LOOP การทำงานของระบบ
/////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // UN 1
  // สั่งให้ TRIG_PIN อยู่ในสถานะ LOW เป็นเวลา 2 ไมโครวินาที
  // เพื่อให้แน่ใจว่าไม่มีสัญญาณค้างจากการใช้งานครั้งก่อน
  digitalWrite(TrigPin_Un1, LOW);
  delayMicroseconds(2);
  // สั่งให้ TRIG_PIN เป็น HIGH เป็นเวลา 10 ไมโครวินาที
  // การส่งสัญญาณ HIGH บอกให้เซนเซอร์ ปล่อยคลื่นเสียงอัลตร้าโซนิคออกมา
  digitalWrite(TrigPin_Un1, HIGH);
  delayMicroseconds(10);
  // ดึง TRIG_PIN กลับมาเป็น LOW เพื่อบอกให้เซนเซอร์หยุดส่งคลื่น
  digitalWrite(TrigPin_Un1, LOW);

  // จากนี้เซนเซอร์จะรอรับคลื่นสะท้อนกลับจากวัตถุผ่าน ECHO_PIN
  duration_Un1 = pulseIn(EchoPin_Un1, HIGH);

  // คำนวณระยะทาง (หน่วย: เซนติเมตร)
  distance_Un1 = duration_Un1 * 0.034 / 2;

  // แสดงผลบน Serial Monitor
  Serial.print("Distance_Un1: ");
  Serial.print(distance_Un1);
  Serial.println(" cm");
  delay(500);  // รอ 500ms ก่อนวัดค่าใหม่
  // ----------------------------------------------
  // UN 2
  // สั่งให้ TRIG_PIN อยู่ในสถานะ LOW เป็นเวลา 2 ไมโครวินาที
  // เพื่อให้แน่ใจว่าไม่มีสัญญาณค้างจากการใช้งานครั้งก่อน
  digitalWrite(TrigPin_Un2, LOW);
  delayMicroseconds(2);
  // สั่งให้ TRIG_PIN เป็น HIGH เป็นเวลา 10 ไมโครวินาที
  // การส่งสัญญาณ HIGH บอกให้เซนเซอร์ ปล่อยคลื่นเสียงอัลตร้าโซนิคออกมา
  digitalWrite(TrigPin_Un2, HIGH);
  delayMicroseconds(10);
  // ดึง TRIG_PIN กลับมาเป็น LOW เพื่อบอกให้เซนเซอร์หยุดส่งคลื่น
  digitalWrite(TrigPin_Un2, LOW);

  // จากนี้เซนเซอร์จะรอรับคลื่นสะท้อนกลับจากวัตถุผ่าน ECHO_PIN
  duration_Un2 = pulseIn(EchoPin_Un2, HIGH);

  // คำนวณระยะทาง (หน่วย: เซนติเมตร)
  distance_Un2 = duration_Un2 * 0.034 / 2;

  // แสดงผลบน Serial Monitor
  Serial.print("Distance_Un2: ");
  Serial.print(distance_Un2);
  Serial.println(" cm");
  delay(500);  // รอ 500ms ก่อนวัดค่าใหม่
  // ----------------------------------------------
  // ตรวจจับวัตถุที่ผ่านเซนเซอร์ในระยะที่กำหนด เช่น ถ้าวัตถุอยู่ในระยะ 20 cm เงื่อนไขจะเป็นจริง (จาก Un1 หรือ Un2)
  if ((distance_Un1 > 0 && distance_Un1 < OBJECT_THRESHOLD) || (distance_Un2 > 0 && distance_Un2 < OBJECT_THRESHOLD)) {
    // เงื่อนไขนี้มีเพื่อไม่ให้นับรถคันเดิมซำ่ (ง่ายๆเพื่อไม่ให้รถ 1 คันมีที่จอดรถมากกว่า 1)
    if (!objectDetected) {
      objectDetected = true;
      // ตรวจจับวัตถุที่ผ่านเซนเซอร์ในระยะที่กำหนด และ ในที่จอดรถ รถยังไม่เต็ม เงื่อนไขจะเป็นจริง
      if ((distance_Un1 > 0 && distance_Un1 < OBJECT_THRESHOLD) && number_car < MAX_CAR_PARKING) {
        // จำนวนรถ +1
        number_car++;
        // เปิดไฟ LED GREEN 1 วิ
        digitalWrite(LED_GREEN_PIN, HIGH);
        delay(1000);
        digitalWrite(LED_GREEN_PIN, LOW);
        // แสดงข้อความบน LCD
        lcd.noBacklight();
        lcd.setCursor(0, 0);
        lcd.print("SMART PARKING");
        lcd.setCursor(0, 1);
        lcd.print("EMPTY: " + String(MAX_CAR_PARKING - number_car));
        lcd.backlight();
        delay(1000);
        // Servo เปิดประตู
        Serial.println("Opening gate...");
        myServo_In.write(90);
        delay(3000);
        myServo_In.write(0);
        delay(1000);
        Serial.println("Closing gate...");
      }
      // ถ้าที่จอดรถเต็มเงื่อนไขจะเป็นจริง
      if (number_car == MAX_CAR_PARKING) {
        // เปิดไฟ LED RED ตลอดจนกว่าจะมีที่ว่างในที่จอดรถ
        digitalWrite(LED_RED_PIN, HIGH);
        lcd.noBacklight();
        lcd.setCursor(0, 0);
        lcd.print("SMART PARKING");
        lcd.setCursor(0, 1);
        lcd.print("EMPTY: MAX");
        lcd.backlight();
        delay(1000);
      }
      // ถ้ามีรถออกจากที่จอดรถเงื่อนไขจะเป็นจริง
      if ((distance_Un2 > 0 && distance_Un2 < OBJECT_THRESHOLD) && number_car > 0) {
        // จำนวนรถ -1
        number_car--;
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(LED_GREEN_PIN, HIGH);
        delay(1000);
        digitalWrite(LED_GREEN_PIN, LOW);
        // แสดงข้อความบน LCD
        lcd.noBacklight();
        lcd.setCursor(0, 0);
        lcd.print("SMART PARKING");
        lcd.setCursor(0, 1);
        lcd.print("EMPTY: " + String(MAX_CAR_PARKING - number_car) + "  ");
        lcd.backlight();
        delay(1000);
        // แสดงผลบน Serial Monitor
        Serial.println("Opening gate...");
        myServo_Out.write(90);
        delay(3000);
        myServo_Out.write(0);
        delay(1000);
        Serial.println("Closing gate...");
      }
    }
    // เมื่อไม่ใช้รถคันเดิม
  } else {

    objectDetected = false;
  }
}
