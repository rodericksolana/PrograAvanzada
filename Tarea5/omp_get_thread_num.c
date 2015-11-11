/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
Se muestra como funciona omp_get_thread_num()
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>


int main(int argc, const char * argv[])
{

int tid;
int i=0;

#pragma omp parallel private(tid)
{
tid=omp_get_thread_num(); //nos permite regresar el id del thread en ejecución
if(tid==0)
{
printf("Soy el thread Master con tid %d\n", tid);
}
else
printf("Soy el thread con tid %d\n", tid);



}//Cierre de parallel


return 0; 	
}//Cierre de main
