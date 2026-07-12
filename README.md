# Arduino Smart Door Lock System

## Core Function
An embedded smart door lock system that authenticates users using a keypad password. The system provides visual and audio feedback, controls a servo motor to lock/unlock the door, and enhances security by locking the system after multiple failed login attempts.

## Main Components

- **Arduino Uno:** The microcontroller that processes user input and controls all connected components.
- **4×4 Keypad:** Used for password entry.
- **16×2 I2C LCD:** Displays system messages and user instructions.
- **Servo Motor:** Simulates the door locking and unlocking mechanism.
- **Green LED:** Indicates successful authentication.
- **Red LED:** Indicates an incorrect password.
- **Buzzer:** Provides different sound alerts for successful and failed authentication.

## Working Principle

The user enters a password using the keypad and presses `#` to confirm.
- If the password is correct, the green LED turns on, the buzzer plays a success melody, and the servo unlocks the door for five seconds before locking again.
- If the password is incorrect, the red LED lights up and the buzzer plays an error tone.
- After three consecutive failed attempts, the system locks for 20 seconds while displaying a countdown timer on the LCD.

## Future Improvements

- RFID authentication
- Fingerprint sensor integration
- Bluetooth/Wi-Fi remote access (ESP32)
- Mobile application support
- EEPROM password storage
