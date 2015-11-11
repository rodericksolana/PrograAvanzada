/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
Se muestra como funciona omp_get_max_threads()
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>


int main(int argc, const char * argv[])
{

int i=0;
	int num;
num=omp_get_max_threads(); //nos regresa el numero maximo de threads que hay en ejecución o que se pueden crear.
omp_set_num_threads(num);
	printf("\nPrimera seccion\n");
	#pragma omp parallel
	{
printf("Estoy usando el max de threads de esta pc\n");
		
	}//Cierre de parallel
printf("El num max de threads fue de %d\n", num);

printf("Cambiando el num de threads a 2\n");
omp_set_num_threads(2);
	#pragma omp parallel
	{
printf("Estoy usando el max de threads que se declararon para esta seccion\n");
		
	}//Cierre de parallel
num=omp_get_max_threads();
printf("El num max de threads fue de %d\n", num);
return 0; 	
}//Cierre de main
