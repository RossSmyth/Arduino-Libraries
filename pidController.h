// pidController.h

#ifndef HEADER_PIDCONTROLLER
  #define HEADER_PIDCONTROLLER
    #include "Arduino.h"

    struct PID_STATE {
      float integral;
      float prevErr;
    };
    
    struct PID_CONTROLLER  { // May add more terms for more interesting controllers (i.e. anti-windup and derivative filter)
      float             Kp;        // Proportional gain
      float             Ki;        // Integral gain
      float             Kd;        // Derivative gain
      int               dt;        // Time step (milliseconds)
      struct PID_STATE* pidState;  // Current state of the controller
    };
    
    // Prototype for setup function
    struct PID_CONTROLLER* setupPID(float userKp, float userKi, float userKd, int userdt);
    void                   resetPID( PID_CONTROLLER*  );
    float                  runPID( float error, PID_CONTROLLER* );
  
#endif
