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

//motor speeds
int leftMotorSpeed = 35;
int rightMotorSpeed = 35;
int run_time;

//The point at which the sensor knows it is LEAVING the line
int leftSensorThreshold = 200;
int rightSensorThreshold = 200;

//The point at which the sensor knows it HAS LEFT the line
int leftSensorLow = 50;
int rightSensorLow = 50;
          
void setup() {
  //setting the speed of motors
  AFMS.begin();
  motor1->setSpeed(leftMotorSpeed);
  motor2->setSpeed(rightMotorSpeed);
  //declaring pin types
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
  
  //begin serial communication
  Serial.begin(9600);  
}

void loop(){

// SERIAL PROTOCOL:
// Format -> [num_value];
// Serial input changes the speed of the motors
run_time = millis();

//  if (Serial.available()>0)
//    {
//      int speed = Serial.parseInt();
//      Serial.println(speed);
//      if (speed >= 0 && speed <= 255)
//      {
//        motor1->setSpeed(speed);
//        motor2->setSpeed(speed);
//      }
//    }


   //Read IR sensors
  int l = analogRead(lefts);
  int r = analogRead(rights);
  
  //line detected by both
//  if(l > leftSensorThreshold && r > rightSensorThreshold){
//    //spin
//    motor1->run(FORWARD);
//    motor2->run(FORWARD);
//  //printing values of the sensors to the serial monitor
//    Serial.print(analogRead(lefts));
//    Serial.print(",");
//    Serial.print(analogRead(rights));
//    Serial.print(leftMotorSpeed);
//    Serial.print(",");
//    Serial.print(rightMotorSpeed);
//    Serial.print(",");
//    Serial.println(run_time);
//  }
  
  //line detected by left sensor
  if(r < rightSensorThreshold && l > leftSensorLow && l < leftSensorThreshold){
    //turn left
    motor1->run(BACKWARD);
    motor2->run(FORWARD);
  //printing values of the sensors to the serial monitor
    Serial.print(analogRead(lefts));
    Serial.print(",");
    Serial.print(analogRead(rights));
    Serial.print(",");
    Serial.print(-1*leftMotorSpeed);
    Serial.print(",");
    Serial.print(rightMotorSpeed);
    Serial.print(",");
    Serial.println(run_time);
  }
  
  //line detected by right sensor
  else if(l < leftSensorThreshold && r > rightSensorLow && r < rightSensorThreshold){
    //turn right
    motor1->run(FORWARD);
    motor2->run(BACKWARD);
  //printing values of the sensors to the serial monitor
    Serial.print(analogRead(lefts));
    Serial.print(",");
    Serial.print(analogRead(rights));
    Serial.print(",");
    Serial.print(leftMotorSpeed);
    Serial.print(",");
    Serial.print(-1*rightMotorSpeed);
    Serial.print(",");
    Serial.println(run_time);
  }
  
  //line detected by none
  else if(l < leftSensorThreshold && r < rightSensorThreshold){
    //stop
    motor1->run(FORWARD);
    motor2->run(FORWARD);
  //printing values of the sensors to the serial monitor
    Serial.print(analogRead(lefts));
    Serial.print(",");
    Serial.print(analogRead(rights));
    Serial.print(",");
    Serial.print(leftMotorSpeed);
    Serial.print(",");
    Serial.print(rightMotorSpeed);
    Serial.print(",");
    Serial.println(run_time);
  }
}
