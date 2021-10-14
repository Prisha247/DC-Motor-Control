//  CODE TO TURN WHEELS TO CORRECT AFTER HITTING TAPE  //

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

int MotorSpeed = 75
int CorrectionSpeed = 15

leftMotor->setSpeed(MotorSpeed);
rightMotor->setSpeed(MotorSpeed);


void setup()  {
  Serial.begin(9600);
  AFMS.begin();
}


void VSensorR
void VSensorL
int VTapeMin = 0.1

void loop() {  
  if VSensorR > VtapeMin {
    leftMotor->setSpeed(MotorSpeed + CorrectionSpeed)
    delay(5)
    leftMotor->setSpeed(MotorSpeed - CorrectionSpeed)
  }
    if VSensorL > VtapeMin {
    rightMotor->setSpeed(MotorSpeed + CorrectionSpeed)
    delay(5)
    rightMotor->setSpeed(MotorSpeed - CorrectionSpeed)
  }
}
