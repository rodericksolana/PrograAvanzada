/*Rodrigo Solana Chao 
Matricula: A01129839
ITESM CSF CARRERA ITC
Se muestra como funciona omp_get_cancellation
Regresa un valor booleano 
0 no se ha cancelado ninguna región
1 se ha cancelado y sale de la zona paralela
*/
#include <stdio.h>
#include<stdlib.h>
#include <omp.h>


int main(int argc, const char * argv[])
{
int i=0;

    #pragma omp parallel
        {
if(omp_get_cancellation()!=0)
{
            printf("Saliendo del programa\n");
		abort();

}
else printf("No se ha cancelado ninguna sección\n");
        }


return 0; 	
}//Cierre de main
