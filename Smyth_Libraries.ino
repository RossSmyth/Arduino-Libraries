#include "encoderRead.h"
#include "joystickRead.h"
#include "motorControl.h"
#include "pidController.h"
#include "coroutine.h"
#include "queue.h"
#include "timerConfigure.h"

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

}

void* test1( void ) {
  return *(void**)(&test2);
}

void* test2( void ) {
  return *(void**)(&test3);
}

void* test3( void ) {
  return *(void**)(&test1);
}
