#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <inttypes.h>
#include "../sc/sc.h"
#include "eps.h"

/* VALUES AND TOLERANCES */
#define VOLTAGE_SAFE          15
#define CURRENT_SAFE          45
#define TEMPERATURE_SAFE      355
#define WARNING_THRESHOLD     2
#define DANGER_THRESHOLD      4

/* ERROR CODES */
#define NOMINAL               1
#define WARNING               2
#define DANGER                3


/* BATTERY VECTOR */
uint16_t EPS_BATT[EPS_SIZE];

// YOUR CODE HERE!

int main() {
  // initialize your threads and start the program
  
  return 0;
}