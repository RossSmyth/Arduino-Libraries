#include "joystickRead.h"

/*
 * * * * * * * * * * * * * * * * * * * * * * * Functions
 */ 
 
// Initilizes the hardware pins and gives user struct. Don't call in loop()
struct JOYSTICK* setupJoystick(int userPitchIn, int userRollIn, int userButIn, int userAnaRes, int userJoyRange) {

  // allocate struct on heap for user
  struct JOYSTICK* userJoystick = (struct JOYSTICK*)malloc(sizeof(struct JOYSTICK));
  
  // Ensure a null pointer wasn't returned.
  if (userJoystick == NULL) {
    return NULL; // if so make it the user's problem anyways
  }
  
  // Set inputs to pins described
  userJoystick->pitchInput = userPitchIn;
  userJoystick->pitchInput = userRollIn;
  userJoystick->pitchInput = userButIn;

  // Set configuration parameters to user defiend ones.
  userJoystick->analogResolution = userAnaRes;
  userJoystick->joystickRange    = userJoyRange;
  
  // Configure for input. To be safe do the normal inputs too.
  pinMode(userJoystick->pitchInput, INPUT);
  pinMode(userJoystick->rollInput,  INPUT);
  pinMode(userJoystick->butInput,   INPUT_PULLUP);

  return userJoystick;
}

// Takes in the user's joystick struct, reads the joystick, and updates struct members.
void readJoystick(struct JOYSTICK* userJoystick) {

  // Init some variables for this function
  int rollRaw  = 0;
  int pitchRaw = 0;
  
  // Set button to the value of the button.
  userJoystick->butState = !digitalRead(userJoystick->butInput);

  // Get the raw integer analog values.
  rollRaw  = analogRead(userJoystick->rollInput);
  pitchRaw = analogRead(userJoystick->pitchInput);
  
  // Recenter them so that negative values map to the negative axes
  rollRaw  -= userJoystick->analogResolution >> 1;
  pitchRaw -= userJoystick->analogResolution >> 1;

  // Map to [-1, 1]ish float
  userJoystick->pitch = pitchRaw / userJoystick->joystickRange;
  userJoystick->roll  = rollRaw  / userJoystick->joystickRange;
}
