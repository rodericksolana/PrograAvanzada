#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define UAD 5 //Secciones
FILE * datos;
int medidas[UAD];
int alarmas[UAD];
int i=0;

pthread_t central;
pthread_mutex_t mutexes[UAD * 2] = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_archivo = PTHREAD_MUTEX_INITIALIZER;

void registro(int);
void registroCritico(int);

void * threadfunc(void * arg)
{
    int temp;

    while(1)
    {
        sleep(rand()%3 + 1);
        pthread_mutex_lock(&(*(mutexes + (int) arg)));

        medidas[(int) arg] = rand()%10;
        pthread_mutex_unlock(&(*(mutexes + (int) arg)));
        if(!(temp =rand()%10))
        {
            printf("UAD #%d - VALOR CRITICO - se envió la alarma\n", (int) arg);
            
            pthread_mutex_lock(mutexes + (int) arg + UAD);
            
            alarmas[(int) arg]++;
            pthread_kill(central, SIGUSR1);
         
            pthread_mutex_unlock(mutexes + (int) arg + UAD);
        }

    }
    pthread_exit(NULL);
}

void * centralfunc(void * arg)
{
    signal(SIGALRM, registro);
    signal(SIGUSR1, registroCritico);

    alarm(rand()% 5);
    while(1);
    pthread_exit(NULL);
}



void registro(int ids) 
{
    printf("Tomando Registros.\n");
    for (i = 0; i < UAD; i++)
    {
        pthread_mutex_lock(mutexes+i);
        pthread_mutex_lock(&m_archivo);
        
        datos = fopen("datos", "a+");
        fprintf(datos,"UAD #%d medicion total=>%d\n",i, medidas[i]);
        fclose(datos);
        pthread_mutex_unlock(&m_archivo);
        pthread_mutex_unlock(mutexes+i);
        alarm(rand()%5);
    }
printf("Cerrando Archivo.\n");
}

void registroCritico(int ids)
{
    for (i = 0; i < UAD; i++)
    {
        pthread_mutex_lock(mutexes+UAD+i);

        if (alarmas[i])
        {
            pthread_mutex_lock(&m_archivo); 
            datos = fopen("datos", "a+");
            fprintf(datos,"UAD #%d  - Alerta! VALOR-CRITICO\n",i);
            fclose(datos);
            pthread_mutex_unlock(&m_archivo);
            alarmas[i]--;
        }
        
        pthread_mutex_unlock(mutexes+UAD+i);


    }

}


int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
 
    pthread_t * uads = (pthread_t *) malloc (sizeof(pthread_t) * UAD);
    pthread_create(&central,NULL,centralfunc,NULL);

    for (i = 0; i < UAD; i++) {
        pthread_create(uads+i, NULL, threadfunc, i);
    }

   
   

    for (i = 0; i < UAD; i++) {
        pthread_join(*(uads+i), NULL);
    }
    
    pthread_join(central, NULL);
    
    free(uads);
    
    return 0;
}


