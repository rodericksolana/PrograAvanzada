/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
Se muestra como funciona omp_set_nested ()
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>


int main(int argc, const char * argv[])
{
int i=0;

omp_set_nested (1);  // me permite anidar una sección paralela
omp_set_num_threads(2);
    #pragma omp parallel
        {
	
printf("Seccion1: Soy el thread  %d  y el maximo de threads aqui son: %d\n",  omp_get_thread_num(), omp_get_max_threads() );
omp_set_num_threads(4);
 #pragma omp parallel
        {
	printf("Seccion2-Anidada: Soy el thread  %d  y el maximo de threads aqui son: %d\n",  omp_get_thread_num(), omp_get_max_threads() );

	}

        }

return 0; 	
}//Cierre de main
