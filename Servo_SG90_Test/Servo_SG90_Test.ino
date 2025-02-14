/*
สายสีน้ำตาล -> GND
สายสีแดง -> 5V
สายสีส้ม -> data
*/

#include <ESP32Servo.h>

#define SERVO_PIN 18  // เปลี่ยนเป็น GPIO ที่รองรับ PWM

Servo myServo;

void setup() {
  Serial.begin(115200);
  myServo.attach(SERVO_PIN);
}

void loop() {
  myServo.write(0);
  Serial.println("Servo at 0 degrees");
  delay(2000);
  
  myServo.write(90);
  Serial.println("Servo at 90 degrees");
  delay(2000);
  
  myServo.write(180);
  Serial.println("Servo at 180 degrees");
  delay(2000);
}

