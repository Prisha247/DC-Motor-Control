//I have added the possibilities of testing
//The values of analogRead could be changed for trouble shooting

//including the libraries
//Include requisite libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

//defining pins and variables

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor1 = AFMS.getMotor(3);
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);

#define lefts A1
#define rights A0

void setup() {
  //setting the speed of motors
  AFMS.begin();
  motor1->setSpeed(30);
  motor2->setSpeed(30);
  //declaring pin types
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
  //begin serial communication
  Serial.begin(9600);
  
}

void loop(){
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(lefts));
  Serial.println(analogRead(rights));
  //line detected by both
  if(analogRead(lefts)<=400 && analogRead(rights)<=400){
    //stop
    motor1->run(RELEASE);
    motor2->run(RELEASE);
  }
  //line detected by left sensor
  else if(analogRead(lefts)<=400 && !analogRead(rights)<=400){
    //turn left
    motor1->run(BACKWARD);
    motor2->run(FORWARD);
    /*
    motor1->run(RELEASE);
    motor2->run(FORWARD);
     */
  }
  //line detected by right sensor
  else if(!analogRead(lefts)<=400 && analogRead(rights)<=400){
    //turn right
    motor1->run(FORWARD);
    motor2->run(BACKWARD);
    /*
    motor1->run(FORWARD);
    motor2->run(RELEASE);
     */
  }
  //line detected by none
  else if(!analogRead(lefts)<=400 && !analogRead(rights)<=400){
    //stop
    motor1->run(FORWARD);
    motor2->run(FORWARD);
    /*
    motor1->run(BACKWARD);
    motor2->run(BACKWARD);
     */
  }
  
}
