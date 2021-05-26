#include <Arduino.h>

// Variables will change:
int ledState = HIGH;         // the current state of the output pi
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int rechtsom = 0;
int linksom = 0;
int stopcount = 0;

const int rgbLedPinRed = 47;                         // rgb led red
const int rgbLedPinGreen = 45;                      // rgb led green
const int rgbLedPinBlue = 46;                       // rgb led blue

#define DS1 22
#define DS2 24
#define DS3 26
#define DS4 28
#define DS5 30
#define DS6 32

int bl = 1;
int wh = 0;
int start = 0;

int s1, s2, s3, s4, s5, s6;

void red(){
  digitalWrite(rgbLedPinRed, LOW);
  digitalWrite(rgbLedPinGreen, HIGH);
  digitalWrite(rgbLedPinBlue, HIGH);
}
void green(){
  digitalWrite(rgbLedPinRed, HIGH);
  digitalWrite(rgbLedPinGreen, LOW);
  digitalWrite(rgbLedPinBlue, HIGH);
}
void blue(){
  digitalWrite(rgbLedPinRed, HIGH);
  digitalWrite(rgbLedPinGreen, HIGH);
  digitalWrite(rgbLedPinBlue, LOW);
}

void straight() {
  Serial.println("Driving straight");
  green();
  //Driving forward
  //Motor A forward @ full speed
    digitalWrite(12, HIGH); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B forward @ full speed
    digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 255);    //Spins the motor on Channel B at full speed
    digitalWrite(rgbLedPinGreen, LOW);
}

void right() {
  Serial.println("Gaat naar rechts");
  //Driving right
  //Motor A forward @ full speed forward
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    digitalWrite(12, LOW); //Establishes reverse direction of Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B forward @ full speed backward
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    analogWrite(11, 255);    //Spins the motor on Channel B at full speed backward
}


void left() {
  Serial.println("Gaat naar links");
  //Driving left
  //Motor A forward @ full speed backward
    digitalWrite(12, HIGH); //Establishes  direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed backward

  //Motor B forward @ full speed forward
    digitalWrite(13, LOW);  //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 255);     //Spins the motor on Channel B at full speed forward
}
  


void stop() {
  red();
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
}

//start functie hij begint niet zonder dat dit waar is 
void Start(){
  stop();
  while(start == 0){
s1 = digitalRead(DS1);
s2 = digitalRead(DS2);
s3 = digitalRead(DS3);
s4 = digitalRead(DS4);
s5 = digitalRead(DS5);
s6 = digitalRead(DS6);
    if ((s2 == bl) && (s3 == bl) && (s1 == bl) && (s4 == wh) && (s5 == wh)){
      start = 1;
    }
    else{
     Serial.println("De auto is een imbeciel");
     delay(10);
     
    }
  }
}


void setup() {
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pi
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin

  //Setup sensor
  pinMode(DS1, INPUT);
  pinMode(DS2, INPUT);
  pinMode(DS3, INPUT);
  pinMode(DS4, INPUT);
  pinMode(DS5, INPUT);
  pinMode(DS6, INPUT);
  
  pinMode(rgbLedPinRed, OUTPUT);
  pinMode(rgbLedPinGreen, OUTPUT);
  pinMode(rgbLedPinBlue, OUTPUT);
  
  Serial.begin(9600); //Starts the serial monitor


Start();


}

void loop(){
  // assigns signal 1-6 from digital sensor 1-6
s1 = digitalRead(DS1);
s2 = digitalRead(DS2);
s3 = digitalRead(DS3);
s4 = digitalRead(DS4);
s5 = digitalRead(DS5);
s6 = digitalRead(DS6);

//tijdelijke straight

straight();

 //rechts af
  if (s5 == bl){//rechter sensor 

  delay(5); // delay voor 2e lezing
    s6 = digitalRead(DS6);
    s5 = digitalRead(DS5);
    s4 = digitalRead(DS4);
    s3 = digitalRead(DS3);
    s2 = digitalRead(DS2);
    s1 = digitalRead(DS1);

    //kijken of het alsnog pauze of stop is 
    if(s4 == bl){// hij is nu pauze
    Serial.println("pauze");
      delay(350);
      stop();
      blue();
      delay(5100);
    s6 = digitalRead(DS6);
    s5 = digitalRead(DS5);
    s4 = digitalRead(DS4);
    s3 = digitalRead(DS3);
    s2 = digitalRead(DS2);
    s1 = digitalRead(DS1);
      if((s4 == bl) && (s5 == bl)){
          Serial.println("hij staat nu in zijn stop");
          stopcount = 1;
      }

    }
    //anders is het een bocht
    else{
      s6 = digitalRead(DS6);
    //1e stap hij moet door rijden totdat sensor 6 wit is
      while (s6 == bl){
          s6 = digitalRead(DS6);
          Serial.println("S6 is zwart rechtsom");
      }
       Serial.println("S6 is wit");
        stop();
        delay(200);
        right();
        //vanaf hier moet hij opzoek naar de lijn en kijken of sensor 1 weer zwart word
        s1 = digitalRead(DS1);
        while(s1 == wh){
          s1 = digitalRead(DS1);
          Serial.println("S1 wit"); 
        } 
        Serial.println("S1 zwart");
        stop();
    }
  }
    s6 = digitalRead(DS6);
    s5 = digitalRead(DS5);
    s4 = digitalRead(DS4);
    s3 = digitalRead(DS3);
    s2 = digitalRead(DS2);
    s1 = digitalRead(DS1);

  // linker af
 if (s4 == bl){//rechter sensor
    //1e stap hij moet door rijden totdat sensor 6 wit is
    Serial.println("Ik ben een imbiciel");
    delay(5); // delay voor 2e lezing
    s6 = digitalRead(DS6);
    s5 = digitalRead(DS5);
    s4 = digitalRead(DS4);
    s3 = digitalRead(DS3);
    s2 = digitalRead(DS2);
    s1 = digitalRead(DS1);
    
    //kijken of het alsnog pauze of stop is 
    if(s5 == bl){// hij is nu pauze
      Serial.println("pauze");
      delay(350);
      stop();
      blue();
      delay(5100);
      s6 = digitalRead(DS6);
      s5 = digitalRead(DS5);
      s4 = digitalRead(DS4);
      s3 = digitalRead(DS3);
      s2 = digitalRead(DS2);
      s1 = digitalRead(DS1);
      if((s4 == bl) && (s5 == bl)){
          Serial.println("hij staat nu in zijn stop");
          stopcount = 1;
      }
    }
   else{
    s6 = digitalRead(DS6);
    // hij moet hier nog een check uitvoeren

      while (s6 == bl){
          s6 = digitalRead(DS6);
          Serial.println("S6 is zwart linksom");
      }
      Serial.println("S6 is wit");
      stop();
      delay(200);
      left();
      //vanaf hier zoek hij weer de lijn
      s1 = digitalRead(DS1);
      while(s1 == wh){
        s1 = digitalRead(DS1);
        Serial.println("S1 wit");
      }
      Serial.println("S1 zwart");
      stop();
   }
  }
    s6 = digitalRead(DS6);
    s5 = digitalRead(DS5);
    s4 = digitalRead(DS4);
    s3 = digitalRead(DS3);
    s2 = digitalRead(DS2);
    s1 = digitalRead(DS1);


if(stopcount == 1){
s1 = digitalRead(DS1);
while(s1 == bl){
     digitalWrite(12, HIGH); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 135);   //Spins the motor on Channel A at full speed

  //Motor B forward @ full speed
    digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 135);    //Spins the motor on Channel B at full speed
    s1 = digitalRead(DS1);
}
while (stopcount == 1)
{
  stop();
  Serial.println("hij is aan het einde van het traject");
}
}
    s6 = digitalRead(DS6);
    s5 = digitalRead(DS5);
    s4 = digitalRead(DS4);
    s3 = digitalRead(DS3);
    s2 = digitalRead(DS2);
    s1 = digitalRead(DS1);



 //correctie links

    if(s2 == bl){
      analogWrite(3, 255);     //Spins the motor on Channel A at full speed 
      digitalWrite(12, HIGH);  //Establishes forward direction of Channel A

      analogWrite(11, 20);     //Spins the motor on Channel B at full speed forward
      digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    }

//correctie rechts

    if(s3 == bl){
      analogWrite(3, 20);     //Spins the motor on Channel A at full speed 
      digitalWrite(12, HIGH);  //Establishes forward direction of Channel A
    
      analogWrite(11, 255);     //Spins the motor on Channel B at full speed forward
      digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
      }
}