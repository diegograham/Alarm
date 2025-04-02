#include <Wire.h>
#include <LiquidCrystal.h>
#include <DS3231.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  // LCD connected to these pins
DS3231 clock;
RTCDateTime dt;
const int buzzerPin = 6;
const int buttonPin = 2;
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  clock.begin();
  pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as output
  pinMode(buttonPin, INPUT_PULLUP);  // Button pin as input with pullup resistor
  
  // 🚨 SET TIME ONCE, THEN COMMENT OUT AND REUPLOAD 🚨
  //clock.setDateTime(2025, 02, 22, 13, 19, 00);
}

void loop() {
  dt = clock.getDateTime();  // Get current time from RTC

  // 🚨 Do NOT use lcd.clear() every loop! It causes flickering.
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.print(dt.year); lcd.print("/");
  if (dt.month < 10) lcd.print("0"); lcd.print(dt.month); lcd.print("/");
  if (dt.day < 10) lcd.print("0"); lcd.print(dt.day);

  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  if (dt.hour < 10) lcd.print("0"); lcd.print(dt.hour); lcd.print(":");
  if (dt.minute < 10) lcd.print("0"); lcd.print(dt.minute); lcd.print(":");
  if (dt.second < 10) lcd.print("0"); lcd.print(dt.second);

  // Print to Serial Monitor for debugging
  Serial.print("Time: ");
  Serial.print(dt.hour); Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.println(dt.second);

  delay(1000);  // Update every second

  // Check for the alarm time (21:05:00)
  if (dt.hour == 13 && dt.minute == 26 && dt.second == 50) {
    tone(buzzerPin, 200);  // Start buzzer sound at 500 Hz
    delay(250);            // Wait for 250ms
    tone(buzzerPin, 500);  // Change to 250 Hz
    delay(250);            // Wait for 250ms

    // Continuously check the button until it is pressed
    while (digitalRead(buttonPin) == HIGH) {
      // Wait for the button press (active LOW)
    }
    
    // Stop the buzzer when the button is pressed
    noTone(buzzerPin);  
  }
}
