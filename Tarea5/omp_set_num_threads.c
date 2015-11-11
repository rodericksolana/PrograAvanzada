/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
se usa la función omp_set_num_threads()
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>


int main(int argc, const char * argv[])
{

int tid;
int i=0;
omp_set_num_threads(3);//especifica el numero de threads que se van a crear para la siguiente sección paralela

#pragma omp parallel private(tid)
{

printf("Ejecutando la sección paralela\n");

}//Cierre de parallel


return 0; 	
}//Cierre de main
