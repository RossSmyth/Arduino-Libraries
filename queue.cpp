#include "queue.h"

/*
 * * * * * * * * * * * * * * * *  ** * * * * * Functions
 */ 
struct CORO_QUEUE* setupQueue( unsigned int queueLength ) {

  // allocate the queue's memory
  struct CORO_QUEUE* userQueue = (struct CORO_QUEUE*)malloc(sizeof(struct CORO_QUEUE*) + sizeof(COROUTINE_DEF*) * queueLength);
  // Ensure a null pointer wasn't returned.
  if (userQueue == NULL) {
    return NULL; // if so make it the user's problem anyways
  }

  // Init the queue configuration
  userQueue->front     =  0;
  userQueue->rear      = -1;
  userQueue->qLength   =  queueLength;
  userQueue->itemCount =  0;
  
  return userQueue;
}


// Return true is the queue is full
bool checkQFull( struct CORO_QUEUE* userQueue ) {
  return userQueue->itemCount == userQueue->qLength;
}

// Returns true if the queue is empty
bool checkQEmpty( struct CORO_QUEUE* userQueue ) {
  return !(userQueue->itemCount);
}

// Inserts a coroutine to the queue.
void insertQData( COROUTINE_DEF* userCoroutine ,  struct CORO_QUEUE* userQueue) {

  if ( !checkQFull( userQueue )) {
    if ( userQueue->rear == (userQueue->qLength - 1) ) {
      userQueue->rear = -1;
    }

    userQueue->qData[++userQueue->rear] = userCoroutine;
    userQueue->itemCount++;
  }
}

// Removes an item from the front of the queue and return it
COROUTINE_DEF* removeQData( struct CORO_QUEUE* userQueue ) {
  COROUTINE_DEF* retCoroutine = userQueue->qData[userQueue->front++];

  if ( userQueue->front == userQueue->qLength ) {
    userQueue->front = 0;
  }

  userQueue->itemCount--;
  return retCoroutine;
}
