/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
Se muestra como funciona omp_get_num_procs()
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>


int main(int argc, const char * argv[])
{

int tid;
int num=0;
int i=0;

num=omp_get_num_procs();  //regresa el numero de procesadores que están disponibles
#pragma omp parallel private(tid)
{

}//Cierre de parallel
printf("El total de procesadores disponibles es: %d\n", num);

return 0; 	
}//Cierre de main
