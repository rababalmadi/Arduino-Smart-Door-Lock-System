//=====================================================
// Libraries
//=====================================================
#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>

//=====================================================
// LCD and Servo Objects
//=====================================================
Adafruit_LiquidCrystal lcd(0);
Servo ServoDoorLock;

//=====================================================
// Keypad Configuration
//=====================================================
const byte Rows = 4;
const byte Colms = 4;

char hexaKeys[Rows][Colms] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte RowPins[Rows] = {13,12,11,10};
byte ColmsPins[Colms] = {9,8,7,6};

Keypad Mykeypad = Keypad(makeKeymap(hexaKeys), RowPins, ColmsPins, Rows, Colms);

//=====================================================
// Password Variables
//=====================================================
String Password = "12AB89";   // Correct password
String Input = "";            // Stores user input
int WrongAttempts = 0;        // Counts wrong password attempts

//=====================================================
// Output Pins
//=====================================================
int RedLED = 4;
int GreenLED = 3;
int Buzzer = 2;

//=====================================================
// Setup Function
// Initializes all components
//=====================================================
void setup()
{
  // Configure output pins
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  // Initialize servo motor
  ServoDoorLock.attach(5);
  ServoDoorLock.write(0);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.setBacklight(1);

  // Display welcome message
  lcd.setCursor(4,0);
  lcd.print("Welcome!");
  delay(500);

  // Display password prompt
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
  lcd.setCursor(0,1);
}

//=====================================================
// Main Program
//=====================================================
void loop()
{
  // Read pressed key
  char Key = Mykeypad.getKey();

  // Continue only if a key is pressed
  if(Key != NO_KEY)
  {
    // Backspace: remove the last entered character
    if(Key == '*')
    {
      if(Input.length() > 0)
      {
        Input.remove(Input.length() - 1);
        lcd.setCursor(Input.length(), 1);
        lcd.print(" ");
        lcd.setCursor(Input.length(), 1);
      }
    }

    // Check entered password
    else if(Key == '#')
    {
      // Correct password
      if(Input == Password)
      {
        WrongAttempts = 0;

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Access Granted");
        lcd.setCursor(0,1);
        lcd.print("Door Opened");

        // Green LED and success melody
        digitalWrite(GreenLED, HIGH);

        tone(Buzzer,1000);
        delay(100);
        tone(Buzzer,1400);
        delay(150);
        tone(Buzzer,1800);
        delay(300);
        noTone(Buzzer);

        // Open the door
        ServoDoorLock.write(90);
        delay(5000);

        // Lock the door again
        ServoDoorLock.write(0);
        digitalWrite(GreenLED, LOW);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Door Locked");
        delay(2000);
      }

      // Wrong password
      else
      {
        WrongAttempts++;

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Wrong Password");

        lcd.setCursor(0,1);
        lcd.print("Try Again");

        // Red LED and error tone
        digitalWrite(RedLED, HIGH);

        tone(Buzzer,2000);
        delay(600);

        noTone(Buzzer);
        digitalWrite(RedLED, LOW);

        delay(1000);

        // Lock the system after 3 failed attempts
        if(WrongAttempts >= 3)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("System Locked");
          delay(1000);

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Wait 20 Sec");
          delay(1000);

          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Wait:");

          // Display countdown
          for(int i = 20; i >= 1; i--)
          {
            lcd.setCursor(0,1);
            lcd.print(i);
            lcd.print(" sec ");
            delay(1000);
          }

          WrongAttempts = 0;
        }
      }

      // Clear input and return to password screen
      Input = "";

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Password:");
      lcd.setCursor(0,1);
    }

    // Store pressed key
    else
    {
      Input += Key;
      lcd.print("*");
    }
  }
}