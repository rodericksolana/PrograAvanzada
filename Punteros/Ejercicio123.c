/*Rodrigo Solana Chao
ITESM CSF 
Ejercicio1. Apuntadores
Programación Avanzada*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define N 3

char * copiaCadena(char *);
void invierte(char *);
int tamanio(char *);

int main(int argc, const char * argv[])
{
/*Reservar memoria*/
char * cadena = (char *) malloc(N * sizeof(char));
printf("Dame una cadena de caracteres:   ");
scanf("%s", &*cadena); 
invierte(cadena);
printf("La longitud de la cadena es :  %d \n", tamanio(cadena));

char * cadena2= copiaCadena(cadena);

printf("Esta es la cadena original: %s \n", cadena);
printf("Esta es la cadena copiada: %s \n", cadena2);
printf("Dame una cadena de caracteres:   ");
scanf("%s", &*cadena); 
printf("Esta es la cadena original modificada: %s \n", cadena);
printf("Esta es la cadena copiada: %s \n", cadena2);

/*liberar memoria*/
free(cadena);
//free(cadena2);

}//Cierre de main


char * copiaCadena(char *cadena)
{
int i= tamanio(cadena);
char * cadena2 = (char *) malloc(sizeof(char) * i);
char * p = cadena;
char * d = cadena2;
    
    while ( (*d++ = *p++) != '\0') {};
    return cadena2;
}//Cierre de copiaCadena


void invierte(char * cadena)
{
char *aux;
printf("\nEsta es la cadena invertida:  ");
for(aux=cadena+tamanio(cadena); aux>=cadena;aux--)
{
printf("%c", *aux);
}//
printf("\n");
}//Cierre de invierte

int tamanio(char * cadena)
{
char *aux2 =cadena;
while(*aux2!= '\0')
aux2++;
return aux2-cadena;

}//Cierre de funcion tamanio


