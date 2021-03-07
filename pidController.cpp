#include "pidController.h"

/*
 * * * * * * * * * * * * * * * *  ** * * * * * Functions
 */ 


// Initilizes PID struct. Since this will be called in setup() free() doesn't need to be worried about. Unless it does.
// Basically don't use this function inside loop()
struct PID_CONTROLLER* setupPID(float userKp, float userKi, float userKd, int userdt) {

  // allocate memory for struct to be used outside this stack frame (on heap)
  struct PID_CONTROLLER* userPID = (struct PID_CONTROLLER*)malloc(sizeof(struct PID_CONTROLLER));

  // Ensure a null pointer wasn't returned.
  if (userPID == NULL) {
    return NULL; // if so make it the user's problem anyways
  }
  
  // Init to user's values
  userPID->Kp = userKp;
  userPID->Ki = userKi;
  userPID->Kd = userKd;
  userPID->dt = userdt;

  // init pid state on heap
  userPID->pidState = (struct PID_STATE*)malloc(sizeof(struct PID_STATE));
  
  // Ensure a null pointer wasn't returned.
  if (userPID->pidState == NULL) {
    free(userPID); // if it was free the memory and return all null.
    return NULL;
  }
  
  userPID->pidState->integral = 0;
  userPID->pidState->prevErr  = 0;

  // Give the user a struct pointer and let them deal with it.
  return userPID;
}

void resetPID( PID_CONTROLLER* userPID) {
  userPID->pidState->integral = 0;
  userPID->pidState->prevErr  = 0;
}

// This function takes in the error and controller config and returns effort
float pid_run( float error, PID_CONTROLLER* userPID) {

  // Return value
  float effort;
  
  // Accumulate more error. Convert to seconds.
  userPID->pidState->integral += (userPID->dt * 0.001f) * error;

  // Calculate the effort to output [Kp*e + Ki*integral(e) + Kd*diff(e)]
  effort = userPID->Kp * error + 
           userPID->Kp * userPID->pidState->integral + 
           userPID->Kp * (error - userPID->pidState->prevErr) / (userPID->dt * 0.001f);

  // Set the previous error
  userPID->pidState->prevErr = error;

  // return
  return effort;
}
