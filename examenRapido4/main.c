#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_THREADS 4
#define papel 0
#define tabaco 1
#define fosforo 2

int flag[MAX_THREADS];
int turn[MAX_THREADS];
int pap=0;
int tab=0;
int fos=0;
int materiales[3];
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
		if (materiales[temp] < 2)
		{
		if(temp==0)
	{
		    materiales[tabaco]++;
		    materiales[fosforo]++;
		printf("Agente coloco material tipo: tabaco  y  fosforo \n");
		}
		else if(temp==1)
		{
				    materiales[papel]++;
				    materiales[fosforo]++;
		printf("Agente coloco material tipo: papel y fosforo \n");
		}

		else if(temp==2)
		{
				    materiales[tabaco]++;
				    materiales[papel]++;
		printf("Agente coloco material tipo: tabaco y papel \n");
		}

                    
		}
		if (materiales[tabaco] && materiales[fosforo])
		    pap = 1;
		if (materiales[papel] && materiales[fosforo])
		    tab = 1;
		if (materiales[papel] && materiales[tabaco])
		    fos = 1;

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

	    if (pap)
	    {
		materiales[tabaco]--;
		materiales[fosforo]--;
		printf("fumador 1 esta fumando, tengo papel\n");
		sleep(2);
		pap = 0;
	    }
	 if (tab)
	    {
        	materiales[papel]--;
		materiales[fosforo]--;
		printf("fumador 2 esta fumando, tengo tabaco\n");
		sleep(2);
		tab = 0;
	    }
	 if (fos)
	    {
        	materiales[papel]--;
		materiales[tabaco]--;
		printf("fumador 3 esta fumando, tengo fosforo\n");
		sleep(2);
		fos = 0;
	    }
	    
	    turn[id] = 0;
	   
	    }
	 
	}
}

