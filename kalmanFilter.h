// kalmanFilter.h

#ifndef HEADER_KALMANFILTER
  #define HEADER_KALMANFILTER
    #include "Arduino.h"
    #include <string.h>
    
    /*
     * * * * * * * * * * * * * * * * ** * * * * * Defintions
     */ 

    // Kalman filter struct for a second-order system with one input and one sensor.
    struct KALMAN {
      // Constant members
      const float stateTrans[2][2];   // State Transition matrix (often called "A")
      const float controlTrans[1][2]; // Control matrix (input->state change)
      const float observMatrix[2];    // Maps state to observation (sensor output)
      const float measCov;            // Measurement covariance
      const float procCov[2][2];      // Process Covariance matrix
    
      // variable members
      float state[1][2];         // The estimated state vector
      float covariance[2][2]; // Estmates the error for each part of the state
    };
  
    
    // Prototypes for functions
    void runKalman( struct KALMAN* userKalman );
#endif
