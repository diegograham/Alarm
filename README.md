# Arduino Alarm Clock

**By:** Diego J. Graham

## Overview

This project is an Arduino-based alarm clock that uses an LCD, DS3231 Real-Time Clock (RTC), and a variety of buttons for user interaction. The alarm clock includes features such as setting the time, adjusting the alarm time, selecting from five alarm sounds, snooze functionality, and controlling a lamp when the alarm rings.

### Features:
- Snooze button
- Adjustable alarm time
- 5 different alarm sounds
- Stop button to turn off the alarm
- Lamp control (via relay)
- Set current time using buttons

## Components Used:
- Arduino (e.g., Arduino Uno)
- LCD (Liquid Crystal Display)
- DS3231 RTC (Real-Time Clock Module)
- Buzzer
- 4 Buttons
- Relay (for controlling a lamp)
- Potentiometer (for controlling alarm settings)
  
## Pin Assignments:
- **LCD Pins:** 7, 8, 9, 10, 11, 12
- **Buzzer Pin:** 6
- **Adjustment Button:** 2
- **Hour Button:** 5
- **Minute Button:** 4
- **Settings Button:** 3
- **Relay Pin:** 13

## Libraries Used:
- `Wire.h` (for I2C communication)
- `LiquidCrystal.h` (for LCD display)
- `DS3231.h` (for RTC functionality)

## Functions:

### `setup()`
- Initializes the LCD, RTC, and pins.
- Sets up interrupts for button presses.

### `toggleAlarmSetting()`
- Toggles the alarm setting mode.

### `toggleSettingsSetting()`
- Toggles the settings mode.

### `displayTime()`
- Displays the current date and time on the LCD.

### `activateAlarm()`
- Activates the alarm with different sounds based on the selected alarm noise.

### `setAlarm()`
- Allows the user to set the alarm time.

### `setNoise()`
- Allows the user to select the alarm noise.

### `setLight()`
- Allows the user to toggle the alarm light on or off.

### `setTime()`
- Allows the user to set the current time.

### `selectScreen()`
- Displays the current screen (time, alarm settings, or adjustment settings).

### `settingsScreen()`
- Displays the settings screen for adjusting light and time.

### `adjustmentScreen()`
- Displays the screen for adjusting alarm time and noise.

### `alarm()`
- Activates the alarm at the set time, handles snooze functionality, and stops the alarm when the stop button is pressed.

## How to Use:

1. **Set the Time**: Press the settings button to access the time-setting screen. Use the hour and minute buttons to adjust the time.
2. **Set the Alarm**: Once the time is set, press the adjustment button to enter the alarm-setting screen. Use the hour and minute buttons to set the alarm time.
3. **Select Alarm Sound**: Press the settings button while in the alarm-setting screen to cycle through the five different alarm sounds.
4. **Enable/Disable Lamp**: The relay controls a lamp. You can enable or disable it via the settings screen.
5. **Snooze/Stop Alarm**: When the alarm goes off, you can press the snooze button to delay it or the stop button to turn it off.

## Notes:
- You may need to set the time manually once, and then comment out the time-setting line after uploading the code.
- The relay pin controls a lamp and can be connected to any device that works with an on/off relay.
  
## License:
This project is open source and free to use with credit.
