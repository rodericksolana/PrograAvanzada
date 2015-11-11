/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
Se muestra como funciona omp_get_nested ()
en el que en la segunda iteración se acepta la anidación y se puede observar el cambio
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>

void anidado(a)
{
if(a==0)
printf("No está anidado\n");
else 
printf("Si está anidado\n");
}

int main(int argc, const char * argv[])
{
int i=0;
printf("\nInicia programa\n");
anidado(omp_get_nested ()); //Verifica si está activo o no la anidación de seccion paralela
for(i=0;i<2;i++)
{
if(i>0)
{
printf("\nCambiando la anidación en el omp_set_nested\n");
omp_set_nested (1);
anidado(omp_get_nested ());
}

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
}//Cierre de for
return 0; 	
}//Cierre de main


