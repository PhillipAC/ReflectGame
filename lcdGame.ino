#include <LiquidCrystal_I2C.h>

#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int rightButton = LOW;
int leftButton = LOW;
unsigned long startTime = millis();
int LEFT = 8;
int RIGHT = 7;
int STATE = 0; // 0 - into, 1 - awaing play, 2 - intro, 3 - playing , 4 - Done

void updateScreen(const String &top, const String &button);
void intro();
void start();
void playing();

void setup() {
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  checkInput();
  if(STATE == 0)
  {
    intro();
  }
  else if(STATE == 1)
  {
    awaiting();
  }
  else if(STATE == 2)
  {
    start();
  }
  else
  {
    playing();
  }
}

void checkInput()
{
  rightButton = digitalRead(RIGHT);
  leftButton = digitalRead(LEFT);
}

void intro()
{
  updateScreen("Press left", "to play!");
  STATE = 1;
}

void awaiting()
{
  if(leftButton == HIGH)
  {
    STATE = 2;
  }
}

void start()
{
  updateScreen("Get Ready","");
  delay(1000);
  updateScreen("3...","");
  delay(1000);
  updateScreen("2...","");
  delay(1000);
  updateScreen("1...","");
  delay(1000);
  updateScreen("WAIT!!!!!", "");
  delay(random(1000,3000));
  updateScreen("PRESS RIGHT!", "");
  startTime = millis();
  STATE = 3;
}

void playing()
{
   if(rightButton == HIGH)
   {
    unsigned long clickTime = millis();
    unsigned long elaspedTime = clickTime - startTime;
    updateScreen("Time: " + String(elaspedTime / 1000.0), "");
    STATE = 1;
   }
}

void updateScreen(const String &top, const String &button)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(top);
    lcd.setCursor(0,1);
    lcd.print(button);
}