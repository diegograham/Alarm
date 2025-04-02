// Alarm Clock
// By: Diego J. Graham
// Allows the user to us an alarm clock with an arduino, LCD, DS1307, a few wires, 
// 4 buttons, a potentiometer, and a buzzer.
// Features: snooze button, adjustable alarm, 5 alarm noises, a stop button, a lamp, 
// and the ability to set the time.

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
const int adjustmentButton = 2;
const int hourButton = 5;
const int minuteButton = 4;
const int settingsButton = 3; 
const int relayPin = 13;
const int snoozeTime = 5; 

// Set Variables for the alarm to 0
int alarmHour = 0;
int alarmMinute = 0; // Fixed the incorrect variable name
int alarmNoise = 0;
int alarmLight = 1;


// Tracks wether the alarm is on or off
bool settingAlarm = false; 
bool settings = false;


// A set up loop, runs once
void setup() {
  lcd.begin(16,2); // Define the area of the LCD
  clock.begin(); // Start Clock
  Wire.begin(); // Start simple communication with embeded systems in RTC
  
  // Defines input and output for pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(adjustmentButton, INPUT_PULLUP);
  pinMode(hourButton, INPUT_PULLUP);
  pinMode(minuteButton, INPUT_PULLUP);
  pinMode(settingsButton, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, LOW);  // Ensure relay starts in OFF state

  // SET TIME ONCE, THEN COMMENT OUT AND REUPLOAD 
  //clock.setDateTime(2025, 03, 25, 15, 17, 00);

  // Allows buttons to interupt code
  attachInterrupt(digitalPinToInterrupt(adjustmentButton), toggleAlarmSetting, FALLING);
  attachInterrupt(digitalPinToInterrupt(settingsButton), toggleSettingsSetting, FALLING);

}


void toggleAlarmSetting() {
  settingAlarm = !settingAlarm;
}


void toggleSettingsSetting() {
  settings = !settings;
}


// Displays the Date and Time
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


// Defines the various alarm noises
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


// Adjusts the alarm time
void setAlarm() {
  // Activates the new screen 
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


// Selects the alarm noise the user wants
void setNoise() {
  // Set the cursor 
  lcd.setCursor(0, 1);
  lcd.print("Set Noise: ");
  lcd.print(alarmNoise + 1);

  // 5 alarm otions that go up each time the button is pressed
  if (digitalRead(settingsButton) == LOW){
    alarmNoise = (alarmNoise + 1) % 5;
    activateAlarm();
  }
}


// Selects the alarm light setting the user wants
void setLight() {
  // Set the cursor unter the alarm noise screen
  lcd.setCursor(0,1);
  lcd.print("Alarm Light: ");

  // Display on or off for the light 
  if (alarmLight == 0) {
    lcd.print("ON");
  } 
  else if (alarmLight == 1) {
    lcd.print("OFF");
  }

  // When button is pressed change the value for alarm light
  if (digitalRead(adjustmentButton) == LOW) {
    alarmLight = (alarmLight + 1) % 2;
  }
}


// Sets the time
void setTime(){
  //innitiate the interface
  lcd.setCursor(0, 0);
  lcd.print("Set Time: ");

  // Show the time
  if (dt.hour < 10) lcd.print("0");
  lcd.print(dt.hour);
  lcd.print(":");
  if (dt.minute < 10) lcd.print("0");
  lcd.print(dt.minute);

  // Set the Hour
  if (digitalRead(hourButton) == LOW){
    dt.hour = (dt.hour + 1) % 24;
    clock.setDateTime(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
  }
  
  // Set the Minute
  if (digitalRead(minuteButton) == LOW){
    dt.minute = (dt.minute + 1) % 60;
    clock.setDateTime(dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
  }
}

// Allows the user to switch through different screens
void selectScreen(){
  // Clock
  if (!settings && !settingAlarm) {
    displayTime(); // Clock
    // Turn the light off
    if (digitalRead(relayPin) == HIGH){
      if(digitalRead(hourButton) == LOW){
        digitalWrite(relayPin, LOW);
      }
    }
    // Turn the light on
    if (digitalRead(relayPin) == LOW){
      if(digitalRead(minuteButton) == LOW){
        digitalWrite(relayPin, HIGH);
      }
    }
  } 
  
  // Adjustment screen
  if (settingAlarm ) {
    adjustmentScreen();
  }
  
  // Setting screen
  if (settings){
    settingsScreen();
  }
}


// The settings screem
void settingsScreen(){
  lcd.clear();
  setLight();
  setTime();
}


// The adjustment screen
void adjustmentScreen(){
  lcd.clear();
  setAlarm();
  setNoise();
}


// The Alarm
// Allows the user to stop and snooze the alarm
void alarm(){
  // Check if it's time to activate the alarm
  while (dt.hour == alarmHour && dt.minute == alarmMinute && dt.second == 0) {
    // Continuously check the button until it is pressed
    while (digitalRead(settingsButton) == HIGH) {
      // Check to see if user wants the light to turn on when alarm goes off
      if(alarmLight == 0){
      digitalWrite(relayPin, HIGH);
      }  
      // Start the alarm noise
      activateAlarm();
      // Snooze button
      if (digitalRead(adjustmentButton)== LOW){
      // Turns off the light if snooze button is pressed
      digitalWrite(relayPin, LOW);  
        break;
      }
      // Wait for the button press 
      if (digitalRead(settingsButton) == LOW) {

        break;
      }
    }
    
    // Stop the buzzer when the button is pressed
    noTone(buzzerPin);
    break;
  }
}
  




// The main loop
void loop() {
  // Shorten the expression for ease of use
  dt = clock.getDateTime();
  
  // Define weather display shoud show clock, adjustment screen, or settings screen 
  selectScreen();
  
  // Sounds the alarm and snoozes or stops the alarm
  alarm();
  
  // Delay for smooth running
  delay(500);
}
