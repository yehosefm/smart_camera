#include <Servo.h>

Servo servo1;
int posn = 90;

void setup() {
  Serial.begin(9600);
  servo1.attach (9);
  //rotate();
  servo1.write(posn);
}

void rotate()
{
  for (posn = 0; posn < 180; posn += 1) 
 {                      
    servo1.write (posn);  
    delay (100);      
  }
  for (posn = 180; posn>=1; posn-=1)
{                               
    servo1.write (posn);
    delay (100);
  }

}

void turn_left(){
  for(int i=0; i < 15; i++){
    if(posn >= 180){
      break;
    }
    posn ++;
    servo1.write(posn);
    delay(100);
  }
}

void turn_right(){
  for(int i=0; i < 15; i++){
    if(posn <= 0){
      break;
    }
    posn --;
    servo1.write(posn);
    delay(100);
  }
}


void loop() {
  Serial.println("available");
  while (Serial.available() == 0) {}  //wait for data available
    String teststr = Serial.readString();  //read until timeout
    teststr.trim();
    //int incoming = Serial.read();
    if (teststr == "r") {
      Serial.println("turn right\n");
      turn_right();    
    } else if (teststr == "l"){
      Serial.println("turn left\n");
      turn_left();
    } else {
      Serial.println(teststr);
      Serial.println("something else %s\n");

    }
}
