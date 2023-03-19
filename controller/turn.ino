#include <Servo.h>

Servo servo1;
int posn = 90;

void setup() {
  Serial.begin(9600);
  servo1.attach (8);      // attaches the servo on pin 9 to the servo object
  rotate();
  servo1.write(posn);
}

void rotate()
{
  for (posn = 0; posn < 180; posn += 1)            // goes from 0 degrees to 180 degrees
 {                                                                       // in steps of 1 degree
    servo1.write (posn);                                                 // tell servo to go to position in variable 'pos'
    delay (10);                                       // waits 10ms for the servo to reach the position
  }
  for (posn = 180; posn>=1; posn-=1)                // goes from 180 degrees to 0 degrees                                                                                 // in steps of 1 degree
{                               
    servo1.write (posn);                                                  // tell servo to go to position in variable 'pos'
    delay (10);                                        // waits 10ms for the servo to reach the position
  }

}

void turn_left(){
  if(posn < 170){
    posn += 10;
    servo1.write(posn);
  }
}

void turn_right(){
    if(posn > 10){
    posn -= 10;
    servo1.write(posn);
  }
}


void loop() {
  
  Serial.println("turn to?\n");
  while (Serial.available() == 0) {}  //wait for data available
    //String teststr = Serial.readString();  //read until timeout
    //teststr.trim();
    int incoming = Serial.read();
    if (incoming == 'r') {
      Serial.println("turn right\n");
      turn_right();    
    } else if (incoming == 'l'){
      Serial.println("turn left\n");
      turn_left();
    } else {
      Serial.println("something else\n");
    }
}
