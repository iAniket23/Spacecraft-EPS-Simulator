#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <pthread.h>
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


// Mutex Initialize
pthread_mutex_t mutex;


/* Functions from sc.c */
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


// First Thread
void *firstThread(void *threadid)
{   
	long tid;
	tid = (long)threadid;

	printf("It's thread %ld\n", tid);

	while(TRUE)
	{   
		// Mutex Locking
		pthread_mutex_lock(&mutex);


			// Vector Initialization
			EPS_BATT[EPS_CURRENT_VAL] = sc_get_current();
    		EPS_BATT[EPS_VOLTAGE_VAL] = sc_get_voltage();
    		EPS_BATT[EPS_TEMPERATURE_VAL] = sc_get_temp();



    		printf("Current : %d\n",EPS_BATT[EPS_CURRENT_VAL]);
     		printf("Voltage : %d\n",EPS_BATT[EPS_VOLTAGE_VAL]);
        	printf("Temperature: %d\n",EPS_BATT[EPS_TEMPERATURE_VAL]);


        // Mutex Unlocking

     	pthread_mutex_unlock(&mutex);


     	//Time Interval
   		sleep(3);
     

     }
     

     pthread_exit(NULL);

}


// Second Thread
void *secondThread(void *threadid2)
{   
	long tid2;
	tid2= (long)threadid2;

	printf("It's thread %ld\n", tid2);
	
	while(TRUE)
	{
		//Mutex Locking
		pthread_mutex_lock(&mutex);

			//CURRENT 
			if ((EPS_BATT[EPS_CURRENT_VAL] >= (CURRENT_SAFE - WARNING_THRESHOLD)) && (EPS_BATT[EPS_CURRENT_VAL] <= (CURRENT_SAFE + WARNING_THRESHOLD)))
				{
					EPS_BATT[EPS_CURRENT_STATE] = NOMINAL;
				} 
		
			else if ((EPS_BATT[EPS_CURRENT_VAL] >= (CURRENT_SAFE - DANGER_THRESHOLD)) && (EPS_BATT[EPS_CURRENT_VAL] <= (CURRENT_SAFE + DANGER_THRESHOLD)))
         		{
             		EPS_BATT[EPS_CURRENT_STATE] = WARNING;

         		}
         	else
         		{
         			EPS_BATT[EPS_CURRENT_STATE] = DANGER;	
         		}


         	//VOLTAGE 
         	if ((EPS_BATT[EPS_VOLTAGE_VAL] >= (VOLTAGE_SAFE - WARNING_THRESHOLD)) && (EPS_BATT[EPS_VOLTAGE_VAL] <= (VOLTAGE_SAFE + WARNING_THRESHOLD)))
				{
					EPS_BATT[EPS_VOLTAGE_STATE] = NOMINAL;
				} 
		
			else if ((EPS_BATT[EPS_VOLTAGE_VAL] >= (VOLTAGE_SAFE - DANGER_THRESHOLD)) && (EPS_BATT[EPS_VOLTAGE_VAL] <= (VOLTAGE_SAFE + DANGER_THRESHOLD)))
         		{
             		EPS_BATT[EPS_VOLTAGE_STATE] = WARNING;

         		}
         	
         	else
         		{
         			EPS_BATT[EPS_VOLTAGE_STATE] = DANGER;	
         		}


         	//TEMPERATURE
         	if ((EPS_BATT[EPS_TEMPERATURE_VAL] >= (TEMPERATURE_SAFE - WARNING_THRESHOLD)) && (EPS_BATT[EPS_TEMPERATURE_VAL] <= (TEMPERATURE_SAFE + WARNING_THRESHOLD)))
				{
					EPS_BATT[EPS_TEMPERATURE_STATE] = NOMINAL;
				} 
		
			else if ((EPS_BATT[EPS_TEMPERATURE_VAL] >= (TEMPERATURE_SAFE - DANGER_THRESHOLD)) && (EPS_BATT[EPS_TEMPERATURE_VAL] <= (TEMPERATURE_SAFE + DANGER_THRESHOLD)))
         		{
             		EPS_BATT[EPS_TEMPERATURE_STATE] = WARNING;

         		}
         	else
         		{
         			EPS_BATT[EPS_TEMPERATURE_STATE] = DANGER;	
         		}
        


         	printf("Current : %d\n",EPS_BATT[EPS_CURRENT_VAL]);
         	printf("Voltage : %d\n",EPS_BATT[EPS_VOLTAGE_VAL]);
         	printf("Temperature: %d\n\n\n",EPS_BATT[EPS_TEMPERATURE_VAL]);


         // Mutex Unlocking
         pthread_mutex_unlock(&mutex);


         // Time Interval
         sleep(3);


    }
     
     pthread_exit(NULL);

}


int main() 
{
  	// initialize your threads and start the program
	pthread_t threads[2];
	long t1=1,t2=2;


	//pthread creation
	pthread_create(&threads[0], NULL, firstThread, (void *)t1);
	pthread_create(&threads[1], NULL, secondThread, (void *)t2);


	//pthread exit
	pthread_exit(NULL);

}


