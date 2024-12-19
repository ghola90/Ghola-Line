/*

Ghola Loop Code Version - 1.0 - Jan 2025 - Make the motor move

Pin use:

A0 - 
A1 - 
A2 - 
A3 - 
A4 - SDA on LCD
A5 - SCL on LCD

D0 - 
D1 - 
D2 - 
D3 - 
D4 - 
D5 - 
D6 - 
D7 - 
D8 - 
D9 - motor driver pin IN2
D10- motor driver pin IN1
D11- motor driver pin ENT
D12- 
D13- 

*/

#include <LiquidCrystal_I2C.h>       // inlude required LCD library
LiquidCrystal_I2C lcd(0x27, 16, 2);  // use this for 16x2 LCD modules

int Motor_1 = 9;   // assign motor driver pin IN2 to pin 9
int Motor_2 = 10;  // assign motor driver pin IN1 to pin 10
int ENA = 11;      // assign motor driver pin ENA to pin 11


void setup() {

  lcd.init();       // initialize the LCD
  lcd.backlight();  // turn on the backlight for the LCD

  pinMode(Motor_1, OUTPUT);  // set the mode for the pin INPUT/OUTPUT
  pinMode(Motor_2, OUTPUT);  // set the mode for the pin INPUT/OUTPUT
}


void loop() {

  lcd.clear();           // clear LCD screen
  lcd.setCursor(0, 0);   // set cursor to 1st character on 1st line
  lcd.print("Train 1");  // print x on the LCD screen
  lcd.setCursor(0, 1);   // set cursor to 1st character on 2nd line
  lcd.print("STOP");     // print x on the LCD screen

  digitalWrite(Motor_1, LOW);  // the train will stop
  digitalWrite(Motor_2, LOW);  // the train will stop

  delay(4000);  // delay for (x)

  lcd.clear();               // clear LCD screen
  lcd.setCursor(0, 0);       // set cursor to 1st character on 1st line
  lcd.print("Train 1 100");  // print x on the LCD screen
  lcd.setCursor(0, 1);       // set cursor to 1st character on 2nd line
  lcd.print("Speeding Up");  // print x on the LCD screen

  analogWrite(ENA, 100);        // set train speed x on 0-255 range
  digitalWrite(Motor_1, LOW);   // the train will move
  digitalWrite(Motor_2, HIGH);  // the train will move

  delay(1000);  // delay for (x)

  lcd.clear();               // clear LCD screen
  lcd.setCursor(0, 0);       // set cursor to 1st character on 1st line
  lcd.print("Train 1 130");  // print x on the LCD screen
  lcd.setCursor(0, 1);       // set cursor to 1st character on 2nd line
  lcd.print("Speeding Up");  // print x on the LCD screen

  analogWrite(ENA, 130);  // set train speed x on 0-255 range

  delay(1000);  // delay for (x)

  lcd.clear();               // clear LCD screen
  lcd.setCursor(0, 0);       // set cursor to 1st character on 1st line
  lcd.print("Train 1 160");  // print x on the LCD screen
  lcd.setCursor(0, 1);       // set cursor to 1st character on 2nd line
  lcd.print("Full Speed ");  // print x on the LCD screen

  analogWrite(ENA, 160);  // set train speed x on 0-255 range

  delay(1000);  // delay for (x)
}
