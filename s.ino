#include <Servo.h> // servo library
Servo s1;
const int trigPin = 2;
const int echoPin = 3;
long duration;
int distanceCm, distanceInch;
unsigned long servoOnTime = 0;  // เก็บเวลาเมื่อเซอร์โวเปิด
bool servoState = false;  // ตัวแปรที่ใช้ตรวจสอบสถานะเซอร์โว

void setup()
{
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  s1.attach(4);   // Servo Motor
}

void loop() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;
  Serial.println("Distance: ");
  Serial.println(distanceCm);
  delay(100);

  if(distanceCm < 5)
  {
    if (!servoState) {
      s1.write(140);  // เปิดเซอร์โว
      servoOnTime = millis();  // เก็บเวลาเริ่มต้นการเปิดเซอร์โว
      servoState = true;  // เปลี่ยนสถานะเป็นเปิด
    }
  }
  else
  {
    if (servoState && (millis() - servoOnTime >= 5000)) {  // ถ้าเซอร์โวยังคงเปิดเกิน 5 วินาที
      s1.write(0);  // ปิดเซอร์โว
      servoState = false;  // เปลี่ยนสถานะเป็นปิด
    }
  }
}
