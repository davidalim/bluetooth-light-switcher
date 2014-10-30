/*
Bluetooth-controlled Light Switcher
4/6/14

David Lim

Control any light switch from your Android device

Two servos are used to turn the light on/off
LED used to indicate signal recieved

*/

#include <Servo.h>

// Create servo objects
Servo myservo;  
Servo myservo2;

int ledPin = 13;   // Use the built in LED pin 13 of the Uno
int state = 0;     // Data recieved from Bluetooth
int pos = 0;       // variable to store the servo position 
boolean lightOn = false;

void setup() {

  // Attach servos to pins 9 and 10
  myservo.attach(10); 
  myservo2.attach(9); 

  // Set the pins as outputs:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Set servos to initial angles
  myservo2.write(30);
  myservo.write(170); 

  Serial.begin(9600); // Default connection rate for my BT module
}

void loop() {
  
  // Bluetooth
  // If some data is sent, read it and save it in the state variable
  if(Serial.available() > 0){
    state = Serial.read();
  }
  
  // State 0: turn light off
  if (state == '0') {    
      
    // Blink LED
    digitalWrite(ledPin, HIGH);
    delay(35);
    digitalWrite(ledPin, LOW);
      
    if(lightOn){

      // Moves the servo up to flip switch, then back down
      // Servo moves 1 degree at a time, every 15ms
      for(pos = 30; pos < 170; pos += 1)   
      {                                  
        myservo2.write(pos);            
        delay(15);                      
      } 
      for(pos = 170; pos>=30; pos-=1)     
      {                                
        myservo2.write(pos);              
        delay(15);                        
      } 
            
      Serial.println("Light: OFF");
      lightOn = true;
    }

  }
  
  // State 1: turn light on
  else if (state == '1') {
        
    // Blink LED
    digitalWrite(ledPin, HIGH);
    delay(35);
    digitalWrite(ledPin, LOW);
      
    if(!lightOn){    

      // Moves the servo up to flip switch, then back down
      // Servo moves 1 degree at a time, every 15ms
      for(pos = 170; pos >= 30; pos -= 1)
      {                                
        myservo.write(pos);              
        delay(15);                       
      }
      for(pos = 30; pos <= 170; pos += 1)
      {                                  
        myservo.write(pos);              
        delay(15);                       
      } 
      
       Serial.println("Light: ON");
      lightOn = false; 
    }
    
  }

}
