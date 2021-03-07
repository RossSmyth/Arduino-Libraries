// coroutine.h

/*
 * This might be cursed. But also might be epic.
 * 
 * This makes simple coroutines for easier event handling. Needs a seperate event loop for that though
 * Uses a Duff device to make the function a state-machine. Needs static variables though otherwise the 
 * state is not saved between reentries.
 * 
 * Best to just wrap the entire coroutine in the begin and finish preprocessor gates
 * 
 * Example that does nothing useful
 * int foo( void ) {
 *   crBegin;
 *   crReturn(1);
 *   crFinish;
 * }
 * 
 * Best practice is probably to have variables that have real work done to them either returned or as globals.
 * Could make some more whacky macros for saving the state but I don't think they are needed.
 * 
 * Between each crReturn should be fairly short operations, or 
 */

#ifndef HEADER_COROUTINE
  #define HEADER_COROUTINE

    // typedef of couroutines. A bit nasty.
    // But it's just a function that has no arguments and returns
    // a function pointer disguised as a void pointer.
    typedef void* COROUTINE_DEF( void );

    // Begin the coroutine state-machine. the argument should be the function itself.
    #define crBegin(crName) static int scrLine = 0; crPointer = *(void**)(&crName); switch(scrLine) { case 0:;

    // Awaits another coroutine. 
    #define crAwait(func) do { scrLine=__LINE__; return *(void**)(&func); case __LINE__:; } while (0)

    // Ends the coroutine state machine
    #define crFinish } return NULL;

    // Delays in a non-blocking way until some amount of time has passed
    // Basically just yields back to the caller each time called until the duration is met.
    #define co_delay(duration) do {\
      static unsigned long start;\
      for (start = millis(); millis() - start < (duration); ) return crPointer;\
    } while (0)
#endif
