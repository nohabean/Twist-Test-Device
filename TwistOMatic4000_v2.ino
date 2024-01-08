#define button 2

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,20,4);
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
int count = 0;

void setup()
{
  // initialize the button
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);

  // initialize the lcd
  lcd.init();               
  lcd.backlight();
  lcd.setCursor(1,1);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(1);
}

void loop()
{
  if (digitalRead(button) == LOW)           // LOW means the device is on
  {
    for (pos = 1; pos <= 119; pos += 1)     // go forward
    {
      // in steps of 1 degree
      myservo.write(pos);
      delay(5.5);
      // Serial.print("forward");           // test in the terminal
    }

    for (pos = 119; pos >= 1; pos -= 1)     // go backward
    {
      myservo.write(pos);
      delay(5.5);
      // Serial.print("backward");           // test in the terminal
      
      // counts one full forward and backward cycle completion
      if(pos == 1)
      {
        count++;
      }
    }

    // clears any previous cycle count and displays the current cycle count
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print("Cycles: ");
    lcd.print(count);

    // prints in the terminal
    Serial.print("Cycles: ");
    Serial.println(count);
  }
  
  if (digitalRead(button) == HIGH)      // HIGH means the device is off, reset count
  {
    count = 0;
  }
}
