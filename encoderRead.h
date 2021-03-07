// encoderRead.h
#ifndef HEADER_ENCODERREAD
  #define HEADER_ENCODERREAD
    #include "Arduino.h"
  
    struct ENCODER {
      // Inputs
      int encoderChannel1;
      int encoderChannel2;
    
      // Config
      float anglePerPulse;
    
      // User output
      float angle;
   };

    // Prototype for functions
    struct ENCODER* setupEncoder(int userChannel1, int userChannel2, float userAngPP);
    void            readEncoder( struct ENCODER* );
    void  reset_encoder( void );
#endif
