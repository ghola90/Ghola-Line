/*

Ghola Loop Code Version - 1.6 - Jan 2025 - Adding Tunnel Stop and using random delay to stop the train
 
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
D4 - IR Sensor #3
D5 - Tunnel Red LED
D6 - Tunnel Green LED
D7 - Station Signal Red LED
D8 - Station Signal Green LED
D9 - motor driver pin IN2
D10- motor driver pin IN1
D11- motor driver pin ENT
D12- DFPlayer TX
D13- DFPlayer RX

*/

#include <LiquidCrystal_I2C.h>       // LCD library
LiquidCrystal_I2C lcd(0x27, 16, 2);  // for 16x2 LCD modules
// LiquidCrystal_I2C lcd(0x3F, 20, 4);  // for 20x4 LCD modules

#include "SoftwareSerial.h"       // SoftwareSerial library req. to communicate with DFPlayer Mini
#include "DFRobotDFPlayerMini.h"  // DFPlayer Mini library

int Sensor_at_station = 2;      // assign IR sensor to pin 2
int Sensor_before_station = 3;  // assign IR sensor to pin 3
int Sensor_tunnel = 4;          // assign IR sensor to pin 4

int red_tunnel = 5;    // red light pin 5
int green_tunnel = 6;  // green light pin 6

int red_led = 7;    // red light pin 7
int green_led = 8;  // green light pin 8

int Motor_1 = 9;   // assign motor driver pin IN2 to pin 9
int Motor_2 = 10;  // assign motor driver pin IN1 to pin 10
int ENA = 11;      // assign motor driver pin ENA to pin 11

int train_loop = 0;  // set train_loop variable to 0
int at_station = 1;  // set at_station variable to 1

int station_led = 1;  // set station_led variable to 1

int train_number = 1;  // set train_number variable

int tunnel_stop = 0;  // set tunnel_stop variable

SoftwareSerial softwareSerial(13, 12);  // Connect to module's RX to pin 13 and TX to pin 12
DFRobotDFPlayerMini player;


void setup() {

  lcd.init();       // initialize the LCD
  lcd.backlight();  // turn on the backlight for the LCD

  pinMode(Motor_1, OUTPUT);               // set the mode for the pin INPUT/OUTPUT
  pinMode(Motor_2, OUTPUT);               // set the mode for the pin INPUT/OUTPUT
  pinMode(Sensor_at_station, INPUT);      // set the mode for the pin INPUT/OUTPUT
  pinMode(Sensor_before_station, INPUT);  // set the mode for the pin INPUT/OUTPUT
  pinMode(Sensor_tunnel, INPUT);          // set the mode for the pin INPUT/OUTPUT

  pinMode(red_tunnel, OUTPUT);    // set the mode for the pin INPUT/OUTPUT
  pinMode(green_tunnel, OUTPUT);  // set the mode for the pin INPUT/OUTPUT

  pinMode(red_led, OUTPUT);    // set the mode for the pin INPUT/OUTPUT
  pinMode(green_led, OUTPUT);  // set the mode for the pin INPUT/OUTPUT

  softwareSerial.begin(9600);  // Initialize serial port for DFPlayer

  // Test DFPlayer
  if (player.begin(softwareSerial)) {
    lcd.clear();               // clear LCD screen
    lcd.setCursor(0, 0);       // set cursor to 1st character on 1st line
    lcd.print("DFPlayer OK");  // print x on the LCD screen
    delay(1000);               // delay for (x)
  } else {
    lcd.clear();                   // clear LCD screen
    lcd.setCursor(0, 0);           // set cursor to 1st character on 1st line
    lcd.print("DFPlayer failed");  // print x on the LCD screen
    while (true)
      ;  // stops the program
  }
}


void loop() {                   // enable the motor
  digitalWrite(Motor_1, LOW);   // the train will move
  digitalWrite(Motor_2, HIGH);  // the train will move

  if (train_loop == 0) {      // if train_loop value is 0 run this code
    analogWrite(ENA, 160);    // default train speed 0-255
    lcd.clear();              // clear LCD screen
    lcd.setCursor(0, 0);      // set cursor to 1st character on 1st line
    lcd.print("Train ");      // print x on the LCD screen
    lcd.print(train_number);  // print value of train_number on the LCD screen
    lcd.print(" ");           // print " " on the LCD screen
    lcd.setCursor(0, 1);      // set cursor to 1st character on 2nd line
    lcd.print("First Run ");  // print x on the LCD screen

    digitalWrite(Motor_1, LOW);   // the train will move
    digitalWrite(Motor_2, HIGH);  // the train will move

    station_signal(9);  // set the signal led, green=1 red=0 both=9

    delay(5000);  // delay for (x)

    train_loop = 1;           // set train_loop variable to 1
    lcd.clear();              // clear LCD screen
    lcd.setCursor(0, 0);      // set cursor to 1st character on 1st line
    lcd.print("Train ");      // print x on the LCD screen
    lcd.print(train_number);  // print value of train_number on the LCD screen
    lcd.print(" ");           // print " " on the LCD screen
    lcd.setCursor(0, 1);      // set cursor to 1st character on 2nd line
    lcd.print("Active");      // print x on the LCD screen

    station_signal(1);  // set the signal led, green=1 red=0 both=9

    player.volume(20);  // set volume to maximum (0 to 30)
    player.play(0003);  // play the xxxx MP3 file on the SD card
  }


  if (train_loop == 1) {  // if train_loop value is 1 run this

    if (digitalRead(Sensor_before_station) == LOW) {  // check if Sensor_before_station was triggered and then run this code

      at_station = 0;  // set at_station variable to 0

      train_move(160);  // send (x) to train_move function
      delay(1000);      // delay for (x)

      train_move(130);  // send (x) to train_move function
      delay(1000);      // delay for (x)

      train_move(100);  // send (x) to train_move function
      delay(1000);      // delay for (x)

      player.play(0002);  // play the xxxx MP3 file on the SD card
    }


    if (digitalRead(Sensor_at_station) == LOW) {  // check if Sensor_at_station was triggered and then run this code

      at_station = 1;  // set at_station variable to 1

      train_move(0);                           // send (x) to train_move function
      int station_stop = random(3000, 10000);  // random time for the delay between 3 and 10 seconds
      lcd.setCursor(14, 1);                    // set cursor to 15th character on 2nd line
      lcd.print("S");                          // print x on the LCD screen
      lcd.print((station_stop / 1000));        // show delay in seconds
      delay(station_stop);                     // delay for (x)



      player.play(0001);  // Play the xxxx MP3 file on the SD card

      train_move(100);  // send (x) to train_move function
      delay(1000);      // delay for (x)

      train_move(130);  // send (x) to train_move function
      delay(1000);      // delay for (x)

      train_move(160);  // send (x) to train_move function
    }


    if (digitalRead(Sensor_tunnel) == LOW) {  // check if Sensor_tunnel was triggered and then run this code

      tunnel_stop = 1;  // set tunnel_stop variable to 1
      train_move(0);    // send (x) to train_move function

      digitalWrite(red_tunnel, HIGH);   // turn ON/OFF the led
      digitalWrite(green_tunnel, LOW);  // turn ON/OFF the led

      int tunnel_delay = random(0, 10000);  // random time for the delay between 0 and 10 seconds
      lcd.setCursor(14, 1);                 // set cursor to 15th character on 2nd line
      lcd.print("T");                       // print x on the LCD screen
      lcd.print((tunnel_delay / 1000));     // show delay in seconds
      delay(tunnel_delay);                  // delay for (x)

      digitalWrite(red_tunnel, LOW);        // turn ON/OFF the led
      digitalWrite(green_tunnel, HIGH);     // turn ON/OFF the led
      
      tunnel_stop = 0;                      // set tunnel_stop variable to 0
      
      train_move(100);  // send (x) to train_move function
      delay(1000);      // delay for (x)

      train_move(130);  // send (x) to train_move function
      delay(1000);      // delay for (x)

      train_move(160);  // send (x) to train_move function
    }
  }
}


void station_signal(int station_led) {

  if (station_led == 0) {
    digitalWrite(red_led, HIGH);   // turn ON/OFF the led
    digitalWrite(green_led, LOW);  // turn ON/OFF the led
  }
  if (station_led == 1) {
    digitalWrite(red_led, LOW);     // turn ON/OFF the led
    digitalWrite(green_led, HIGH);  // turn ON/OFF the led
  }
  if (station_led == 9) {
    digitalWrite(red_led, HIGH);    // turn ON/OFF the led
    digitalWrite(green_led, HIGH);  // turn ON/OFF the led
  }
}


void train_move(int train_speed) {  // train_move function

  lcd.clear();              // clear LCD screen
  lcd.setCursor(0, 0);      // set cursor to 1st character on 1st line
  lcd.print("Train ");      // print x on the LCD screen
  lcd.print(train_number);  // print value of train_number on the LCD screen
  lcd.print(" ");           // print " " on the LCD screen
  lcd.print(train_speed);   // print value of train_speed on the LCD screen

  lcd.setCursor(0, 1);  // set cursor to 1st character on 2nd line

  if (at_station == 0) {         // if at_station is 0 run this code
    lcd.print("Slowing Down ");  // print x on the LCD screen
  }

  if (at_station == 1) {  // if at_station is 1 run this code

    if (train_speed == 0) {           // if train_speed is 0 run this code
      lcd.print("Stop ");             // print x on the LCD screen
    } else if (train_speed == 160) {  // if the train_speed IS 160
      lcd.print("Full Speed ");       // print x on the LCD screen
    }

    else if ((train_speed != 0 || train_speed != 160)) {  // if train_speed is not 0 or 160 run this code
      lcd.print("Speeding Up ");                          // print x on the LCD screen
    }
  }

  lcd.setCursor(13, 0);   // 14th character on the first LCD line
  lcd.print("ST");        // print x on the LCD screen
  lcd.print(at_station);  // show at_station value

  if ((at_station == 0 && train_speed == 100 && tunnel_stop == 0) || (at_station == 1 && train_speed == 0 && tunnel_stop == 0)) {  // if at_station is 0 and train_speed is 100 and tunnel_stop is 0 OR at_station is 1 and train_speed is 0  and tunnel_stop is 0 run this code
    station_signal(0);                                                                                                             // set the signal led, green=1 red=0 both=9 
  } else {  
    station_signal(1);  // set the signal led, green=1 red=0 both=9
  }

  analogWrite(ENA, train_speed);  // set train speed
  digitalWrite(Motor_1, LOW);     // the train will move
  digitalWrite(Motor_2, HIGH);    // the train will move
}
