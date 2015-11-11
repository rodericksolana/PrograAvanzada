/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
Se muestra como funciona omp_in_parallel()  
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>

void parallel(int);

int main(int argc, const char * argv[])
{

int tid;
int num=0;
int i=0;

printf("\nInicio del programa\n");
num=omp_in_parallel();//nos regresa 0 si la sección no está en paralelo y 1 si está en paralelo
parallel(num);

printf("\nEntrando en la seccion paralela\n");
#pragma omp parallel private(tid)
{
num=omp_in_parallel();
parallel(num);
}//Cierre de parallel

printf("\nSaliendo de la sección paralela\n");

num=omp_in_parallel();
parallel(num);

return 0; 	
}//Cierre de main

void parallel (int a)
{

if(a==0)
printf("Esta sección no está en paralelo\n");
else 
printf("Esta sección está en paralelo\n");


}//cierre de parallel
