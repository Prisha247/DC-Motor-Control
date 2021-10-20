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

//motor speeds
int leftMotorSpeed = 35;
int rightMotorSpeed = 35;

//The point at which the sensor knows it is LEAVING the line
int leftSensorThreshold = 200;
int rightSensorThreshold = 200;

//The point at which the sensor knows it HAS LEFT the line
int leftSensorLow = 50;
int rightSensorLow = 50;

// SERIAL PROTOCOL:
// Format -> [cmd_char][num_value];
// char 'a' means set a new left motor speed
// char 'b' means set a new right motor speed
// char 'l' means set a new left IR threshold value
// char 'r' means set a new right IR threshold value
// 'x' means start streaming IR values
// 'y' means stop streaming IR values

// Serial control variables
char rx_byte;
String rx_string = "";
bool receiving_val = false;
char last_cmd_received;
String all_cmds = "ablrxy";
bool streaming = false;
bool plotStreaming = false;

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
  update_rx();
  
  //printing values of the sensors to the serial monitor
//  Serial.print(analogRead(lefts));
//  Serial.print(",");
//  Serial.print(analogRead(rights));
//  Serial.print(",");
//  Serial.println(analogRead(rightMotorSpeed));

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

void update_rx() {

  // While there character available to read
  while (Serial.available()) {
    rx_byte = Serial.read();

    // Check for a valid command
    if (!receiving_val) {
      if (all_cmds.indexOf(rx_byte) > -1) {
        last_cmd_received = rx_byte;
        rx_string = "";
        receiving_val = true;
      }
    } 
    // If the command is complete, start processing
    else if (rx_byte == ';') {
      receiving_val = false;

      // Call the respective method based on the command
      switch (last_cmd_received) {
        case 'a':
          set_left_motor_speed();
          break;
        case 'b':
          set_right_motor_speed();
          break;
        case 'l':
          set_left_threshold();
          break;
        case 'r':
          set_right_threshold();
          break;
        case 'x':
          stream_start();
          break;
        case 'y':
          stream_stop();
          break;
      }
    } 

    // If a number is typed, store it
    else if (isdigit(rx_byte)) {
      rx_string += rx_byte;
    }
  }
}

// Set the speed of the left motor
void set_left_motor_speed() {
  leftMotorSpeed = rx_string.toInt();
  Serial.print("Left motor speed set to ");
  Serial.println(leftMotorSpeed);
  return;
}

// Set the speed of the right motor
void set_right_motor_speed() {
  rightMotorSpeed = rx_string.toInt();
  Serial.print("Right motor speed set to ");
  Serial.println(rightMotorSpeed);
  return;
}

// Set the left IR threshold value
void set_left_threshold() {
  leftSensorThreshold = rx_string.toInt();
  Serial.print("Left IR threshold value set to ");
  Serial.println(leftSensorThreshold);
  return;
}


// Set the right IR cutoff value
void set_right_threshold() {
  rightSensorThreshold = rx_string.toInt();
  Serial.print("Right IR threshold value set to ");
  Serial.println(rightSensorThreshold);
  return;
}

// Start streaming IR values
void stream_start() {
  streaming = true;
  Serial.println("Streaming enabled");
  return;
}


// Stop streaming IR values
void stream_stop() {
  streaming = false;
  Serial.println("Streaming disabled");
  return;
}
