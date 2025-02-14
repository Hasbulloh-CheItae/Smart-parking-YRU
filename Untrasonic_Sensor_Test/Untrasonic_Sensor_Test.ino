/*
Ultrasonic Sensor:
โค้ดนี้จะส่งสัญญาณจากขา trigPin และรับค่ากลับที่ echoPin เพื่อคำนวณระยะทางจากเซนเซอร์
อัปโหลดโค้ดไปยังบอร์ด Arduino แล้วเปิด Serial Monitor เพื่อตรวจสอบค่าระยะทางที่อ่านได้! 🚀

หลักการทำงานของ Ultrasonic Sensor (เช่น HC-SR04)
เซนเซอร์ Ultrasonic ใช้หลักการของ คลื่นเสียงอัลตราโซนิก (Ultrasonic Waves) เพื่อวัดระยะทางของวัตถุ
โดยการส่งคลื่นเสียงความถี่สูงและคำนวณเวลาที่คลื่นเสียงสะท้อนกลับมายังตัวเซนเซอร์

🔧 โครงสร้างของ HC-SR04
เซนเซอร์ HC-SR04 ประกอบด้วย สองส่วนหลัก:
1.Transmitter (Trig Pin) → ส่งคลื่นเสียงอัลตราโซนิกออกไป
2.Receiver (Echo Pin) → รับคลื่นเสียงที่สะท้อนกลับมา
3.VCC (5V)

⚙️ ขั้นตอนการทำงาน
1.ส่งสัญญาณเสียง:
-Arduino จะส่งพัลส์ไฟฟ้า HIGH ไปที่ขา Trig เป็นเวลา 10 ไมโครวินาที (10 µs)
-เซนเซอร์จะส่งคลื่นเสียงอัลตราโซนิกออกไปที่ความถี่ 40 kHz

2.รับคลื่นเสียงสะท้อนกลับ
-คลื่นเสียงเดินทางไปกระทบวัตถุแล้วสะท้อนกลับมา
-เมื่อคลื่นเสียงกลับถึงเซนเซอร์ ขา Echo จะเปลี่ยนเป็น HIGH และจับเวลาการเดินทางของเสียง
3.คำนวณระยะทาง
ใช้สูตร:
Distance=Time × Speed of Sound/2
-โดยที่ Speed of Sound = 343 m/s = 0.034 cm/µs
-หารด้วย 2 เพราะเสียงเดินทางไป-กลับ

🛠 ข้อจำกัดของ Ultrasonic Sensor
-ระยะตรวจจับโดยทั่วไปอยู่ที่ 2 cm - 400 cm
-อาจได้รับผลกระทบจาก พื้นผิวของวัตถุ (พื้นผิวขรุขระอาจทำให้เสียงสะท้อนไม่ตรง)
-อุณหภูมิและความชื้นสามารถมีผลต่อความเร็วเสียง

📌 สรุป:
Ultrasonic Sensor ใช้หลักการส่งและรับคลื่นเสียงเพื่อวัดระยะทาง และเหมาะสำหรับงาน ตรวจจับวัตถุ, หุ่นยนต์เลี่ยงสิ่งกีดขวาง, และระบบวัดระดับน้ำ เป็นต้น 🚀
*/
const int trigPin = 33;
const int echoPin = 32;

void setup() {
    Serial.begin(115200); // เริ่มต้น Serial Monitor
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    long duration;
    float distance;
    
    // ส่งสัญญาณ Trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // อ่านค่าจาก Echo Pin
    duration = pulseIn(echoPin, HIGH);
    
    // คำนวณระยะทาง (หน่วย: เซนติเมตร)
    distance = duration * 0.034 / 2;
    
    // แสดงผลบน Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    delay(500); // รอ 500ms ก่อนวัดค่าใหม่
}
