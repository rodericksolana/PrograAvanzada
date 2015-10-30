#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define enanos 7

int sillas = 4;
int pendiente=0;

pthread_mutex_t enano = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t blancaN = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t come = PTHREAD_COND_INITIALIZER;
pthread_cond_t cocina = PTHREAD_COND_INITIALIZER;



void * servir(void * arg)
{


	while(1)
	{

	pthread_mutex_lock(&blancaN);
	if(pendiente==0)
	{
	    printf("BlancaNieves: Dando la vuelta\n");
	    pthread_cond_wait(&cocina, &blancaN); //espera
	   
	}
	printf("BlancaNieves: me pidieron de comer\n");
	pthread_mutex_unlock(&blancaN);
	printf("BlancaNieves: Cocinando\n");
	sleep(rand()%3);   
	pthread_mutex_lock(&blancaN);
	pendiente--;
	pthread_cond_signal(&come);
	pthread_mutex_unlock(&blancaN);
	printf("BlancaNieves: Ya puedes comer enano\n");


	//pthread_mutex_unlock(&mutex);

	}
	pthread_exit(NULL);
}//Cierre de servir

void * comer(void * arg)
{


	while(1)
	{

	printf("Enano: %d trabajando\n", (int)arg);
	sleep(rand() % 15);

	pthread_mutex_lock(&enano);
	if(sillas>0)
	{
	    sillas--;
	    printf("Enano: %d ya me senté quedan %d sillas\n", (int)arg, sillas);
	    pthread_mutex_unlock(&enano);
	    
	    pthread_mutex_lock(&blancaN);
	    pendiente++;
	    pthread_mutex_unlock(&blancaN);
	    pthread_cond_signal(&cocina); //avisar a blancaNieves
	    printf("Enano: %d dice:  blancaNives Tengo Hambre!\n", (int)arg);
	    pthread_mutex_lock(&blancaN);
	    pthread_cond_wait(&come, &blancaN); //esperar a que sirva de comer
	    pthread_mutex_unlock(&blancaN);	
	    printf("Enano: %d ya estoy comiendo\n", (int)arg);
	    sleep(rand() % 2); //tiempo q tarda en comer
	    
	    pthread_mutex_lock(&enano);
	    sillas++;
	    printf("Enano: %d ya acabe quedan %d sillas\n", (int)arg,sillas);
	    
	    pthread_mutex_unlock(&enano);
	}
	else
	{
printf("Enano:  %d no hay sillas disponibles! Regreso en un rato\n", (int)arg);
	    pthread_mutex_unlock(&enano);
	}
	}
	pthread_exit(NULL);
}//Cierre de comer


int main(int argc, const char * argv[]) 
{
int i=0;

	srand(time(NULL));

	pthread_t blancanieves;
	pthread_t * enanitos = (pthread_t *) malloc (sizeof(pthread_t) * enanos);

	blancanieves = pthread_create(&blancanieves, NULL, servir, NULL); //crea el thread

	for ( i = 0; i < enanos; i++) {
	pthread_create(enanitos+i, NULL, comer, i); //crea el thread
	}

	for (i = 0; i < enanos; i++) {
	pthread_join(*(enanitos+i), NULL);
	}
	pthread_join(blancanieves, NULL);

	free(enanitos);

	return 0;
}//Cierre de main




