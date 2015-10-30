#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define Pisos 5
#define Robot 5


pthread_mutex_t *mutex_niveles;
pthread_cond_t *cond_niveles;

int pesoRobot[Robot];
int pesoPisos[Pisos];
int pesoTotal[Pisos];

void *robot(void *arg){

	//datos_robot *d = (datos_robot*)arg;
	printf("Voy de compras Robot %d\n",(int)arg);

	//Comienzo mis niveles
	int cont = 0;
	while (cont < Pisos)
	{

		pthread_mutex_lock(mutex_niveles+cont);
		if (pesoRobot[(int)arg] + pesoTotal[cont] > pesoPisos[cont])
		{
			printf("Robot %d tengo que esperar a que baje el peso\n",(int)arg);
			pthread_cond_wait(cond_niveles+cont,mutex_niveles+cont);
			pthread_mutex_unlock(mutex_niveles+cont);
		}//Cierre de if
		

		else 
		{
			pesoTotal[cont] += pesoRobot[(int)arg];
			pthread_mutex_unlock(mutex_niveles+cont);
			printf("Robot %d de compras en la seccion %d con peso %d  de  %d\n",(int)arg,cont,pesoTotal[cont],pesoPisos[cont]);
			int compra = rand()%3; //Tiempo que se tarda comprando
			sleep(compra);
			printf("Robot %d ya termine de comprar en la seccion %d\n",(int)arg,cont);
			pthread_mutex_lock(mutex_niveles+cont);
			pesoTotal[cont] -= pesoRobot[(int)arg];
			pthread_cond_broadcast(cond_niveles+cont);
			pthread_mutex_unlock(mutex_niveles+cont);
			cont++;
		}//cierre de else
	}//Cierre de while

	pthread_exit(NULL);
}


int main(int argc, const char * argv[])
{

	pthread_t *robots = (pthread_t*)malloc(Robot*2*sizeof(pthread_t));
	mutex_niveles = (pthread_mutex_t*)malloc(Pisos*sizeof(pthread_mutex_t));
	cond_niveles = (pthread_cond_t*)malloc(Pisos*sizeof(pthread_cond_t));

	srand(time(NULL));
	int i;
	for (i=0;i<Pisos;++i){
		pesoPisos[i] = rand() % 10+5;
		pesoTotal[i]=0;
		printf("La seccion %d pesa: %d \n",i,pesoPisos[i]);
	}

	for (i=0;i<Pisos;++i){
		pthread_mutex_init(mutex_niveles+i,NULL);
		pthread_cond_init(cond_niveles+i,NULL);
	}

	//Creando robots
	

	for (i=0; i < Robot; i++){		
	pesoRobot[i] = rand() % 4 +1;
	printf("El robot %d pesa: %d \n",i,pesoRobot[i]);
	pthread_create(robots+i,NULL,robot,(i));
	}

	//Esperando a que acaben
	for (i=0;i<Robot;++i){
		pthread_join(*(robots),NULL);
	}

	free(mutex_niveles);
	free(cond_niveles);
	free(robots);

	return 0;
}

