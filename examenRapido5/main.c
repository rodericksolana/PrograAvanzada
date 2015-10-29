#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define cines 3
#define salas 4
#define asientos 2
int sillas [cines * salas * asientos]; //numero total de sillas en todos los cines

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

int condition=0;
int aux=0;
int sigue=0;
int comprando=0;

int temp=0;
pthread_mutex_t lock;


void* agente(void *arg)
{

while(1)
{
if (sigue==0)
{
pthread_mutex_lock(&lock2);
pthread_mutex_lock(&lock);
condition = 1;
//printf("Agente con id %d\n",(int)arg);
if(comprando==0)
{
 aux = rand() % 3;
printf("acaba de llegar un cliente  aux  %d\n", aux);
comprando=1;
}

pthread_cond_signal(&cond);
pthread_mutex_unlock(&lock);
sigue=1;
}//Cierre de while
}
}



void* compra(void * arg)
{

while(1)
{
    int cine;
    int sala;
    int asiento;
pthread_mutex_lock(&lock);
while (condition == 0)
    pthread_cond_wait(&cond, &lock);
//printf("Fumador con id %d\n",(int)arg);

switch ((int)arg)
        {
           
            case 0: 
                if (aux==0){
                    printf("Voy a comprar boletos soy el proceso %d\n", (int)arg);

                    comprando=0;
cine = rand()%cines;
sala=rand()%salas;
asiento=rand()%asientos;

printf("proceso %d  Comprando el asiento %d, en la sala %d, en el cine %d\n", (int)arg, asiento, sala, cine);
                    sleep (rand()%3);
                    
                }
                break;
            case 1:
                if (aux==1){
                      printf("Voy a comprar boletos soy el proceso %d\n", (int)arg);
comprando=0;
cine = rand()%cines;
sala=rand()%salas;
asiento=rand()%asientos;

printf("proceso %d  Comprando el asiento %d, en la sala %d, en el cine%d\n", (int)arg, asiento, sala, cine);
                    sleep (rand()%3);
                }
                break;
            case 2:
                if (aux==2){
                      printf("Voy a comprar boletos soy el proceso %d\n", (int)arg);
                    comprando=0;
cine = rand()%cines;
sala=rand()%salas;
asiento=rand()%asientos;

printf("proceso %d  Comprando el asiento %d, en la sala %d, en el cine %d\n", (int)arg, asiento, sala, cine);
                    sleep (rand()%3);
                }
                    
        }



  /*
Aqui va el codigo
*/


pthread_mutex_unlock(&lock);
pthread_mutex_unlock(&lock2);

sigue=0; //avido al agente que despierte
sleep(2);

}//Cierre
}



int main(void)
{


pthread_t * tid = (pthread_t *) malloc (sizeof(pthread_t) * 5);

  pthread_create(tid, NULL, &compra, 0); //crea el thread
  pthread_create(tid+1, NULL, &compra, 1); //crea el thread
  pthread_create(tid+2, NULL, &compra, 2); //crea el thread
  pthread_create(tid+2, NULL, &agente, 3); //crea el thread

    pthread_join(*(tid), NULL);
    pthread_join(*(tid+1), NULL);
    pthread_join(*(tid+2), NULL);

    	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	free(tid);
printf("Libere memoria\n");

    return 0;
}
