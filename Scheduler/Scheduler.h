#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

//------ Loop 1 -------

// Initialize a "loop" to run every X milliseconds
// Sets up a variable to hold time of last run
// Must be called outside of the infinite loop
#define INIT_LOOP_1_FREQUENCY(X) \
    unsigned long lastRun1 = 0;
 
// Start of code to run every X milliseconds
// May run slower than every X milliseconds if loop and rest of code too slow
#define BEGIN_LOOP_1_FREQUENCY(X) \
if ( (lastRun1 + (X)) <= millis()) {
 
// end of loop to run every X milliseconds
#define END_LOOP_1_FREQUENCY(X) \
    lastRun1 = millis(); \
    } 


//------- Loop 2 --------

// Initialize a "loop" to run every X milliseconds
// Sets up a variable to hold time of last run
// Must be called outside of the infinite loop
#define INIT_LOOP_2_FREQUENCY(X) \
    unsigned long lastRun2 = 0;
 
// Start of code to run every X milliseconds
// May run slower than every X milliseconds if loop and rest of code too slow
#define BEGIN_LOOP_2_FREQUENCY(X) \
if ( (lastRun2 + (X)) <= millis()) {
 
// end of loop to run every X milliseconds
#define END_LOOP_2_FREQUENCY(X) \
    lastRun2 = millis(); \
    } 


//-------- Loop 3 ---------

// Initialize a "loop" to run every X milliseconds
// Sets up a variable to hold time of last run
// Must be called outside of the infinite loop
#define INIT_LOOP_3_FREQUENCY(X) \
    unsigned long lastRun3 = 0;
 
// Start of code to run every X milliseconds
// May run slower than every X milliseconds if loop and rest of code too slow
#define BEGIN_LOOP_3_FREQUENCY(X) \
if ( (lastRun3 + (X)) <= millis()) {
 
// end of loop to run every X milliseconds
#define END_LOOP_3_FREQUENCY(X) \
    lastRun3 = millis(); \
    } 


#endif
