/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
Se muestra como funciona omp_get_dynamic()
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>

void dinamico(int a)
{
if (a==0)
printf("La sección NO es dinámica\n");
else 
printf("La sección es dinámica\n");
}

int main(int argc, const char * argv[])
{
int num=0;
 omp_set_dynamic(1); // me permite hacer dinamicos los threads es booleano:  0 no los hace dinamicos y con !=0 ej: 1 si.

printf("\nPrimera sección\n");
    printf("el valor de la función es: %d\n", omp_get_dynamic( )); //Ve si una sección es dinamica o no regresando booleanos. 0 no y con !=0 ej: 1 si
    #pragma omp parallel
        #pragma omp master //Para que solamente el master haga algo
        {
           dinamico(omp_get_dynamic( ));
        }

printf("\ncambio del valor omp_set_dynamic\n");
omp_set_dynamic(0);

printf("\nSegunda sección\n");
    printf("el valor de la función es: %d\n", omp_get_dynamic( )); //Ve si una sección es dinamica o no regresando booleanos. 0 no y con !=0 ej: 1 si
    #pragma omp parallel
        #pragma omp master //Para que solamente el master haga algo
        {
           dinamico(omp_get_dynamic( ));
        }



return 0; 	
}//Cierre de main
