/*
 *  Stargate
 * 
 */

#include <TimerOne.h>

#define EN 8/* Enable pin for all stepper outputs */
#define X_DIR 5/* Direction-Pin for X-axis */
#define X_STEP 2/* Step-Pin for X-axis */

int Count = 0; /* Counter to count number of steps made */
boolean Direction = LOW; /* Rotational direction of stepper motors*/

int incomingByte = 0;

boolean stop = false;

void setup(){
  Serial.begin(9600);


pinMode(EN, OUTPUT);
pinMode(X_DIR, OUTPUT);
pinMode(X_STEP, OUTPUT);

digitalWrite(EN, LOW); //Low to enable

 
}

void loop(){

  if (Serial.available() > 0) {

    incomingByte = Serial.read();

    Serial.print("I received: ");
    Serial.println(incomingByte);
    Serial.println(incomingByte, DEC);
    if ( incomingByte == 97) {
      Serial.println("a");
      Direction = LOW;    
    }
    if ( incomingByte == 122) {
      Serial.println("z");
      Direction = HIGH;
    }

    if ( incomingByte == 101) {
      Serial.println("e");
       Direction = LOW; 
      stop = !stop;
    }

    if ( incomingByte == 114) {
      Serial.println("r");
      Direction = HIGH;
      stop = !stop;
    }
      
  }
    
  Count++;
  
  if (Count >= 100){
    
    digitalWrite(X_DIR, Direction); // Low = CW
  
    Count = 0;
    stop = true;
  }

  
  if (stop) {
    // Stop
    digitalWrite(X_STEP, LOW);
    delay(1);
    digitalWrite(X_STEP, LOW);
    delay(1);  
  } else {
    // Rotate
    digitalWrite(X_STEP, HIGH);
    delay(1);
    digitalWrite(X_STEP, LOW);
    delay(1);
    }
  

} 
