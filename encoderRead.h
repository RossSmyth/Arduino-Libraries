// encoderRead.h
#include "Arduino.h"

#ifndef HEADER_ENCODERREAD
  #define HEADER_ENCODERREAD
    /* encoderRead module
     *  This module manages a quarature encoder. It calculates both the angle and velocity of the device.
     *  To use, allocate a struct pointer of type ENCODER provided in this header.
     *  After that pass the pins for the encoder to use, and the angle per pulse of the encoder.
     *  Ensure that these pins can have external interrupts attached, otherwise this library will not work at all.
     *  I don't think it would even compile. Unless you (the user) is attaching interrupts mid-program.
     *  
     *  Example:
     *    struct ENCODER* myEncoder; // init pointer
     *    myEncoder = setupEncoder( 2, 3, 0.35f ); // setup encoder struct and all the other fun parts
     *  
     *    // Read the encoder and output the angle and velocity
     *    readEncoder( myEncoder ); 
     *    Serial.print(myEncoder->angle, DEC);
     *    Serial.print("\t")
     *    Serial.println(myEncoder->velocity, DEC);
     *  
     *  Theoretically the only members of the struct that need to be access are angle and velocity.
     *  If the system is ran for a long time (around an hour) the velocity will have one data point
     *  that will be extremly large in magnitude due to the time overflowing.
     *  
     *  Make sure to check for null pointers being set to the struct in the constructor.
     */
    struct ENCODER {
      // Inputs
      int encoderChannel1;
      int encoderChannel2;
    
      // Config
      float anglePerPulse;

      // "Private" (even if no such thing)
      unsigned long _lastRead;
      
    
      // User output
      float angle;
      float velocity;
   };

    // Prototype for functions
    struct ENCODER* setupEncoder(int userChannel1, int userChannel2, float userAngPP);
    void            readEncoder( struct ENCODER* userEncoder );
    void            resetEncoder( struct ENCODER* userEncoder );
#endif
