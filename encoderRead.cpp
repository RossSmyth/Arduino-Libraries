#include "encoderRead.h"
/*
 * * * * * * * * * * * * * * * * * * * * * * * Variables
 */ 

// There are put here under the assumption that an AVR board is used
// because there are only two external interrupts on them. So only one encoder can be used.
static volatile int  encoderCount;
static int*          userEncoderChannel2;

/*
 * * * * * * * * * * * * * * * * * * * * * * * Functions
 */ 

// Prototype for interrupt that is harder for the user to access
void Chan1Rise();

// Sets up the encoder library with pins and variables
struct ENCODER* setupEncoder(int userChannel1, int userChannel2, float userAngPP) {

  // allocate struct on heap for user
  struct ENCODER* userEncoder = (struct ENCODER*)malloc(sizeof(struct ENCODER));
  
  // Ensure a null pointer wasn't returned.
  if (userEncoder == NULL) {
    return NULL; // if so make it the user's problem anyways
  }
  
  // Set pins for the interrupt to use
  userEncoder->encoderChannel1 = userChannel1;
  userEncoder->encoderChannel2 = userChannel2;
  
  // Set the encoder pin modes
  pinMode(userEncoder->encoderChannel1, INPUT);
  pinMode(userEncoder->encoderChannel2, INPUT);

  // Sets the degrees per pulse of the encoder
  userEncoder->anglePerPulse = userAngPP;

  // Ensure the memory is 0 for total angle
  userEncoder->angle = 0;
  
  // Attach interrupt. Only look at rising edges of one channel for direction detection
  attachInterrupt(digitalPinToInterrupt(userEncoder->encoderChannel1), Chan1Rise, RISING);

  // Set pointer to be used in the interrupt
  userEncoderChannel2 = &userEncoder->encoderChannel2;
  
  return userEncoder;
}

// Resets the encoder accumulater and the pulse counter to zero.
void resetEncoder( struct ENCODER* userEncoder ) {
  userEncoder->angle = 0;

  // Turn interrupts off to be safe.
  noInterrupts();
  encoderCount = 0;
  // Turn interrupts back on
  interrupts();
}

// Updates angle variable since last reading
void readEncoder( struct ENCODER* userEncoder ) {
  // Turn interrupts off to be safe.
  noInterrupts();
  
  // Increment angle based upon encoder counts
  userEncoder->angle += encoderCount * userEncoder->anglePerPulse;

  // Reset encoder counts
  encoderCount = 0;
  
  // Turn interrupts back on
  interrupts();
}

/*
 * * * * * * * * * * * * * * * * ** * * * * * Interrupts
 */ 

// Check the direction and increments count
// Only increments or decrements counts cause floating point math
// inside of an interrtupt is a bit sketchy.
void Chan1Rise() {
  // check state of other channel
  switch (digitalRead(*userEncoderChannel2)) {
    case 1 : encoderCount++; break; // If high, increment
    case 0 : encoderCount--; break; // If low, decrement
  }
}
