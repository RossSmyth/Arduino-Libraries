#include "Arduino.h"

// motorControl.h

#ifndef HEADER_MOTORCONTROL
  #define HEADER_MOTORCONTROL
    /*
     *  This is the motor controller module.
     *  Allocate and construct the struct using the setupMotor() function.
     *  Set the motor voltage with the writeMotor() function
     *  
     *  Keep in mind that the conversion in the setupmotor should map the range [-255, 255] to 
     *  the motor voltage range. If the range is not symmetric then this module will not work.
     *  It is better to use a float literal as no conversion must happen.
     *  
     *  Just provide the PWM out pins for the motor and the conversion and it'll work. Just make sure
     *  that the pins are actually avaiable for PWM.
     *  
     *  Example:
     *    struct MOTOR* myMotor;
     *    myMotor = setupMotor( 5, 4, 41.5f )
     *    
     *    // Write 5 "volts" (equivelently) to the motor output
     *    writeMotor( 5.0f, myMotor );
     *    
     *  Be sure to check for a null pointer being returned as always.
     */

    /*
     * * * * * * * * * * * * * * * * ** * * * * * Defintions
     */ 
    
    struct MOTOR {
      // Hardware
      int motorChan1; // Motor driver input 1
      int motorChan2; // Motor driver input 1
    
      // Configure
      float userConvert; // Conversion from user input to [-255, 255]
    };
  
    
    // Prototypes for functions
    struct MOTOR* setupMotor( int motorOut1, int motorOut2, float userPWMconvert );
    void          writeMotor( float motorEffort, struct MOTOR* userMotor );
#endif
