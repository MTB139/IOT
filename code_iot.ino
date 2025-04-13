#include <Servo.h>

const int tempPin = A0;      // TMP36
const int buzzerPin = 13;    // Buzzer
const int buttonPin = 2;     // Button
const int fireThreshold = 50; // Nhiệt độ cảnh báo cháy (°C)

Servo myServo;
bool alarmOn = false;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Sử dụng trở kéo lên nội bộ
  myServo.attach(9); // Servo ở chân D9
  myServo.write(0);  // Vị trí ban đầu
}

void loop() {
  // Đọc nhiệt độ từ cảm biến TMP36
  float voltage = analogRead(tempPin) * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100;

  Serial.print("Nhiet do: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  // Kiểm tra nếu vượt ngưỡng cháy
  if (temperatureC >= fireThreshold && !alarmOn) {
    digitalWrite(buzzerPin, HIGH);  // Bật còi
    myServo.write(90);              // Xoay servo (giả sử đóng van gas, mở cửa...)
    alarmOn = true;
    Serial.println("🔥 Canh bao chay!!!");
  }

  // Kiểm tra nút nhấn để tắt báo động
  if (digitalRead(buttonPin) == LOW && alarmOn) {
    digitalWrite(buzzerPin, LOW);
    myServo.write(0);               // Trả về trạng thái ban đầu
    alarmOn = false;
    Serial.println("✅ Da tat bao dong.");
    delay(1000); // Chống rung nút
  }

  delay(500); // Chờ để đọc lại
}
