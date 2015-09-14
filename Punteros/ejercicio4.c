/*Rodrigo Solana Chao
ITESM CSF 
Ejercicio2. Apuntadores
Programación Avanzada*/

#include <stdio.h>
#include <stdlib.h>

void llenarArreglo(int *, int, int);
void imprimir(int *, int, int);

int main(int argc, const char * argv[])
{
int n , m;
printf("Dame el numero de filas: ");
scanf("%d", &n);
printf("Dame el numero de columnas: ");
scanf("%d", &m);
int *arreglo = (int *) malloc((n*m) * sizeof(int));
llenarArreglo(arreglo,n, m);
imprimir(arreglo,n,m);
free(arreglo);
return 0;
}//Cierre de main

void llenarArreglo(int *a, int n, int m)
{
int i=0;int j=0;int aux=0;
for(i=0;i<n*m;i++)
{
for (j=0;j<m;j++)
{
printf("Dame el elemento de la posicion %d ", aux);
printf(", %d:  ",j);
scanf("%d",&*a+i);
//printf("\ni es igual a: %d \n", i);
++i;
}//Cierre de for interno
--i;
aux++;
}//Cierre de for
}//Cierre de función llenarArreglo

void imprimir(int *a, int n, int m)
{
int i=0;int j=0;
for(i=0;i<n*m;i++)
{
for (j=0;j<m;j++)
{
printf("%d  ",*(a+i));
++i;
}//Cierre de for interno
--i;
printf("\n");
}//Cierre de for
}//Cierre de función imprimir

