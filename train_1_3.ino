/* 

Ghola Loop Code Version - 1.3 - Jan 2025 - Add RED/GREEN LED signal and using TIP122 transistor

Pin use:

A0 - 
A1 - 
A2 - 
A3 - 
A4 - SDA on LCD
A5 - SCL on LCD

D0 - 
D1 - 
D2 - IR Sensor #1
D3 - IR Sensor #2
D4 - 
D5 - 
D6 - 
D7 - Red LED on transistor X--
D8 - Green LED on transistor X--
D9 - motor driver pin IN2
D10- motor driver pin IN1
D11- motor driver pin ENT
D12- 
D13- 

*/

#include <LiquidCrystal_I2C.h>       // inlude required LCD library
LiquidCrystal_I2C lcd(0x27, 16, 2);  // use this for 16x2 LCD modules

int Sensor_at_station = 2;      // IR sensor pin 2
int Sensor_before_station = 3;  // IR sensor pin 3

int red_led = 7;    // red light pin 7
int green_led = 8;  // green light pin 8

int Motor_1 = 9;   // assign motor driver pin IN2 to pin 9
int Motor_2 = 10;  // assign motor driver pin IN1 to pin 10
int ENA = 11;      // assign motor driver pin ENA to pin 11

int train_loop = 0;  // set default value of train_loop to 0


void setup() {

  lcd.init();       // initialize the LCD
  lcd.backlight();  // turn on the backlight for the LCD

  pinMode(Motor_1, OUTPUT);               // set the mode for the pin INPUT/OUTPUT
  pinMode(Motor_2, OUTPUT);               // set the mode for the pin INPUT/OUTPUT
  pinMode(Sensor_at_station, INPUT);      // set the mode for the pin INPUT/OUTPUT
  pinMode(Sensor_before_station, INPUT);  // set the mode for the pin INPUT/OUTPUT
  pinMode(red_led, OUTPUT);               // set the mode for the pin INPUT/OUTPUT
  pinMode(green_led, OUTPUT);             // set the mode for the pin INPUT/OUTPUT
}


void loop() {

  if (train_loop == 0) {            // if train_loop value is 0 run this
    analogWrite(ENA, 160);          // set train speed x on 0-255 range
    lcd.setCursor(0, 0);            // set cursor to 1st character on 1st line
    lcd.print("Train 1");           // print x on the LCD screen
    lcd.setCursor(0, 1);            // set cursor to 1st character on 2nd line
    lcd.print("First Run");         // print x on the LCD screen
    digitalWrite(Motor_1, LOW);     // the train will move
    digitalWrite(Motor_2, HIGH);    // the train will move
    digitalWrite(red_led, LOW);     // turn ON/OFF the led
    digitalWrite(green_led, HIGH);  // turn ON/OFF the led
    delay(5000);                    // delay for (x)
    train_loop = 1;                 // set train_loop value to 1
    lcd.clear();                    // clear LCD screen
    lcd.setCursor(0, 0);            // set cursor to 1st character on 1st line
    lcd.print("Train 1 Active ");   // print x on the LCD screen
  }

  if (train_loop == 1) {  // if train_loop value is 1 run this

    if (digitalRead(Sensor_before_station) == LOW) {  // check if Sensor_before_station was triggered and then run this code

      lcd.clear();                  // clear LCD screen
      lcd.setCursor(0, 0);          // set cursor to 1st character on 1st line
      lcd.print("Train 1 160");     // print x on the LCD screen
      lcd.setCursor(0, 1);          // set cursor to 1st character on 2nd line
      lcd.print("Slowing Down");    // print x on the LCD screen
      analogWrite(ENA, 160);        // set train speed x on 0-255 range
      digitalWrite(Motor_1, LOW);   // the train will move
      digitalWrite(Motor_2, HIGH);  // the train will move

      delay(1000);  // delay for (x)

      lcd.clear();                // clear LCD screen
      lcd.setCursor(0, 0);        // set cursor to 1st character on 1st line
      lcd.print("Train 1 130");   // print x on the LCD screen
      lcd.setCursor(0, 1);        // set cursor to 1st character on 2nd line
      lcd.print("Slowing Down");  // print x on the LCD screen
      analogWrite(ENA, 130);      // set train speed x on 0-255 range

      delay(1000);  // delay for (x)

      lcd.clear();                // clear LCD screen
      lcd.setCursor(0, 0);        // set cursor to 1st character on 1st line
      lcd.print("Train 1 100");   // print x on the LCD screen
      lcd.setCursor(0, 1);        // set cursor to 1st character on 2nd line
      lcd.print("Slowing Down");  // print x on the LCD screen
      analogWrite(ENA, 100);      // set train speed x on 0-255 range

      digitalWrite(red_led, HIGH);   // turn ON/OFF the led
      digitalWrite(green_led, LOW);  // turn ON/OFF the led
    }

    if (digitalRead(Sensor_at_station) == LOW) {  // check if Sensor_at_station was triggered and then run this code

      lcd.clear();                  // clear LCD screen
      lcd.setCursor(0, 0);          // set cursor to 1st character on 1st line
      lcd.print("Train 1 100");     // print x on the LCD screen
      lcd.setCursor(0, 1);          // set cursor to 1st character on 2nd line
      lcd.print("Slowing Down");    // print x on the LCD screen
      analogWrite(ENA, 100);        // set train speed x on 0-255 range
      digitalWrite(Motor_1, LOW);   // the train will move
      digitalWrite(Motor_2, HIGH);  // the train will move

      delay(1000);  // delay for (x)

      lcd.clear();                 // clear LCD screen
      lcd.setCursor(0, 0);         // set cursor to 1st character on 1st line
      lcd.print("Train 1");        // print x on the LCD screen
      lcd.setCursor(0, 1);         // set cursor to 1st character on 2nd line
      lcd.print("STOP");           // print x on the LCD screen
      digitalWrite(Motor_1, LOW);  // the train will stop
      digitalWrite(Motor_2, LOW);  // the train will stop

      delay(4000);  // delay for (x)

      digitalWrite(red_led, LOW);     // turn ON/OFF the led
      digitalWrite(green_led, HIGH);  // turn ON/OFF the led

      delay(1000);  // delay for (x)

      lcd.clear();                  // clear LCD screen
      lcd.setCursor(0, 0);          // set cursor to 1st character on 1st line
      lcd.print("Train 1 100");     // print x on the LCD screen
      lcd.setCursor(0, 1);          // set cursor to 1st character on 2nd line
      lcd.print("Speeding Up");     // print x on the LCD screen
      analogWrite(ENA, 100);        // set train speed x on 0-255 range
      digitalWrite(Motor_1, LOW);   // the train will move
      digitalWrite(Motor_2, HIGH);  // the train will move

      delay(1000);  // delay for (x)

      lcd.clear();               // clear LCD screen
      lcd.setCursor(0, 0);       // set cursor to 1st character on 1st line
      lcd.print("Train 1 130");  // print x on the LCD screen
      lcd.setCursor(0, 1);       // set cursor to 1st character on 2nd line
      lcd.print("Speeding Up");  // print x on the LCD screen
      analogWrite(ENA, 130);     // set train speed x on 0-255 range

      delay(1000);  // delay for (x)

      lcd.clear();               // clear LCD screen
      lcd.setCursor(0, 0);       // set cursor to 1st character on 1st line
      lcd.print("Train 1 160");  // print x on the LCD screen
      lcd.setCursor(0, 1);       // set cursor to 1st character on 2nd line
      lcd.print("Full Speed ");  // print x on the LCD screen
      analogWrite(ENA, 160);     // set train speed x on 0-255 range
    }
  }
}
