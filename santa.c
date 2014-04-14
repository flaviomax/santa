
/** Primeira solução ao problema do Papai Noel */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <vector>
using namespace std;
const int MAX_RAINDEER = 9;
const int MAX_SIMULTANEOUS_ELVES = 3; /* Max number of elves that can get help simultaneously */
const int MAX_ELVES = 10;  /* Max number of elves that can get help simultaneously */


volatile int elves = 0, raindeer = 0, santaDeparted = 0;
sem_t santaSem, raindeerSem;
pthread_mutex_t elfTex = PTHREAD_MUTEX_INITIALIZER, contLock = PTHREAD_MUTEX_INITIALIZER;

void prepareSleigh(){
	printf("Todas as renas chegaram! Papai vai acorda-las\n");
	this_thread::sleep_for(  chrono::milliseconds( 500 ) );
}

void	helpElves(){
	printf("Vou ajudar meus elfos!\n");
	this_thread::sleep_for(  chrono::milliseconds( 200 ) );
}


void santa_t (){
	while(santaDeparted == 0){
		sem_wait (&santaSem);
		pthread_mutex_lock(&contLock);
		if (raindeer == MAX_RAINDEER){
			int i;
			prepareSleigh();
			for (i = 0; i < MAX_RAINDEER; i++)
				sem_post(&raindeerSem);
		}
		else if (elves == MAX_ELVES){
			helpElves();
		}
		pthread_mutex_unlock(&contLock);
	}
}



void raindeer_t (int id){
	pthread_mutex_lock(&contLock);
	raindeer++;
	printf("Chegou a rena %d\ n", raindeer);
	if (raindeer == MAX_RAINDEER)
		sem_post (&santaSem);
	pthread_mutex_unlock(&contLock);

	sem_wait(&raindeerSem);
	//getHitched();	
}

void elf_t (int id){
	pthread_mutex_lock(&elfTex);
	pthread_mutex_lock(&contLock);
	elves++;
	printf("Chegou o elfo %d\n", elves);
	if (elves == MAX_ELVES)
		sem_post(&santaSem);
	else
		pthread_mutex_unlock(&elfTex);
	pthread_mutex_unlock(&contLock);

	//getHelp();

	pthread_mutex_lock(&contLock);
	elves--;
	if (elves == 0)
		pthread_mutex_unlock(&elfTex);
	pthread_mutex_unlock(&contLock);
}

int main(){
	sem_init(&raindeerSem, 0 ,0);
	sem_init(&santaSem, 0, 0);

	vector<thread*> threadsVector;

	threadsVector.push_back( new thread(santa_t) );

	for(int i=1; i <= MAX_RAINDEER; ++i)
		threadsVector.push_back( new thread(raindeer_t,i) );

	for(int i=1; i <= MAX_ELVES; ++i)
		threadsVector.push_back( new thread(elf_t,i) );

	for(int i=0; i < threadsVector.size(); ++i)
		threadsVector[i]->join();

	return 0;
}

