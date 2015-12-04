#include "mpi.h"
#include <stdio.h>
#include <omp.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdbool.h>

#define MAXSIZE 10

void master(int , int *);
void robot(int , int *);


void gestor_sigusr1 (int senial)
 { 
printf("***(%d)*** se mando sigusr1 (señal número %d) \n", getpid(), senial);
sleep(2);
 }


int main(int argc, char *argv[])
{
    int myid, numprocs, nh, tid;
    //int *data[MAXSIZE][MAXSIZE];
int * data = (int *) malloc((MAXSIZE * MAXSIZE) * sizeof(int)); //Tablero con memoria dinámica
    int * p = data;
    int posicion=0;
    int i, n, x, low, high, myresult = 0, result = 0, j;
    int tiempo=0;
    double start, stop;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    int  longitud;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    
    MPI_Get_processor_name(hostname, &longitud);
    
    
    n = MAXSIZE;
    
    if (myid == 0) //Es el master
    {
        /* Inicializar datos en paralelo con OpenMP y aritmetica de apuntadores*/
#pragma omp parallel for private(p) shared(data, n)
        for(p=data; p< (data + (n*n)); p++) {
i++;
if((i%17)==0)
*p=1; //1 son los abstaculos del tablero
else
*p= 0; //0 son las casillas por las que se puede mover el robot

        }//Cierre de for
printf("Se genero el tablero con memoria dinamica\n");

master(numprocs, p);
}//Cierre de master

else
{
printf("Hostname:%s\n", hostname);
        #pragma omp parallel num_threads(posicion)
        {     
            int id = omp_get_thread_num();
	       robot(numprocs, p);
            
        }//Cierre de parallel
    }//Cierre de else 
        //start = MPI_Wtime();
        

    /* Broadcast a todos los procesos */
    MPI_Bcast(data, n, MPI_INT, 0, MPI_COMM_WORLD);
    
    /* Porción de data  que va a procesar cada procesador*/
    x = (n*n)/numprocs;
    low = myid * x;
    high = low + x;
    if (myid == numprocs - 1) { high = n; }
    
#pragma omp parallel default(shared) private(i, nh, tid)
    {
        nh = omp_get_num_threads();
        tid = omp_get_thread_num();
        
#pragma omp for reduction(+:myresult)
        for(i = low; i < high; i++) {
tiempo++;
if((tiempo%10)==0)
signal(SIGUSR1,gestor_sigusr1);

myresult += *(data+i);
            //myresult += data[i][j];
printf("\nEstoy en la posicion %d\n", i);
            printf("\t --- Procesador %d (%s) con %d hilos. Soy el hilo %d y calculo la iteración %d\n", myid, hostname, nh, tid, i);
        }

    }//Cierre de parallel
    
    printf(" *** Yo soy el procesador %d (%s)  y mi suma = %d\n", myid , hostname, myresult);
    
    MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    /* Suma global mediante reducción */

    if (myid == 0)
    {
        printf("La suma total del vector es = %d.\n", result);
        
        stop = MPI_Wtime();
        
        printf("Tiempo de ejecución de la sección paralela = %f \n", stop-start);
    }
    
    MPI_Finalize();

free(data);
    
    return 0;
}



void master(int numprocs, int *p)
{
    printf("Hola soy el master\n");  
	//printf("%d\n", MPI_MAX_PROCESSOR_NAME);
    int r1;
int i;
int total = 0;
while(true){
	total=0;
    for( i = 1; i < numprocs; i++)
	{
	 MPI_Recv(&r1,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	/*printf("en la terminal %d hay %d personas en las bandas\n", i, r1);
	total+=r1;*/

	}
	//printf("En todas las terminales hay %d personas en las bandas\n", total);
    //MPI_Recv(&r1,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    //MPI_Recv(&r2,1,MPI_INT,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }//Cierre de while
    
    
}//cierre de funcion


void robot(int numprocs, int *p)
{
  
}//Cierre de funcion



