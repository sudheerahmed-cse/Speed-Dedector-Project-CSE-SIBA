#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// CHANGE THIS ADDRESS AFTER SCANNING
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
int sensor1 = 2;
int sensor2 = 3;
int buzzer = 8;

// Parameters
float distanceBetweenSensors = 0.10;   // 10 cm = 0.10 meter
float speedLimit = 40.0;               // km/h limit

unsigned long t1, t2;

void setup() {
  // Pin modes
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  // LCD
  lcd.init();          
  lcd.backlight();     

  lcd.setCursor(0, 0);
  lcd.print("Speed Detector");
  delay(1500);
  lcd.clear();
}

void loop() {

  // Wait for sensor 1 detection
  if (digitalRead(sensor1) == LOW) {
    t1 = micros();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor 1 Hit");
    delay(100);
  }

  // Wait for sensor 2 detection
  if (digitalRead(sensor2) == LOW) {
    t2 = micros();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor 2 Hit");

    // Speed calculation
    float timeSeconds = (t2 - t1) / 1000000.0;        // microseconds → seconds
    float speed = (distanceBetweenSensors / timeSeconds) * 3.6;  // m/s → km/h

    delay(200);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Speed: ");
    lcd.print(speed);
    lcd.print(" km/h");

    // Overspeed check
    lcd.setCursor(0, 1);
    if (speed > speedLimit) {
      lcd.print("Over Speed!!!");
      digitalWrite(buzzer, HIGH);
    } else {
      lcd.print("Normal Speed");
      digitalWrite(buzzer, LOW);
    }

    delay(1500);
    digitalWrite(buzzer, LOW);
    lcd.clear();
  }
}
