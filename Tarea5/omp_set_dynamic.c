/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
Se muestra como funciona omp_set_dynamic()
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>



int main(int argc, const char * argv[])
{
int num=2;
 omp_set_dynamic(num); // me permite hacer dinamicos los threads es booleano:  0 no los hace dinamicos y con !=0 ej: 1 si.
    
    #pragma omp parallel
        #pragma omp master //Para que solamente el master haga algo
        {
if(num!=0)
            printf("Se hizo dinamico el thread\n");
else printf("El thread no es dinamico\n");
        }

return 0; 	
}//Cierre de main
