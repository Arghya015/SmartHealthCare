// includethe library code:
#include<LiquidCrystal.h>

//initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int degree;                                                        
double realDegree;
String lcdBuffer;

//for social distancing alarm

int triggerPin = 7;
int echoPin = 6;
unsigned long duration;
int distance;
  int rPin =8;
  int gPin =9;
  int pirsenPin =13;
  int motion =0;

void setup() {                                                                                                                                                                                                                                                             
  //set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(A1,INPUT);
  degree = 0;
  realDegree = 0;
  //Printing to LCD
  lcd.print("Temp:");
  lcd.setCursor(0,1);
  lcd.print("O2&BPM:");
  
  //pins for social distancing alarm
  
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(pirsenPin, INPUT);
}

void loop() {
  lcd.print("                   ");
  float volt;
  volt=analogRead(A1)*(5.0/1023.0)*19.68; //for spo2 reading
  degree = analogRead(0);
  realDegree = (double)degree/1024; //for temperature reading
  realDegree *= 5;
  realDegree -= 0.5;
  realDegree *= 100;
  lcd.setCursor(6,0);
  realDegree = (9.0/5)*(realDegree) + 32;
  String output = String(realDegree) + String((char)178) + "F";
  
  //printing temperature and spo2 level to LCD
  lcd.print(output);
  lcd.setCursor(7, 1);
  lcd.print(volt);
  lcd.setCursor(12, 1);
  lcd.print("%");
  lcd.setCursor(14, 1);
  lcd.print(88-(int)(volt/19.68));
  
  //for social distancing alarm
  

  motion = digitalRead(pirsenPin);
  if (motion ==1){
    
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    //cleaning  the trigger
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    
 // capturing the time duration for sound wave to travel in microseconds
    duration = pulseIn(echoPin, HIGH);
    distance = 0.01723 * duration;
    
    if  (motion == 1 && distance <100 ){
      
      
       digitalWrite(rPin, HIGH);
       digitalWrite(gPin, LOW);
       delay(200);
       digitalWrite(rPin, LOW);
      
      
    }
    else {
   
       digitalWrite(rPin, LOW);
       digitalWrite(gPin, HIGH);
      
    }
    
    
    
  }
  }