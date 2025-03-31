#include <DHT.h>
#include <Servo.h>

#define DHTPIN 2       // DHT11 data pin
#define DHTTYPE DHT11  // DHT11 sensor type
#define FLAME_PIN 3    // IR flame sensor pin
#define GAS_PIN A0     // MQ-2 gas sensor pin
#define SERVO_PIN 9    // Servo motor pin

DHT dht(DHTPIN, DHTTYPE);
Servo servo;

void setup() {
  Serial.begin(9600);
  dht.begin();
  servo.attach(SERVO_PIN);
  pinMode(FLAME_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);
}

void loop() {
  float temperature = dht.readTemperature();
  int flame = digitalRead(FLAME_PIN);
  int gas = analogRead(GAS_PIN);

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Gas Level: ");
  Serial.println(gas);
  Serial.print("Flame Detected: ");
  Serial.println(flame == LOW ? "Yes" : "No");

  if (gas > 300 || flame == LOW || temperature > 50) {
    Serial.println("Fire detected! Activating servo...");
    servo.write(90);  // Move servo to indicate alert
    delay(1000);
    servo.write(0);   // Reset servo position
  }

  delay(2000);
}