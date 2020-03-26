#include <LiquidCrystal.h>
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
#include <Keypad.h> //https://playground.arduino.cc/Code/Keypad/
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
 };
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String spd = "";
int Speed;
int j = 13;
int i = 0;


void setup() {
  // put your setup code here, to run once:
  for(int k = 10; k <= 13; k++)
  {
    pinMode(k, OUTPUT);
  }

  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Direction");
  start();
}

void motor_left()
{
  while(1)
  {
    for(int k=13; k>=10; k--)
    {
      digitalWrite(k, HIGH);
      delay(Speed);
      digitalWrite(k, LOW);
    }
  }
}

void motor_right()
{
  while(1)
  {
    for(int k = 10; k <= 13; k++)
    {
      digitalWrite(k, HIGH);
      delay(Speed);
      digitalWrite(k, LOW);
    }
  }
}

void start()
{
  spd = "";
  Speed = 0;
  while(1)
  {
    char key = kpd.getKey();

    if (key != NO_KEY)
    {
      //For left rotation
      if(key == 'A')
      {
        key = NO_KEY;
        while(1)
        {
          lcd.setCursor(12, 0);
          lcd.print("Left");
          delay(500);
          lcd.setCursor(0, 1);
          lcd.print("Speed");
          while(1)
          {
            char key2 = kpd.getKey();
            if(key2 != NO_KEY)
            {
              lcd.setCursor(j, 1);
              lcd.print(key2);
              spd += (char)key2;
              Speed = spd.toInt();
              j++;

              if(key2 == '#')
              {
                key2 = NO_KEY;
                motor_right();
              }
            }
          }
        }
      }
    }
  }
}
