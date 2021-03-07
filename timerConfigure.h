// timerConfigure.h

#ifndef HEADER_TIMERCONFIGURE
  #define HEADER_TIMERCONFIGURE
    #include "Arduino.h"
    #include <limits.h>

    /*  
     *   This is a library for semi-intelligently setting timer interrupts. 
     *  On the Arduino ATmega328p architecture (and many others) there are 
     *  multiple timers that can be used. This library sets the two counters 
     *  (timers) on TIMER1 which is a 16-bit timer, therefore it can count 
     *  the highest. TIMER1 also doesn't do much else. TIMER0 counts for the 
     *  micros() and millis() functions, and TIMER2 is used on pins D3 and D11.
     *  This does effect the PWM output on pins D9 and D10, meaning they will 
     *  not be usable as PWM pins. If you set the pins as outputs after using 
     *  this library, then this library will not work as expected.
     *  
     *  You should use this because remembering how to set the registers is hard.
     *  You should also call the functions in a specific order, or else unexpected
     *  results may occur. Primarily this would be the interrupt firing when not 
     *  wanted. The order is the following:
     *  
     *  1. setPrescale
     *  2. timerEnable
     *  3. timerDisable [optional]
     *  
     *  Example:
     *  
     *  #include "timerConfigure.h"
     *  
     *  volatile exampleFlag = false;
     *  
     *  void setup() {
     *    // Sets the first timer to fire every millisecond, and sets the other to not fire at all.
     *    setPrescale( 1, MILLI, 0, 0 );
     *  
     *    // Enables the first timer
     *    timerEnable( 1 );
     *  
     *    // To be safe, disables the second timer explicitly. May not be needed.
     *    timerDisable( 2 );
     *  }
     *  
     *  // interrupt for timer1
     *  ISR(TIMER1_COMPA_vect) {
     *    exampleFlag = true;  
     *  }
     *  
     *  This shows that this library is relatively painless to use. IF you do not want 
     *  to use a timer, just set the values to zero in the setPrescale function. You may
     *  not have to call disableTimer on a timer that is unused, but I'm not sure. It won't
     *  hurt anything if you do though. For reference, the ISR for the second timer is shown 
     *  below.
     *  
     *  ISR(TIMER1_COMPB_vect) { 
     *    exampleFlag2 = true;
     *  }
     *  
     */
     
    // Enum constants that also convert from the units to raw clock cycles.
    enum TIMER_UNITS {
      CYCLES = 1,
      MICRO  = 16,
      MILLI  = 16000
    };

    // Sets the prescale and timer. Only call once or the behavior will not be as expected.
    bool setPrescale( unsigned int timeout1, enum TIMER_UNITS units1, unsigned int timeout2, enum TIMER_UNITS units2);
    
    // Sets interrupts on timer 1. We get one timer. But it's 16-bit so that's cool.
    void timerEnable( unsigned char timer );

    // Disable timers
    void timerDisable( unsigned char timer );
#endif
