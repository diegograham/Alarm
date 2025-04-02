// Alarm Clock
// Diego J. Graham
// Allows the user to us an alarm clock with an arduino, LCD, DS1307, a few wires, 
// 4 buttons, a potentiometer, and a buzzer
// Features: snooze button, adjustable alarm, 4 alarm noises, and a stop button

// Include Libraries
#include <Wire.h> 
#include <LiquidCrystal.h>
#include <DS3231.h>


// Set pins for LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


// Initiate the RTC, and shorten expressions
DS3231 clock;
RTCDateTime dt;


// Define Pins
const int buzzerPin = 6; 
const int setButton = 2; // Set button and snooze button
const int hourButton = 3;
const int minuteButton = 4;
const int noiseButton = 5; // Noise button and stop button


// Set Variables for the alarm to 0
int alarmHour = 0;
int alarmMinute = 0; // Fixed the incorrect variable name
int alarmNoise = 0;


// Tracks wether the alarm is on or off
bool settingAlarm = false; 


// A set up loop, runs once
void setup() {
  lcd.begin(16,2); // Define the area of the LCD
  clock.begin(); // Start Clock
  Wire.begin(); // Start simple communication with embeded systems in RTC
  
  // Defines input and output for pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(setButton, INPUT_PULLUP);
  pinMode(hourButton, INPUT_PULLUP);
  pinMode(minuteButton, INPUT_PULLUP);
  pinMode(noiseButton, INPUT_PULLUP);

  // Allows the set button to interupt code
  attachInterrupt(digitalPinToInterrupt(setButton), toggleAlarmSetting, FALLING);

}


// A loop to get the time that runs always
void loop() {
  dt = clock.getDateTime(); // Shorten the expression for ease of use

  // Define weather the clock should be on or adjustment screen
  if (!settingAlarm) {
    displayTime(); // Clock
  } else {
    adjustAlarmTime(); // Adjustment screen
    setNoise(); // Noise portion of adjustment screen
  }

  // Check if it's time to activate the alarm
  while (dt.hour == alarmHour && dt.minute == alarmMinute && dt.second == 0) {

    // Continuously check the button until it is pressed
    while (digitalRead(noiseButton) == HIGH) {
      activateAlarm();

      // Snooze button
      if (digitalRead(setButton)== LOW){
      alarmMinute += 5;
      noTone(buzzerPin);
        break;
      }

      // Wait for the button press (active LOW)
      if (digitalRead(noiseButton) == LOW) {
        break;
      }
    }
    
    // Stop the buzzer when the button is pressed
    noTone(buzzerPin);
    break;
  }

  delay(500);
}


// A function to define what the clock shows
void displayTime() {
  
  // Displays the year
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Date: ");
  lcd.print(dt.year); lcd.print("/");
  if (dt.month < 10) lcd.print("0"); lcd.print(dt.month); lcd.print("/");
  if (dt.day < 10) lcd.print("0"); lcd.print(dt.day);

  // Displays the time
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  if (dt.hour < 10) lcd.print("0"); lcd.print(dt.hour); lcd.print(":");
  if (dt.minute < 10) lcd.print("0"); lcd.print(dt.minute); lcd.print(":");
  if (dt.second < 10) lcd.print("0"); lcd.print(dt.second);
}


// A loop to alwayss check if the alarm needs to be set 
void toggleAlarmSetting() {
  settingAlarm = !settingAlarm; // Toggle alarm setting mode
}


// A loop that allows you to adjust the alarm time
void adjustAlarmTime() {

  // Activates the new screen 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Alarm: ");

  // The logic for how to display the time being set
  if (alarmHour < 10) lcd.print("0"); lcd.print(alarmHour); lcd.print(":");
  if (alarmMinute < 10) lcd.print("0"); lcd.print(alarmMinute);


  // The amount that the hour increses each time button is pressed
  if (digitalRead(hourButton) == LOW) {
    alarmHour = (alarmHour + 1) % 24;
    delay(200);
  }

  // The amount that the hour increses each time button is pressed
  if (digitalRead(minuteButton) == LOW) {
    alarmMinute = (alarmMinute + 1) % 60;
    delay(200);
  }
}


// Select the noise the user wants
void setNoise() {

  // Set the cursor under the Set Alarm option
  lcd.setCursor(0, 1);
  lcd.print("Set Noise: ");

  lcd.print(alarmNoise + 1);

  // 5 alarm otions that go up each time the button is pressed
  if (digitalRead(noiseButton) == LOW){
    alarmNoise = (alarmNoise + 1) % 5;
    activateAlarm();
  }

}



// A loop to define what the alarm noise is
void activateAlarm() {

  // Default Noise
  if (alarmNoise == 0){
    for (int i = 0; i < 5; i++) { // Beep 5 times
      tone(buzzerPin, 1000); // 1000 Hz beep
      delay(500);
      noTone(buzzerPin);
      delay(500);
  }
  }

  // Second Noise
  if (alarmNoise == 1){
    for (int freq = 500; freq <= 1500; freq += 50) {
        tone(buzzerPin, freq);
        delay(50);
    }
    for (int freq = 1500; freq >= 500; freq -= 50) {
        tone(buzzerPin, freq);
        delay(50);
    }
    noTone(buzzerPin);
  }

  // Third Noise
  if (alarmNoise == 2){
    for (int i = 0; i < 10; i++) {
        tone(buzzerPin, 1500); // Higher pitch
        delay(200);
        noTone(buzzerPin);
        delay(200);
  }
  }

  // Forth Noise
  if (alarmNoise == 3){
    for (int i = 0; i < 3; i++) {
        tone(buzzerPin, 1200); // First beep
        delay(300);
        noTone(buzzerPin);
        delay(100);
        tone(buzzerPin, 1200); // Second beep
        delay(300);
        noTone(buzzerPin);
        delay(700);
    }
  }

  // Fifth Noise
  if (alarmNoise == 4){
    for (int freq = 2000; freq >= 500; freq -= 100) {
        tone(buzzerPin, freq);
        delay(100);
    }
    noTone(buzzerPin);
  }
  }


