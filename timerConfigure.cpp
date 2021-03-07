#include "timerConfigure.h"

// Some helper macros for setting and clearing regitser bits.
#define setBit(registerName, bitName)   ((registerName) |= (1 << (bitName)))
#define clearBit(registerName, bitName) ((registerName) &= ~(1 << (bitName)))

// Calcultes the prescale for timers, sets the prescale, and sets the counters.
bool setPrescale( unsigned int timeout1, enum TIMER_UNITS units1, unsigned int timeout2, enum TIMER_UNITS units2) {

  // Function variables
  unsigned int prescale;
  bool         success = true; // default true.

  // Cast to unsigned long for caculations and convert to cycles.
  unsigned long longTimeout1 = (unsigned long)timeout1 * units1;
  unsigned long longTimeout2 = (unsigned long)timeout2 * units2;

  if ( longTimeout1 < UINT_MAX && longTimeout2 < UINT_MAX ) {
    // If less than INT_MAX then prescaler can be 1 (no scaling).
    setBit(TCCR1B, CS10);
    prescale = 1;
  } else if ( longTimeout1 < UINT_MAX * 8 && longTimeout2 < UINT_MAX * 8 ) {
    // Set prescaler to 8
    setBit(TCCR1B, CS11);
    prescale = 8;
  } else if ( longTimeout1 < UINT_MAX * 256 && longTimeout2 < UINT_MAX * 256) {
    // Set prescaler to 256
    setBit(TCCR1B, CS12);
    prescale = 256;
  } else if ( longTimeout1 < UINT_MAX * 1024 && longTimeout2 < UINT_MAX * 1024 ) {
    // Set prescaler to 1024
    setBit(TCCR1B, CS12);
    prescale = 1024;
  } else {
    // Cannot set correctly. This is undefined behavior. The interrupt will fire at random time if enabled.
    success = false;
  }

  // Scale the counter values
  longTimeout1 /= prescale;
  longTimeout2 /= prescale;

  // Set the counter(s)
  OCR1A = (unsigned int)longTimeout1;
  OCR1B = (unsigned int)longTimeout2;

  return success;
}

// Enables a timer interrupt
void timerEnable( unsigned char timer ) {

  // Ensure the input capture interrupt is off.
  clearBit(TIMSK1, ICIE1);

  // Selects the timer to set. Either timer 1 or 2.
  switch (timer) {
    case 1 :
      setBit(TCCR1A, COM1A0); // Turns timer on so it clear each trigger
      setBit(TIMSK1, OCIE1A); // Enable interrupt
      break;
    case 2 :
      setBit(TCCR1A, COM1B0); // Turns timer on so it clear each trigger
      setBit(TIMSK1, OCIE1B); // Enable interrupt
      break;
  }
}

// Disables a timer interrupt
void timerDisable( unsigned char timer ) {

  // Selects the timer to disable. Either timer 1 or 2.
  switch (timer) {
    case 1 :
      clearBit(TIMSK1, OCIE1A); // Disable interrupt
      break;
    case 2 :
      clearBit(TIMSK1, OCIE1B); // Disable interrupt
      break;
  }
}
