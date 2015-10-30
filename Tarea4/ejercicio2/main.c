#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

int aux=0;
int sigue=-1;
int direccion=-1;
int mujeres=0;
int hombres=0;
int ocupado=0;
pthread_mutex_t lock;


void* agregaCola(void *arg)
{

	while(1)
	{

pthread_mutex_lock(&lock2);
pthread_mutex_lock(&lock);


int temp;
	temp = rand() % 100;

	if(temp%2==0)
	{
	mujeres++;
	printf("Llega una Mujer (%d en espera)\n", mujeres);
	
	if(aux==0)
	{
	direccion=0;
	aux=1;
	}

	}

	else if(temp%3==0)
	{
	hombres++;
	printf("Llega un Hombre (%d en espera)\n", hombres);
	
	if(aux==0)
	{
	direccion=1;
	aux=1;
	}
	}

 /*Aqui va el codigo*/
//printf("Agente con id %d\n",(int)arg);
//pthread_cond_signal(&cond);
pthread_cond_broadcast(&cond);
pthread_mutex_unlock(&lock);
sigue=1;
}//Cierre de while
}


void* pasar(void * arg)
{

while(1)
{
int sum=0;
pthread_mutex_lock(&lock);

while (sigue == -1)
    pthread_cond_wait(&cond, &lock);


//printf("Fumador con id %d\n",(int)arg);


  /*
Aqui va el codigo
*/

if(ocupado==2)
printf("Sanitario ocupado por Hombres\n");
else if(ocupado==1)
printf("Sanitario ocupado por Mujeres\n");
else if(ocupado==0)
printf("El baño está vacío\n");


switch ((int)arg)
        {
           
            case 0: 
                if (direccion==0 && mujeres>0){ //sigue = 0 vengo del este
                    ocupado=1;
	mujeres--;

	  printf("Sale una MUJER, quedan  %d\n",  mujeres);
                }
                break;
            case 1:
                if (direccion==1 && hombres>0){
                  ocupado=2;
	hombres--;
	  printf("Sale un Hombre, quedan %d\n", hombres);
	
                }
                                
        }//Cierre de switch
	if(hombres==0 && mujeres==0)
	{
	ocupado=0;
	}
	else if(mujeres==0)
	{
	ocupado=2;
	direccion=1;
	}

	else if(hombres==0)
		{
	ocupado=1;
	direccion=0;
	}




	pthread_mutex_unlock(&lock);
	pthread_mutex_unlock(&lock2);
	//sigue=0; //aviso al agente que despierte
	sleep(1);

}//Cierre
}



int main(void)
{
pthread_t * tid = (pthread_t *) malloc (sizeof(pthread_t) * 3);

  pthread_create(tid, NULL, &agregaCola, 2); //crea el thread
  pthread_create(tid+1, NULL, &pasar, 0); //crea el thread
  pthread_create(tid+2, NULL, &pasar, 1); //crea el thread

    pthread_join(*(tid), NULL);
    pthread_join(*(tid+1), NULL);
    pthread_join(*(tid+2), NULL);

    	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	free(tid);
printf("Libere memoria\n");

    return 0;
}
