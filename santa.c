/** Primeira solução ao problema do Papai Noel */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
using namespace std;
const int MAX_RAINDEER = 9;
const int MAX_SIMULTANEOUS_ELVES = 3; /* Max number of elves that can get help simultaneously */
const int MAX_ELVES = 10;  /* Max number of elves that can get help simultaneously */
bool isSantaSleeping = false;

volatile int elves = 0, raindeer = 0;

volatile bool santaDeparted = false;

sem_t santaSem, raindeerSem;
pthread_mutex_t elfTex = PTHREAD_MUTEX_INITIALIZER, contLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t coutTex = PTHREAD_MUTEX_INITIALIZER;

vector<string> canvas;

map<string, int> getSystemStatus(){
  map<string, int> m;
  
   m["isSantaSleeping"] = isSantaSleeping;
    m["elvesWaiting"] = elves;
  m["elvesOnQueue"] = MAX_ELVES - elves;
   m["raindeers"] = raindeer;
 
 m["santaDeparted"] = santaDeparted;

  return m;
}


void drawRaindeers(int total, int startLine, bool hitched){
	vector <string> rena(4);
	int i;
	
	canvas[startLine] = string(" ,--.  .__         ");
	canvas[startLine+1] = string("('\\  \\_ \\/},=.-._  ");
	canvas[startLine+2] = string("   \\   ';._)_.')-''");
	canvas[startLine+3] = string(" ,___\\_________/__)");
	canvas[startLine+4] = string("  ,___Y_____Y_____)");

	if (!hitched) {
	rena[0] = string("     ff  ");
	rena[1] = string("  ,__/_>o");
	rena[2] = string("  (___)  ");
	rena[3] = string("  << \\\\  ");
	}

	else {
		rena[0] = string("     ff  ");
		rena[1] = string("  ,__/_>o");
		rena[2] = string("~~(___)~~");
		rena[3] = string("  << \\\\  ");
	}
	for (i = 0; i < total; i++){
		canvas[startLine] += rena[0];
		canvas[startLine+1] += rena[1];
		canvas[startLine+2] += rena[2];
		canvas[startLine+3] += rena[3];
	}
}



void drawElves(int startLine, int numberElves ) {
    vector<string> elf(8);
    
    if ( numberElves > 0 ) {
        elf[0] = canvas[startLine] =   string("      ___,@   ");
        elf[1] = canvas[startLine+1] = string("     /  <     ");
        elf[2] = canvas[startLine+2] = string(" _  /    \\  _ "); 
        elf[3] = canvas[startLine+3] = string(" \\`/______\\´/ "); 
        elf[4] = canvas[startLine+4] = string(" |; (e  e) ;| ");
        elf[5] = canvas[startLine+5] = string(" \\/\\   7  /\\/ ");   
        elf[6] = canvas[startLine+6] = string("    \\'=='/    ");
        elf[7] = canvas[startLine+7] = string("     \\__/     ");    


        for (int n = 1; n < numberElves; n++) {
            for (int  i = 0; i < 8; i++)
                canvas[startLine+i] += elf[i];   
        }
    }
}

void drawSantaClausAndStringWithSizeOfElvesQueue(int startLine, bool isSantaWake, int queueSize){
  if (isSantaWake){
    canvas[startLine]  = string("");
    canvas[startLine+1]  = string("    -\"\"\", ");
    canvas[startLine+2]  = string("   /____, \\");
    canvas[startLine+3]  = string("   {_____}`{}");
    canvas[startLine+4]  = string("  (/ O O \\)");
    canvas[startLine+5]  = string("  {`-=^=-`}");
    canvas[startLine+6]  = string("  {   u   }");
    canvas[startLine+7]  = string("   {     }");
    canvas[startLine+7]  = string("    `-,-`");
  }
  else{
    canvas[startLine]  = string("");
    canvas[startLine+1]  = string("    -\"\"\", ");
    canvas[startLine+2]  = string("   /____, \\");
    canvas[startLine+3]  = string("   {_____}`{}");
    canvas[startLine+4]  = string("  (/ - - \\)   Z");
    canvas[startLine+5]  = string("  {`-=^=-`}  z");
    canvas[startLine+6]  = string("  {   -   }Z");
    canvas[startLine+7]  = string("   {     }");
    canvas[startLine+7]  = string("    `-,-`");
  }
  
    stringstream ss;
    ss << queueSize ;
    string aux;
    ss >> aux;
    
    canvas[startLine+3]  += string("			DUENDES NA FILA");
    canvas[startLine+4]  += string("				") +  aux;
  
   
}

void drawSystem(){
	system("clear");
	map<string, int> systemStatus = getSystemStatus();
	canvas.assign(40,string(""));
	drawSantaClausAndStringWithSizeOfElvesQueue(0,!systemStatus["isSantaSleeping"],systemStatus["elvesOnQueue"]);
	drawElves(15,systemStatus["elvesWaiting"]);
	drawRaindeers(systemStatus["raindeers"],30, systemStatus["santaDeparted"]);
	
	for(int i=0; i < canvas.size(); ++i)
		cout << canvas[i] << endl;
	
	sleep(1);
}




void prepareSleigh(){
// 	printf("Todas as renas chegaram! Papai vai acorda-las\n");
	santaDeparted = true;
	this_thread::sleep_for(  chrono::milliseconds( 500 ) );
}

void helpElves(){
// 	printf("Vou ajudar meus elfos!\n\n\n\n");
	this_thread::sleep_for(  chrono::milliseconds( 2000 ) );
}


void santa_t (){
	while(!santaDeparted){
		sem_wait (&santaSem);
		pthread_mutex_lock(&contLock);
		if (raindeer == MAX_RAINDEER){
			int i;
			prepareSleigh();
			for (i = 0; i < MAX_RAINDEER; i++)
				sem_post(&raindeerSem);
		}
		else if (elves == MAX_SIMULTANEOUS_ELVES){
			helpElves();
		}
		
		drawSystem();
		pthread_mutex_unlock(&contLock);

		sleep(1);
	}
}

void getHitched(int id){
//     cout << "rena: " << id << " esta sendo amarrada" << endl;
  this_thread::sleep_for(  chrono::milliseconds( 100 ) );
}

void raindeer_t (int id){
	
	sleep(rand()%6);
	
	pthread_mutex_lock(&contLock);

	raindeer++;
// 	printf("Chegou a rena %d\n", raindeer);


	if (raindeer == MAX_RAINDEER)
		sem_post (&santaSem);
	
	
	drawSystem();
	pthread_mutex_unlock(&contLock);

	   sleep(1);
	
	
	sem_wait(&raindeerSem);
	getHitched(id);	
}

void getHelp(int id){
  pthread_mutex_lock(&coutTex);
//   cout << "elfo: " << id << " esta sendo ajudado" << endl;
    pthread_mutex_unlock(&coutTex);
  this_thread::sleep_for(  chrono::milliseconds( 1000 ) );
}

void elf_t (int id){
	while(true){

// 	  cout << "ELFO " << id << " NO AGUARDO!" << endl;

	  pthread_mutex_lock(&elfTex);

	  pthread_mutex_lock(&contLock);
	  elves++;


	  if (elves == MAX_SIMULTANEOUS_ELVES)
		  sem_post(&santaSem);
	  else{

		  pthread_mutex_unlock(&elfTex);
	  }
	  
	  pthread_mutex_unlock(&contLock);
	  
	  
	  drawSystem();
	  
	  

	   sleep(1);
	   
	   
	  getHelp(id);
// 	  cout << "elves: " << elves << endl;


	  pthread_mutex_lock(&contLock);
	  elves--;
	  if (elves == 0)
		  pthread_mutex_unlock(&elfTex);
	  
	  
	  
	  pthread_mutex_unlock(&contLock);

	 drawSystem();

	  

	  sleep(1);

	}
}

int main(){
	
	system("resize -s 50 130");
	drawSystem();
	srand( time(NULL) );
	
	sem_init(&raindeerSem, 0 ,0);
	sem_init(&santaSem, 0, 0);

	vector<thread*> threadsVector;

	threadsVector.push_back( new thread(santa_t) );

	for(int i=1; i <= MAX_RAINDEER ; ++i)
		threadsVector.push_back( new thread(raindeer_t,i) );

	for(int i=1; i <= MAX_ELVES; ++i)
		threadsVector.push_back( new thread(elf_t,i) );

	for(int i=0; i < threadsVector.size(); ++i)
		threadsVector[i]->join();

	return 0;
}
