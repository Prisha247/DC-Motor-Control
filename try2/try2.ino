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

//The point at which the sensor knows it is LEAVING the line
int leftSensorThreshold = 200;
int rightSensorThreshold = 200;

//The point at which the sensor knows it HAS LEFT the line
int leftSensorLow = 50;
int rightSensorLow = 50;

void setup() {
  //setting the speed of motors
  AFMS.begin();
  motor1->setSpeed(35);
  motor2->setSpeed(35);
  //declaring pin types
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
  //begin serial communication
  Serial.begin(9600);
  
}

void loop(){
  //printing values of the sensors to the serial monitor
  Serial.print(analogRead(lefts));
  Serial.print(",");
  Serial.println(analogRead(rights));

   //Read IR sensors
  int l = analogRead(lefts);
  int r = analogRead(rights);
  
  //line detected by both
//  if(l > leftSensorThreshold && r > rightSensorThreshold){
//    //spin
//    motor1->run(FORWARD);
//    motor2->run(FORWARD);
//  }
  
  //line detected by left sensor
  if(r < rightSensorThreshold && l > leftSensorLow && l < leftSensorThreshold){
    //turn left
    motor1->run(BACKWARD);
    motor2->run(FORWARD);
    /*
    motor1->run(RELEASE);
    motor2->run(FORWARD);
     */
  }
  //line detected by right sensor
  else if(l < leftSensorThreshold && r > rightSensorLow && r < rightSensorThreshold){
    //turn right
    motor1->run(FORWARD);
    motor2->run(BACKWARD);
    /*
    motor1->run(FORWARD);
    motor2->run(RELEASE);
     */
  }
  //line detected by none
  else if(l < leftSensorThreshold && r < rightSensorThreshold){
    //stop
    motor1->run(FORWARD);
    motor2->run(FORWARD);
    /*
    motor1->run(BACKWARD);
    motor2->run(BACKWARD);
     */
  }
  
}
