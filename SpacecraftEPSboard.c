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


// Counter Variable
int nominalCounter, warningCounter, dangerCounter;


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

	while(true)
	{   
		// Mutex Locking
		pthread_mutex_lock(&mutex);
		if (EPS_BATT[EPS_ALERT] == 5)
			{
				sleep(10);
			}
		else
			{
				;
			}	


			// Vector Initialization
			EPS_BATT[EPS_CURRENT_VAL] = sc_get_current();
    		EPS_BATT[EPS_VOLTAGE_VAL] = sc_get_voltage();
    		EPS_BATT[EPS_TEMPERATURE_VAL] = sc_get_temp();

            /*

    		printf("Current : %d\n",EPS_BATT[EPS_CURRENT_VAL]);
     		printf("Voltage : %d\n",EPS_BATT[EPS_VOLTAGE_VAL]);
        	printf("Temperature: %d\n",EPS_BATT[EPS_TEMPERATURE_VAL]);
            
            */

        // Mutex Unlocking

     	pthread_mutex_unlock(&mutex);


     	//Time Interval
   		sleep(0.0003);
     

     }
     

     pthread_exit(NULL);

}


// Second Thread
void *secondThread(void *threadid2)
{   
	long tid2;
	tid2= (long)threadid2;

	printf("It's thread %ld\n", tid2);
	
	while(true)
	{
		//Mutex Locking
		pthread_mutex_lock(&mutex);

		if (EPS_BATT[EPS_ALERT] == 5)
			{
				sleep(10);
			}
		else
			{
				;
			}	

			//CURRENT 
			if ((EPS_BATT[EPS_CURRENT_VAL] >= (CURRENT_SAFE - WARNING_THRESHOLD)) && (EPS_BATT[EPS_CURRENT_VAL] <= (CURRENT_SAFE + WARNING_THRESHOLD)))
				{
					EPS_BATT[EPS_CURRENT_STATE] = NOMINAL;
					nominalCounter = nominalCounter + 1;
					printf("Current : NOMINAL\n");
				} 
		
			else if ((EPS_BATT[EPS_CURRENT_VAL] >= (CURRENT_SAFE - DANGER_THRESHOLD)) && (EPS_BATT[EPS_CURRENT_VAL] <= (CURRENT_SAFE + DANGER_THRESHOLD)))
         		{
             		EPS_BATT[EPS_CURRENT_STATE] = WARNING;
             		warningCounter = warningCounter + 1;
             		printf("Current : WARNING\n");

         		}
         	else
         		{
         			EPS_BATT[EPS_CURRENT_STATE] = DANGER;
         			dangerCounter = dangerCounter + 1;
         			printf("Current : DANGER\n");	
         		}


         	//VOLTAGE 
         	if ((EPS_BATT[EPS_VOLTAGE_VAL] >= (VOLTAGE_SAFE - WARNING_THRESHOLD)) && (EPS_BATT[EPS_VOLTAGE_VAL] <= (VOLTAGE_SAFE + WARNING_THRESHOLD)))
				{
					EPS_BATT[EPS_VOLTAGE_STATE] = NOMINAL;
					nominalCounter = nominalCounter + 1;
					printf("Voltage : NOMINAL\n");
				} 
		
			else if ((EPS_BATT[EPS_VOLTAGE_VAL] >= (VOLTAGE_SAFE - DANGER_THRESHOLD)) && (EPS_BATT[EPS_VOLTAGE_VAL] <= (VOLTAGE_SAFE + DANGER_THRESHOLD)))
         		{
             		EPS_BATT[EPS_VOLTAGE_STATE] = WARNING;
             		warningCounter = warningCounter + 1;
             		printf("Voltage : WARNING\n");

         		}
         	
         	else
         		{
         			EPS_BATT[EPS_VOLTAGE_STATE] = DANGER;
         			dangerCounter = dangerCounter + 1;
         			printf("Voltage : DANGER\n"); 	
         		}


         	//TEMPERATURE
         	if ((EPS_BATT[EPS_TEMPERATURE_VAL] >= (TEMPERATURE_SAFE - WARNING_THRESHOLD)) && (EPS_BATT[EPS_TEMPERATURE_VAL] <= (TEMPERATURE_SAFE + WARNING_THRESHOLD)))
				{
					EPS_BATT[EPS_TEMPERATURE_STATE] = NOMINAL;
					nominalCounter = nominalCounter + 1;
					printf("Temperature : NOMINAL\n");
				} 
		
			else if ((EPS_BATT[EPS_TEMPERATURE_VAL] >= (TEMPERATURE_SAFE - DANGER_THRESHOLD)) && (EPS_BATT[EPS_TEMPERATURE_VAL] <= (TEMPERATURE_SAFE + DANGER_THRESHOLD)))
         		{
             		EPS_BATT[EPS_TEMPERATURE_STATE] = WARNING;
             		warningCounter = warningCounter + 1;
             		printf("Temperature : WARNING\n");

         		}
         	else
         		{
         			EPS_BATT[EPS_TEMPERATURE_STATE] = DANGER;
         			dangerCounter = dangerCounter + 1;
         			printf("Temperature : DANGER \n");	
         		}
        


         	printf("Current : %d\n",EPS_BATT[EPS_CURRENT_VAL]);
         	printf("Voltage : %d\n",EPS_BATT[EPS_VOLTAGE_VAL]);
         	printf("Temperature: %d\n",EPS_BATT[EPS_TEMPERATURE_VAL]);

         	printf("Nominal Values %d\n", nominalCounter);
         	printf("Warning Values %d\n", warningCounter);
         	printf("Danger Values %d\n", dangerCounter);




         // Mutex Unlocking
         pthread_mutex_unlock(&mutex);


         // Time Interval
         sleep(3);


    }
     
     pthread_exit(NULL);

}


// Third Thread
void *thirdThread(void *threadid3)
{   
	long tid3;
	tid3 = (long)threadid3;

	printf("It's thread %ld\n", tid3);

	while(true)
	{   
		

		// Mutex Locking
		pthread_mutex_lock(&mutex);

		if (EPS_BATT[EPS_ALERT] == 5)
			{
				sleep(10);
				EPS_BATT[EPS_ALERT] = 0;

			}
		else
			{
				;
			}	



			// Reporting Non-nominal States
			if (nominalCounter >= 2)
				{
					printf("Thread 3 : No Report\n");
				}

			else if ((warningCounter >=2) && (dangerCounter == 0))
				{
					if (EPS_BATT[EPS_TEMPERATURE_STATE] == 2)
						{
							printf("Thread 3 : Temperature Reported\n");
						}
					else
					{
						;
					}

					if (EPS_BATT[EPS_VOLTAGE_STATE] == 2)
						{
							printf("Thread 3 : Voltage Reported\n");
						}
					else
					{
						;
					}

					if (EPS_BATT[EPS_CURRENT_STATE] == 2)
						{
							printf("Thread 3 : Current Reported\n");
						}
					else
					{
						;
					}		
				}

			else if ((dangerCounter >= 1) && (nominalCounter <= 1))
				{	

					EPS_BATT[EPS_ALERT] = EPS_BATT[EPS_ALERT] + 1;
					printf("EPS ALERT %d\n", EPS_BATT[EPS_ALERT]);


							if (EPS_BATT[EPS_TEMPERATURE_STATE] >= 2)
						{
							printf("Thread 3 : Temperature Reported\n");
						}
					else
					{
						;
					}

					if (EPS_BATT[EPS_VOLTAGE_STATE] >= 2)
						{
							printf("Thread 3 : Voltage Reported\n");
						}
					else
					{
						;
					}

					if (EPS_BATT[EPS_CURRENT_STATE] >= 2)
						{
							printf("Thread 3 : Current Reported\n");
						}
					else
					{
						;
					}

				}

			else
			{
				;
			}	


			// Reset Counters
			nominalCounter = 0;
			warningCounter = 0;
			dangerCounter = 0;

		printf("\n\n\n\n");	



        // Mutex Unlocking

     	pthread_mutex_unlock(&mutex);


     	//Time Interval
   		sleep(3);
     

     }
     

     pthread_exit(NULL);

}



int main() 
{
  	// initialize your threads and start the program
	pthread_t threads[3];
	long t1=1,t2=2,t3=3;


	//pthread creation
	pthread_create(&threads[0], NULL, firstThread, (void *)t1);
	pthread_create(&threads[1], NULL, secondThread, (void *)t2);
	pthread_create(&threads[2], NULL, thirdThread, (void *)t3);


	//pthread exit
	pthread_exit(NULL);

}




