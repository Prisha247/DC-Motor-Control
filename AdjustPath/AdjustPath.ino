////  CODE TO TURN WHEELS TO CORRECT AFTER HITTING TAPE  //

#include <Adafruit_MotorShield.h>
#include <stdio.h>
#include <stdlib.h>

int VSensorL = A0;
int VSensorR = A1;
char outString;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);
// You can also make another motor on port M2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);



void setup()  {
  Serial.begin(9600);
  AFMS.begin();


  int MotorSpeed = 75;
  int CorrectionSpeed = 15;
  
  leftMotor->setSpeed(MotorSpeed);
  rightMotor->setSpeed(MotorSpeed);
  
//  void VSensorR
//  void VSensorL
  int VTapeMin = 0.1;

  pinMode(VSensorL, INPUT);
  pinMode(VSensorR, INPUT);
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");


//
//  leftMotor->setSpeed(MotorSpeed);
//  rightMotor->setSpeed(MotorSpeed);

//  void VSensorR;
//  void VSensorL;

  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(40);
  rightMotor->setSpeed(40);
  leftMotor->run(BACKWARD);
  rightMotor->run(BACKWARD);
  // turn on motor
  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}

void loop() {  
  //if car has drifted right, first back it up, then move forward by correcting the direction by increasing the speed of the left motor and then return to the original motor speed and move forward
  int VTapeMin = 0.1;
  int MotorSpeed = -30;
  int CorrectionSpeed = 15;
  
  if (VSensorR > VTapeMin) {
    leftMotor->setSpeed(-1*MotorSpeed);
    RightMotor->setSpeed(-1*MotorSpeed);
    delay(5);
    leftMotor->setSpeed(MotorSpeed + CorrectionSpeed);
    delay(5);
    leftMotor->setSpeed(MotorSpeed - CorrectionSpeed);
  }
  //if car has drifted left, first back it up, then move forward by correcting the direction by increasing the speed of the right motor and then return to the original motor speed and move forward
    if (VSensorL > VTapeMin) {
    leftMotor->setSpeed(-1*MotorSpeed);
    RightMotor->setSpeed(-1*MotorSpeed);
    rightMotor->setSpeed(MotorSpeed + CorrectionSpeed);
    delay(5);
    rightMotor->setSpeed(MotorSpeed - CorrectionSpeed);
  }
}
