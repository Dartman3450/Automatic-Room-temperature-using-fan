#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define FAN_PIN 3
#define TEMP_THRESHOLD 27.1

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, HIGH);

  Serial.begin(9600);
  dht.begin();

  lcd.begin(16, 2);
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.setCursor(0, 1);
  lcd.print("Kipas: OFF");
}

void loop() {
  float suhu = dht.readTemperature();

  if (isnan(suhu)) {
    lcd.setCursor(0, 0);
    lcd.print("Gagal baca suhu ");
    Serial.println("Gagal baca sensor DHT!");
    digitalWrite(FAN_PIN, HIGH);
  } else {
    lcd.setCursor(6, 0);
    lcd.print("     ");
    lcd.setCursor(6, 0);
    lcd.print(suhu, 1);
    lcd.print(" C ");

    if (suhu >= TEMP_THRESHOLD) {
      digitalWrite(FAN_PIN, LOW); 
      lcd.setCursor(7, 1);
      lcd.print("ON ");
      Serial.println("Kipas ON");
    } else {
      digitalWrite(FAN_PIN, HIGH);
      lcd.setCursor(7, 1);
      lcd.print("OFF");
      Serial.println("Kipas OFF");
    }

    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print(" C, Kipas: ");
    Serial.println((suhu >= TEMP_THRESHOLD) ? "ON" : "OFF");
  }

  delay(2000);
}
