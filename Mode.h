//if use ATOMIC to calculate success task and fail task insertion

// #define _use_ATOMIC
//if use MUTEX to calculate success task and fail task insertion

#define _use_MUTEX

//if use INT it will addition in each thread and sum it after join
// #define _use_INT

// #define SINGLE_THREAD

#define MULTI_THREAD
#ifdef MULTI_THREAD 
    #define NUMBER_OF_THREADS 6
#endif

// ---- please dont edit the code bellow this line -----//

// ----- if default implementation

#if !defined(_use_ATOMIC) && !defined(_use_MUTEX) && !defined(_use_INT)
    #define _use_INT
#endif

#if !defined(SINGLE_THREAD) && !defined(MULTI_THREAD) 
    #define SINGLE_THREAD
#endif

 