#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 4
#define papel 0
#define tabaco 1
#define fosforo 2

int flag[MAX_THREADS];
int turn[MAX_THREADS];
int materiales[3];
int materialesB=0;
void *thread(void *p);

int threads=4;
int main (int argc, const char * argv[]) {
    int i, j;
   
    pthread_attr_t attr;
    pthread_t t;
    pthread_attr_init(&attr);

    int vars[MAX_THREADS];

    //inicializar arreglo con un numero maximo de IDs
    for (i=0;i<MAX_THREADS;i++) {
        vars[i] = i;
    }
    
    //se crean los hilos...
    for (j=0; j<threads;j++) {
               pthread_create(&t, &attr, thread, &vars[j]);
    }

    pthread_exit(0);

}//Cierre de main

void *thread(void *p) {


    int i, j;
    int id = *(int *) p;
    if(id == 0)
    {
        while(1)
        {
		srand(pthread_self());
		flag[id] = 1;
		int max = 0;
		for (i=0; i<threads; i++) {

		if (turn[i] > max)
		    max = turn[i]; //encontrar turno maximo
	    }
	    turn[id] = max + 1; //nuevo turno
	    flag[id] = 0; 

	    for (j=0; j<threads; j++)
	if (j != id) 
		{
		    while (turn[j] != 0 && ((turn[j] < turn[id]) || (turn[j] == turn[id] && j < id))); 
		}
	        int temp = rand()%3;
	       int temp2 = rand()%3;
		if (materiales[temp] < 2)
		{
		    materiales[temp]++;
		   materiales[temp2]++;

                    printf("Agente coloco material tipo: %d  y  tipo: %d \n",temp, temp2);
		}
		if (materiales[papel] && materiales[tabaco] && materiales[fosforo])
		    materialesB = 1;
		turn[id] = 0;
        }
    }
    else
    {
	    while(1)
	    {
	    srand(pthread_self());

	    flag[id] = 1;
	    int max = 0;

	    for (i=0; i<threads; i++) {

		if (turn[i] > max)
		    max = turn[i]; //encontrar turno maximo
	    }

	    turn[id] = max + 1; //nuevo turno
	    flag[id] = 0; 

	    for (j=0; j<threads; j++)
		if (j != id) //Si no soy yo... 
		{
		    while (turn[j] != 0 && ((turn[j] < turn[id]) || (turn[j] == turn[id] && j < id))); 
		}

	    if (materialesB)
	    {
        	materiales[papel]--;
		materiales[tabaco]--;
		materiales[fosforo]--;
		printf("fumador %d esta fumando\n", id);
		sleep(2);
		materialesB = 0;
	    }
	    
	    turn[id] = 0;
	   
	    }
	 
	}
}

