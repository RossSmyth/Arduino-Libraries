// joystickRead.h
#ifndef HEADER_JOYSTICKREAD
  #define HEADER_JOYSTICKREAD
    #include "Arduino.h"
  
    /*
     * * * * * * * * * * * * * * * * ** * * * * * Defintions
     */ 
     
    struct JOYSTICK {
      // Inputs
      int pitchInput; // Pitch analog input pin
      int rollInput;  // Roll analog input pin
      int butInput;   // Button digital input pin (active low, will have INPUT_PULLUP)
  
      // Configs
      int analogResolution; // analog resolution of the ADC
      int joystickRange;    // analog range of the joystick from the center of the ADC range.
  
      // Variables specifically for user access
      float pitch;    // Pitch input normalized to [-1, 1]
      float roll;     // Roll input normalized to [-1, 1]
      bool  butState; // Button state boolean
    };
     
    // Prototype for setup function
    struct JOYSTICK* setupJoystick(int userPitchIn, int userRollIn, int userButIn, int userAnaRes, int userJoyRange);
    void             readJoystick(  struct JOYSTICK* );
#endif
