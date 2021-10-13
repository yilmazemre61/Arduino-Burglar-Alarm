// C++ Code
// Emre YILMAZ
// Final Project
// 15.08.2021


#include <LiquidCrystal.h>
// Initialise the Serial LCD
LiquidCrystal lcd(10,9,8,7,6,5);

// Pins
int trigPin = 12;
int echoPin = 11;
int redLed = 4;
int blueLed = 3;
int piezoPin = 13;

// Distance 
int normalDistance = 200;
boolean triggered = false;
// Passwords
// To deactivate the alarm
String password1 = "12345";
String password2;
String password3;
// To silence the alarm
String password4 = "678";

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2); // Initialise the LCD
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  
  long duration, distance;
  
  digitalWrite(redLed, HIGH);
  digitalWrite(blueLed, HIGH);
  
  digitalWrite(piezoPin, HIGH);
  digitalWrite(redLed, LOW);
  digitalWrite(blueLed, LOW);
  digitalWrite(piezoPin, LOW);
}

void loop(){
  
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Alarm is Active");
  delay(500);

  if(triggered){
    for(int i=0; i<1; i++){
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Password");
      Serial.println("Password: ");
      while(Serial.available() == 0){
        delay(5000); // waits 5 sec to enter the first password
        break;
      }
      password2 = Serial.readString(); // reads the password from the Serial Monitor
      if(password1 == password2){ // checks the password
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("Alarm");
        lcd.setCursor(0,1);
        lcd.print("Deactivated");
        delay(1000); 
        triggered = false;
        break;
      }
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Alarm is ON");
      delay(500);
      digitalWrite(redLed, HIGH);
      tone(piezoPin, 635);
      delay(500);
      digitalWrite(blueLed, HIGH);
      tone(piezoPin, 912);
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Reset the Alarm");
      Serial.println("Deactivated Password : ");
      while(Serial.available() == 0){
        delay(5000); // waits 5 sec to enter the second password
        break;
      }
      password3 = Serial.readString(); // reads the password from the Serial Monitor
      if(password3 == password4){ // checks the password
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("Alarm is");
        lcd.setCursor(0,1);
        lcd.print("Deactivated");
        delay(1000); 
        digitalWrite(redLed, LOW);
        digitalWrite(blueLed, LOW);
        noTone(piezoPin);
        delay(500);
        triggered = false;
        break;
      }
    }
  }else{
    delay(3000);
    // sets the distance 
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delay(2);
    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;
    if(distance < normalDistance){ // checks the distance 
      Serial.println(distance);
      triggered = true; 
    }
    delay(20);
  }

}



   