// Queue.h

#ifndef HEADER_QUEUE
  #define HEADER_QUEUE
    #include "Arduino.h"
    #include "coroutine.h"
        
    // Queue implemented with a circular buffer
    // With this event loop implementation, there should never be more 
    // events in the queue than initially defined.
    struct CORO_QUEUE {
        int front; 
        int rear;
        unsigned int qLength;
        unsigned int itemCount; // Length of queue/buffer
        COROUTINE_DEF* qData[];    
    };

    // Init queue with given length
    struct CORO_QUEUE* setupQueue( unsigned int queueLength );
        
    bool           checkQFull(  struct CORO_QUEUE*                  );
    bool           checkQEmpty( struct CORO_QUEUE*                  );
    void           insertQData( void* (*corout), struct CORO_QUEUE* );
    COROUTINE_DEF* removeQData( struct CORO_QUEUE*                  );
#endif
