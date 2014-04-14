/** Primeira solução ao problema do Papai Noel */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_RAINDEER 9
#define MAX_ELVES 3 /* Max number of elves that can get help simultaneously */

volatile int elves = 0, raindeer = 0, santaDeparted = 0;
sem_t santaSem, raindeerSem;
pthread_mutex_t elfTex = PTHREAD_MUTEX_INITIALIZER, contLock = PTHREAD_MUTEX_INITIALIZER;


void *santa (void *v){
	while(santaDeparted == 0){
		sem_wait (&santaSem);
		pthread_mutex_lock(&contLock);
		if (raindeer == MAX_RAINDEER){
			int i;
			prepareSleigh();
			for (i = 0; i < MAX_RAINDEER; i++)
				sem_post(&raindeer_sem);
		}
		else if (elves == MAX_ELVES)
			helpElves();
		pthread_mutex_unlock(&contLock);
	}
}

void *raindeer (void *v){
	pthread_mutex_lock(&contLock);
	raindeer++;
	if (raindeer == MAX_RAINDEER)
		sem_post (&santaSem);
	pthread_mutex_unlock(&contLock);
	
	sem_wait(&raindeer_sem);
	getHitched();	
}

void *elf (void *v){
	pthread_mutex_lock(&elfTex);
	pthread_mutex_lock(&contLock);
	elves++;
	if (elves == MAX_ELVES)
		sem_post(&santaSem);
	else
		pthread_mutex_unlock(&elfTex);
	pthread_mutex_unlock(&contLock);
	
	getHelp();
	
	pthread_mutex_lock(&contLock);
	elves--;
	if (elves == 0)
		sem_post(&elfTex);
	pthread_mutex_unlock(&contLock);
}
