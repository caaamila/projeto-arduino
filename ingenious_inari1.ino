#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

#define NOTE_C4 262
#define NOTE_G3 196
#define NOTE_A4 440

int melody[] = { NOTE_C4, NOTE_G3, NOTE_A4 };
int noteDurations[] = { 4, 4, 4 };
int count = 5; 

int led1 = 13;  
int led2 = 12;  

Servo servo_9, servo_10;

Adafruit_LiquidCrystal lcd_1(0);

void setup() {
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.print("Bem-vindo a");        
  lcd_1.setCursor(0, 1);
  lcd_1.print("Padaria");            
  delay(2000);                         
  lcd_1.clear();

  lcd_1.print("Paes disponiveis: ");
  lcd_1.setCursor(0, 1);
  lcd_1.print(count);
  
  servo_9.attach(9);
  servo_10.attach(10);

  pinMode(2, INPUT_PULLUP);            
  pinMode(3, INPUT_PULLUP);          
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  if (digitalRead(2) == LOW && count > 0) {
    Serial.println("Cliente entrou");
    while (digitalRead(2) == LOW);
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    delay(500);

    tone(8, melody[0], 300);           
    servo_9.write(180);                
    delay(1000);
    servo_9.write(90);
    count--;                           
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Paes disponiveis:");
    lcd_1.setCursor(0, 1);
    lcd_1.print(count);
    delay(500);

    if (count == 1) {
      lcd_1.clear();
      lcd_1.print("Atenção: Stock");
      lcd_1.setCursor(0, 1);
      lcd_1.print("baixo!");
      tone(8, melody[2], 1000);      
      delay(1000);
      lcd_1.clear();
      lcd_1.setCursor(0, 0);
      lcd_1.print("Paes disponiveis:");
      lcd_1.setCursor(0, 1);
      lcd_1.print(count);
    }
  }

  if (digitalRead(3) == LOW && count > 0) {
    Serial.println("Pão vendido");
    while (digitalRead(3) == LOW);
    digitalWrite(led1, HIGH);        
    delay(500);
    digitalWrite(led1, LOW);
    delay(500);

    tone(8, melody[1], 300);          
    servo_10.write(180);              
    delay(1000);
    servo_10.write(90);
    lcd_1.clear();
    lcd_1.print("Paes disponiveis:");
    lcd_1.setCursor(0, 1);
    lcd_1.print(count);
  }

  if (count == 0) {
    Serial.println("Acabou o stock!");
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Padaria:");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Esgotado!");

    digitalWrite(led2, HIGH);         
    for (int i = 0; i < 3; i++) {    
      tone(8, melody[2], 800);
      delay(800);
      noTone(8);
      delay(300);
    }
    delay(2000);
    digitalWrite(led2, LOW);
   // count++;
  }
}
