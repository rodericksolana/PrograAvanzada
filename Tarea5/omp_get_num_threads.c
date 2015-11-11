/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
El siguiente código muestra el comportamiento de la función
omp_get_num_threads(), con una condición de no ser 4 se sale 
del programa, para probar que salga podemos quitar el comentario
y usar la función de la linea 19
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>


int main(int argc, const char * argv[])
{

	int num;

//omp_set_num_threads(3); 
	#pragma omp parallel
	{

		num=omp_get_num_threads(); //captura el numero de threads que se están ejecutando en la seccion paralela
if(omp_get_num_threads()==4)
		printf("Entre a la condición\n");
else abort();

	}//Cierre de parallel

printf("El total de threads fue de %d\n", num);
return 0; 	
}//Cierre de main
