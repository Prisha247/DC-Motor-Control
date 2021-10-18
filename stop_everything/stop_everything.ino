#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);

void setup()  {
  Serial.begin(9600);
  AFMS.begin();

}

void loop() {
  leftMotor->setSpeed(0);
  rightMotor->setSpeed(0);

//  leftMotor->run(BACKWARD);
//  rightMotor->run(BACKWARD);
//
//  leftMotor->setSpeed(150);
//  rightMotor->setSpeed(150);
}
