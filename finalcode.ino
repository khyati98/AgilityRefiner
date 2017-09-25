#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sensorPin = A0; // select the input pin for ldr
int sv = 0;  //for ldr
int flag = 0;
int val = 0;  //read from push button
int pushbutton1 = 7;
int pushbutton2 = 8 ;
int ledpin1 = 13;
int ledpin2 = 10;
unsigned long t_time = 0, s_time, e_time, r_time;
int rounds = 0, Random = 0;                            
unsigned long TimeinEach(int pushbutton, int led)
{ s_time = millis();
  flag = 0;
  val = digitalRead(pushbutton);
  while (val != LOW)
  {
    val = digitalRead(pushbutton);
  }
  if (val == LOW)
  { digitalWrite(led, LOW);
    flag = 1;                    //push button is pressed
    sv = analogRead(sensorPin);
    lcd.clear();
  }
  while (sv > 100 && flag == 1) //getting back to lcd screen
  {
    digitalWrite(led, LOW);
    sv = analogRead(sensorPin);
  }

  e_time = millis();
  r_time = e_time - s_time;
  lcd.print(r_time/1000.0);
  return r_time;            //time talen in each round
}
void setup() {
  pinMode(pushbutton1, INPUT);
  pinMode(pushbutton2, INPUT);
  pinMode(ledpin1, OUTPUT);                      //digital inputs are to be defined not ldr one
  pinMode(ledpin2, OUTPUT);
  lcd.begin(16, 2);
  randomSeed(analogRead(A0));
  Serial.begin(115200); //sets serial port for communication
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("let's begin!!!");
  Serial.println("let's begin!!!");
  delay(2000);

  lcd.clear();
  while (rounds < 10)
  {
    Random = random(1, 3); //generates 1 or 2
    if (Random == 1)
    {
      digitalWrite(ledpin1, HIGH);
      lcd.print(rounds + 1);
      t_time += TimeinEach(pushbutton1, ledpin1);
      delay(1000);
      lcd.clear();
      rounds++;
    }
    else
    { digitalWrite(ledpin2, HIGH);
      lcd.print(rounds + 1);
      t_time += TimeinEach(pushbutton2, ledpin2);
      delay(1000);
      lcd.clear();
      rounds++;

    }
  }
  lcd.print("You did it!!!");
  delay(1000);
  lcd.clear();
  lcd.print("your average");
  delay(1000);
  lcd.clear();
  lcd.print(t_time / 10000.0);  //average over 10 rounds
  lcd.print(" s");
  delay(1000);
  lcd.clear();
  delay(1000);
  lcd.print("ALL THE BEST");
  delay(2000);
}

