#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>



LiquidCrystal_I2C lcd(0x27, 20, 4);
int buttonStateY = 0;
int buttonStateN = 0;
const int buttonPinY = 8;
const int buttonPinN = 7;
#define echoPin 3
#define trigPin 2
#define redPin 13
#define greenPin 12
long duration;
int distance;

void setup() {
 pinMode(redPin, OUTPUT);
 pinMode(greenPin, OUTPUT); 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 lcd.init();
 pinMode(buttonPinY, INPUT);
 pinMode(buttonPinN, INPUT);
 Serial.begin(9600);
 lcd.setCursor(0, 0);
 lcd.backlight();
}

void loop() {
   
  initialization();

  letsbegin();
 
  waituserchoice();

  nextguestion("Do you have", "any difficulty", "breathing?","");
  
  waituserchoice();
  
  if (buttonStateY == HIGH) {  //problem with breathing
    giveanswer("You should look", "for medical", "assistance!"); 
    digitalWrite(redPin, HIGH);  
  }
  else {  ////ok with breathing
    nextguestion("Do you feel", "like you have", "high body", "temperature?");
    waituserchoice();
    if (buttonStateY == HIGH) {
      nextguestion("Do you have", "cough?", "", "");
      waituserchoice();
      cough (); 
  }
  else { //low temperature
    nextguestion("Do you have", "cough?", "", "");
    waituserchoice();
    if (buttonStateY == HIGH) { //have cough
      nextguestion("Are you feeling", "tired?", "", "");
      waituserchoice();
      tired (); 
    }
    else { //don't have cough
      nextguestion("Are you feelling", "tired?", "", "");
      waituserchoice();
      if (buttonStateY == HIGH) { //tired
        nextguestion("Do you feel", "a sore throat?", "", "");
        waituserchoice(); 
        sorethroat1(); }
       else { //not tired
        nextguestion("Do you feel", "a sore throat?", "", "");
        waituserchoice(); 
        sorethroat2();
      }}}}
      delay(1000);
      lcd.clear();
      lcd.setCursor(2, 1);
      lcd.print("Thank you"); 
      delay(2000);
      }

void nextguestion(String msg1, String msg2, String msg3, String msg4){
    buttonStateY = LOW;
    buttonStateN = LOW;
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Ok, please answer");
    delay(3000);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print(msg1);
    lcd.setCursor(2, 1);
    lcd.print(msg2);
    lcd.setCursor(2, 2);
    lcd.print(msg3);
    lcd.setCursor(2, 3);
    lcd.print(msg4);
    do {
    delay(1);
    buttonStateY = digitalRead(buttonPinY);
    buttonStateN = digitalRead(buttonPinN);
    }
   while (buttonStateY == LOW && buttonStateN == LOW);
    buttonStateY = LOW;
    buttonStateN = LOW;
}

void giveanswer(String msg1, String msg2, String msg3){
    buttonStateY = LOW;
    buttonStateN = LOW;
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print(msg1);
    lcd.setCursor(2, 2);
    lcd.print(msg2);
    lcd.setCursor(2, 3);
    lcd.print(msg3);
    delay(4000);  
}

void waituserchoice(){
  do {
    delay(1);
    buttonStateY = digitalRead(buttonPinY);
    buttonStateN = digitalRead(buttonPinN);
  }
  while (buttonStateY == LOW && buttonStateN == LOW); 
    }

void initialization(){
 digitalWrite(redPin, LOW);
 digitalWrite(greenPin, LOW);
 do {
  lcd.clear();
  delay(1);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  Serial.println("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  }
 while (distance > 30);
 if (distance <= 30) {
  digitalWrite(greenPin, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--------------------");
  lcd.setCursor(7, 1);
  lcd.print("RoboDoc");
  delay(100);
  lcd.setCursor(7, 2);
  lcd.print("Welcome");
  lcd.setCursor(0, 3);
  lcd.print("--------------------"); 
  delay(2000);}
}

void letsbegin(){
 lcd.clear();
 lcd.setCursor(1, 1);
 lcd.print("Left button for Yes");
 lcd.setCursor(1, 2);
 lcd.print("Right button for No");
 delay(4000);
 lcd.clear();
 lcd.setCursor(2, 1);
 lcd.print("Ok, let us begin");
 lcd.setCursor(2, 2);
 lcd.print("Press to start");
 delay(3000);
}

void cough(){
  
  if (buttonStateY == HIGH) {
    giveanswer("You should look", "for medical", "assistance!");
    digitalWrite(redPin, HIGH);  
  }
  else {
    nextguestion("Are you feel", "tired?", "", "");
    waituserchoice();
    if (buttonStateY == HIGH) {
         giveanswer("You should look", "for medical", "assistance!"); 
         digitalWrite(redPin, HIGH); 
       }
    else {
    nextguestion("Do you have", "a sore throat?", "", "");
    waituserchoice();
    if (buttonStateY == HIGH) {
         giveanswer("You should look", "for medical", "assistance!"); 
         digitalWrite(redPin, HIGH); 
        }
     else {
      nextguestion("Dou you have", "decreaced sense", "of smell?", "");
      waituserchoice();
      if (buttonStateY == HIGH) {
         giveanswer("You should look", "for medical", "assistance!"); 
         digitalWrite(redPin, HIGH); 
       }
      else {
        giveanswer("You don't have", "covid. Attend", "your fever");
      
       }}}}}

void sorethroat1(){
   if (buttonStateY == HIGH) {
     giveanswer("You should look", "for medical", "assistance!"); 
     digitalWrite(redPin, HIGH);  
  }
  else {
      nextguestion("Do you have", "decreaced sense", "of smell?", "");
      waituserchoice();
      if (buttonStateY == HIGH) {
         giveanswer("You should look", "for medical", "assistance!"); 
         digitalWrite(redPin, HIGH); 
       }
      else {
        giveanswer("Possible" , "covid symptom", "Be careful");
      
       }}}
        
        
void sorethroat2(){
   if (buttonStateY == HIGH) {
     nextguestion("Do you have", "decreaced sense", "of smell?", "");
     waituserchoice();
     if (buttonStateY == HIGH) {
         giveanswer("You should look", "for medical", "assistance!"); 
         digitalWrite(redPin, HIGH); 
       }
      else {
        giveanswer("Possible" , "covid symptom", "Be careful");
  }}
  else {
      nextguestion("Do you have", "decreaced sense", "of smell?", "");
      waituserchoice();
      if (buttonStateY == HIGH) {
         giveanswer("Possible" , "covid symptom", "Be careful");
       }
      else {
        giveanswer("You don't" , "have", "anything");
      }}}

void tired (){
  if (buttonStateY == HIGH) {
     giveanswer("You should look", "for medical", "assistance!");  
     digitalWrite(redPin, HIGH); }
  else {
     nextguestion("Do you feel", "a sore throat?", "", "");
     waituserchoice();
     sorethroat1();
  }
  }
