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

long int voltage=0,current=0,temp=0;

int rand_range(int min, int max) 
{
  srand(time(0)+clock()+rand());
  return (uint16_t) (rand() % (max - min + 1)) + min;
}

uint16_t sc_get_voltage(void) 
{
  return (uint16_t) rand_range(10, 20); // 18
}

uint16_t sc_get_current(void) 
{
  return (uint16_t) rand_range(40, 50);
}

uint16_t sc_get_temp(void) 
{
  return (uint16_t) rand_range(350, 360);
}



void *firstthread(void *threadid)
{ long tid;
	tid= (long)threadid;
	printf("It's thread %ld\n", tid);
	while(1)
	{
	voltage = sc_get_voltage();
    current = sc_get_current();
    temp = sc_get_temp();
    printf("Voltage is %ld\n",voltage );
    printf("current is %ld\n",current );
    printf("temp is %ld\n",temp);
    sleep(3);
     }
     pthread_exit(NULL);

}

int main() {
  // initialize your threads and start the program
	pthread_t threads[1];
	long t1=1;

	pthread_create(&threads[0], NULL, firstthread, (void *)t1);
	
	pthread_exit(NULL);

}
