#include <Arduino.h>


int DS1=30;  
int DS1value = 0;  

void setup() {
  pinMode(DS1,INPUT);

  Serial.begin(9600); 
}

void loop(){
DS1value = digitalRead(DS1);  

 Serial.println(DS1value); 
 
 delay(1000);
}