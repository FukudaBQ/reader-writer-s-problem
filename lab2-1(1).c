/*
Beau QU*/

#include "buffer.h"
#include <stdlib.h> /* required for rand_r(…) */
#include <pthread.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

/* the buffer */
buffer_item buffer[BUFFER_SIZE];
/* the mutex lock*/
pthread_mutex_t mutex;
/*semaphores*/
sem_t full;
sem_t empty;
int counter, in, out = 0;

int insert_item(buffer_item item) {
	int retValue = -1;
	/* insert an item into buffer */
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	
	/* if buffer is full*/
	while(in == BUFFER_SIZE){
		/*do nothing*/
	}
	/* if buffer is not full*/
	if(counter != BUFFER_SIZE){
		buffer[in] = item;
		in = (in + 1) % BUFFER_SIZE;
		counter ++;
		retValue = 0;
	}

	printf ("producer produced %d\n", item);
	/*critical section*/
	/* release mutex lock and signal*/
	pthread_mutex_unlock(&mutex);
	sem_post(&full);

	/* return 0 if successful, otherwise
	return -1 indicating an error condition */
	return retValue;
}

int remove_item(buffer_item *item) {
	int retValue = -1;
	/* remove an object from buffer and placing it in item*/
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	/*empty*/
	while(counter == 0){
		/* do nothing*/	
	}
	if(counter != 0){
		*item = buffer[out];
		out = (out+1)%BUFFER_SIZE;
		counter --;
		retValue = 0;
	}

	/* unlock and post*/
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);

	printf("consumer consumed %d\n", *item);
	/* return 0 if successful, otherwise
	return -1 indicating an error condition */
	return retValue;
}

void *producer(void *param) {
	buffer_item rand;
	unsigned int seed = time(NULL);
	while (1) {
		/* sleep for a random period of time */
		sleep(rand_r(&seed)%BUFFER_SIZE+1);
		/* generate a random number */
		rand = rand_r(&seed);
		if (insert_item(rand) < 0)
			printf("An error happens in the producer function"); 
// report error condition
	}
}
void *consumer(void *param) {
	buffer_item rand;
	unsigned int seed = time(NULL);
	while (1) {
		/* sleep for a random period of time */
		sleep (rand_r(&seed)%BUFFER_SIZE + 1);
		if (remove_item(&rand) < 0)
			printf("An error happens in consumer function"); // report error condition
	}
}

int main(int argc, char*argv[]) {
	/* 1. Get command line arguments argv[1], argv[2], argv[3] */

	int sleepTime = atoi(argv[1]);
	int numOfProducer = atoi(argv[2]);
	int numOfConsumer = atoi(argv[3]);

	/* 2. Initialize buffer, mutex, semaphores, and other global vars */
	
	/* initilize mutex*/
	pthread_mutex_init(&mutex, NULL);
	/*initilize two semaphores empty and full*/
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);
	
	/* 3. Create producer thread(s) */

	pthread_t producers[numOfProducer];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	/* use a for loop to initilize every producer threads*/
	int num = 0;
	for(num; num < numOfProducer; num ++){
		pthread_create(&producers[num], &attr, producer, NULL);
	}


	/* 4. Create consumer thread(s) */

	pthread_t consumers[numOfProducer];
	/* use a for loop to initilize every producer threads*/
	num = 0;
	for(num; num < numOfProducer; num ++){
		pthread_create(&consumers[num], &attr, consumer, NULL);
	}

	/* 5. Sleep */
	sleep(sleepTime);
	/* 6. Release resources, e.g. destroy mutex and semaphores */

	/* semaphore destory*/
	sem_destroy(&full);
	sem_destroy(&empty);
	/*thread release*/
	pthread_mutex_destroy(&mutex);

	/* 7. Exit */
	return 0;
}
