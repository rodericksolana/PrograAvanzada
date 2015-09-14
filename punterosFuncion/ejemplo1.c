#include <stdio.h>
#include <stdlib.h>

typedef void(* opcion_t) (int); 

#define N 4
void abrir(int);
void guardar(int);
void salir(int);
void copiar(int);


int main(int argc, const char * argv[])
{

//void(*)(int) *menu =();
opcion_t * menu=((opcion_t*) malloc(N * sizeof(opcion_t)));

*(menu)=abrir;
*(menu+1)=guardar;
*(menu+2)=salir;
*(menu+3)=copiar;

printf("---Opciones---\n1-Abrir\n2-Guardar\n3-Salir\n4-Copiar\nEscoge tu opción:  ");
int opcion=0;

scanf("%d", &opcion);

/*Utilizando switch*/
/*
switch(opcion)
{
case 1:
abrir(opcion);
break;
case 2:
guardar(opcion);
break;
case 3:
salir(opcion);
break;
case 4:
copiar(opcion);
break;
default:
printf("opcion no valida\n");
break;
}
//menu[opcion-1](opcion);
*/
/*Apuntadores a funciones*/

(*(menu+opcion-1))(opcion);
free(menu);
return 0;
}//Cierre de main


void abrir(int opcion)
{
printf("%d - abriendo el archivo...\n", opcion);
}


void guardar(int opcion)
{
printf("%d - guardando el archivo...\n", opcion);
}


void salir(int opcion)
{
printf("%d - terminando el programa...\n", opcion);
}

void copiar(int opcion)
{
printf("%d - copiando el programa...\n", opcion);
}
