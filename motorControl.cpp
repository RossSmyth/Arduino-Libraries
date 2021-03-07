#include "motorControl.h"
/*
 * * * * * * * * * * * * * * * * * * * * * * * Functions
 */ 

// init motor struct for user and configure pins for PWM. Don't call in loop()
struct MOTOR* setupMotor( int motorOut1, int motorOut2 ) {

  // allocate struct on heap for user
  struct MOTOR* userMotor = (struct MOTOR*)malloc(sizeof(struct MOTOR));

  // Ensure a null pointer wasn't returned.
  if (userMotor == NULL) {
    return NULL; // if so make it the user's problem anyways
  }

  userMotor->motorChan1 = motorOut1;
  userMotor->motorChan2 = motorOut2;
  
  // Initilize pins for motor PWM control
  pinMode(userMotor->motorChan1, OUTPUT);
  pinMode(userMotor->motorChan2, OUTPUT);

  return userMotor;
}

// This function sets motor speed
void writeMotor( float motorEffort, struct MOTOR* userMotor ) {
  
  // Init variables for function
  int  motorSpeed;
  bool motorDir;
  
  // Convert from user range to PWM [-255, 255]
  motorEffort *= userMotor->userConvert;

  // Cast to int
  motorSpeed = (int)abs(motorEffort);

  // Set to true for forwards when greater than zero
  motorDir = (motorEffort > 0);
  
  if (!motorSpeed) {      // If speed is zero, outputs are low
    analogWrite(userMotor->motorChan1, 0);
    analogWrite(userMotor->motorChan2, 0);
  } else if (motorDir) { // If positive have IN1 is PWM output, IN2 is low
    analogWrite(userMotor->motorChan1, motorSpeed);
    analogWrite(userMotor->motorChan2, 0);
  } else {               // If negative have IN1 low, IN2 is PWM output
    analogWrite(userMotor->motorChan1, 0);
    analogWrite(userMotor->motorChan2, motorSpeed);
  }
}
