/*Rodrigo Solana Chao
ITESM CSF Ejercicio1.
Programación Avanzada*/
#include <stdio.h>
#include<stdlib.h>
#define N 5
int i=0;
typedef struct{
	int edad;
	char *nombreP;	
	char *apellido;
	char *rol;
	int status;
	
	
} Persona;

typedef struct
{
	char *nombreB;
	float eslora;
	float manga;
	int nMax;
	int ocupado;
	int ocupado2;
	Persona *propietario;
	Persona *tripulacion; 

} Barco;

typedef void(* opcion_t) (Barco *, int);
typedef void(* opcion_t2) (Persona *, int);
typedef void(* opcion_t3) (Barco *, Persona *, int, int);

int tamanioP(Persona *);
int tamanioB(Barco *);
void agregarBarco(Barco *, int);
void agregarPersona(Persona *, int);
void relacionar(Barco*, Persona *, int, int);
void imprimir(Barco *, int);
void imprimir2(Barco *, Persona *, int, int);
void salir(Barco *, Persona *, int, int);

int main(int argc, const char * argv[]){
   opcion_t * menu=((opcion_t*) malloc(N * sizeof(opcion_t)));
   opcion_t2 * menu2=((opcion_t2*) malloc(N * sizeof(opcion_t2)));
   opcion_t3 * menu3=((opcion_t3*) malloc(N * sizeof(opcion_t3)));
   
   Persona *p;
   Barco *b;

int tamB=0;
int tamP=0;

   *(menu)=agregarBarco;
   *(menu2+1)=agregarPersona;
   *(menu3+2)=relacionar;
   *(menu3+3)=imprimir2;
   *(menu3+4)=salir;
   int opcion=-1;

   b=(Barco*)malloc(1*sizeof(Barco));
   p=(Persona*)malloc(1*sizeof(Persona));
   
while(opcion!=0)
{

//printf("Direccion en main %p\n",p);
	printf("---Opciones---\n1-Agregar Barco\n2-Agregar Persona\n3-Relacionar\n4-Imprimir\n5-Salir\nEscoge tu opción:  ");

	scanf("%d", &opcion);
	if(opcion==1)
	{
	b = (Barco*)realloc(b, (tamB+1) * sizeof(Barco));
	(*(menu+opcion-1))(b, tamB);
//printf("Aumente el tamB");
tamB++;
	}else if (opcion==2)
	{
	p = (Persona*)realloc(p, (tamP+1) * sizeof(Persona));
	//printf("Direccion en funcion despues de realloc %p\n",p);
	(*(menu2+opcion-1))(p, tamP);
tamP++;
	}
	else
	(*(menu3+opcion-1))(b, p, tamB, tamP);

}//Cierre de while
printf("---Opciones---\n1-Agregar Barco\n2-Agregar Persona\n3-Salir\n4-Copiar\nEscoge tu opción:  ");

//free(p);
//free(b);
free(menu);
free(menu2);
free(menu3);
	return 0;
}//Cierre de main

void agregarBarco(Barco *b, int a)
{
	int aux=0;
	
	   (b+a)->nombreB = malloc(sizeof(char)*10); //asigno memoria al arreglo de la estructura
	   printf("Dame el nombre: ");
           scanf("%s",(b+a)->nombreB);
	   printf("Dame la eslora: ");
	   scanf("%f",&(b+a)->eslora);
	   printf("Dame la manga: ");
	   scanf("%f",&(b+a)->manga);
	   printf("Dame la capacidad max: ");
	   (b+a)->propietario = malloc(sizeof(Persona)* 1);
	   (b+a)->propietario->nombreP = malloc(sizeof(char)*10);
	   scanf("%d",&(b+a)->nMax);
	   aux=(b+a)->nMax;
	   (b+a)->tripulacion = malloc(sizeof(Persona) * (aux));

}//Cierre de funcion agregarBarco


void agregarPersona(Persona *p, int a)
{
	
	   (p+a)->nombreP = malloc(sizeof(char)*10); //asigno memoria al arreglo de la estructura
	   printf("Dame el nombre: ");
       	   scanf("%s",(p+a)->nombreP);
	   (p+a)->apellido = malloc(sizeof(char)*10);
	   printf("Dame el apellido: ");
           scanf("%s",(p+a)->apellido);	  
	   //(p+a)->edad = malloc(sizeof(int)*10);
      	   printf("Dame la edad: ");
      	   scanf("%d",&(p+a)->edad);
	   (p+a)->rol = malloc(sizeof(char)*10);
	   printf("Dame el rol: ");
      	   scanf("%s",(p+a)->rol);
}//Ciere de funcion agregaP

void relacionar(Barco *b, Persona *p, int a, int c)
{
int idB=0; int idP=0; int opcion=0;
if(a>0)
{
printf("Quieres agregar: 1->propietario 2->tripulante:  ");
scanf("%d",&opcion);

if(opcion==1)
{
printf("A que barco quieres adicionar un propietario?\n");
imprimir(b,a);
printf("Dame el Id del barco:  ");
scanf("%d", &idB);
idB--;

for(i=0;i<c;++i)
{	
	if((p+i)->status==0 && strcmp((p+i)->rol, ("propietario"))==0)
{
       printf("ID - %d\t%s\t%s\t%d\t%s\t%d\n",(i+1),(p+i)->nombreP,(p+i)->apellido,(p+i)->edad,(p+i)->rol,(p+i)->status);
}//Cierre de if
}//Cierre de for

if(c>0)
{
printf("Dame el Id de la Persona:  ");
scanf("%d", &idP);
idP--;
(p+idP)->status=1;
*((b+idB)->propietario+(b+idB)->ocupado2)=*(p+idP);
(b+idB)->ocupado2++;
printf("Esto vale ocupado2.. %d",(b+idB)->ocupado2);

}//Ciere de if
else 
printf("Aun no hay personas");

}//Cierre de if propietario

else
{

printf("A que barco quieres adicionar un tripulante?\n");
imprimir(b,a);
printf("Dame el Id del barco:  ");
scanf("%d", &idB);
idB--;

if((b+idB)->ocupado < (b+idB)->nMax)
{
 printf("Personas:\n");
   for(i=0;i<c;++i)
{	
	if((p+i)->status==0 && strcmp((p+i)->rol, ("propietario"))!=0)
{
       printf("ID - %d\t%s\t%s\t%d\t%s\t%d\n",(i+1),(p+i)->nombreP,(p+i)->apellido,(p+i)->edad,(p+i)->rol,(p+i)->status);
}//Cierre de if
}//Cierre de for

if(c>0)
{
printf("Dame el Id de la Persona:  ");
scanf("%d", &idP);
idP--;
(p+idP)->status=1;
*((b+idB)->tripulacion+(b+idB)->ocupado)=*(p+idP);
(b+idB)->ocupado++;
}//Ciere de if
else 
printf("Aun no hay personas");

}//Cierre de if
else
printf("No hay espacio disponible en el barco...\n");
}
}//Cierre de else propietario y tripulacion
else //Cierre de else Principal
printf("No hay ningun barco en el puerto...\n");
}//Cierre de funcion relacionar

/*
int tamanioP(Persona *p)
{
Persona *aux2 =p;
while((aux2)->rol!= '\0')
aux2++;
//printf("LLevo %d personas", aux2-p);
return (aux2-p);

}//Cierre de funcion tamanioP

int tamanioB(Barco *b)
{
Barco *aux2 =b;
while((aux2)->nombreB!= '\0')
aux2++;

return aux2-b;

}//Cierre de funcion tamanioB
*/

void imprimir(Barco *b, int a)
{
int j=0;
 printf("Displaying Information Barcos:\n");
   for(i=0;i<a;++i)
       printf("ID: %d Barco:%s\t%f\t%f\tLugares Disponibles: %d\n",i+1,(b+i)->nombreB, (b+i)->eslora,(b+i)->manga,((b+i)->nMax-(b+i)->ocupado));

}//Cierre de funcion imprimir

void imprimir2(Barco *b, Persona *p, int a, int c)
{
int j=0;
 printf("Displaying Information Barcos:\n");
   for(i=0;i<a;++i)
{
       printf("\nID: %d Barco: %s\teslora: %f\tmanga%f\tLugares Disponibles: %d\n",i+1,(b+i)->nombreB, (b+i)->eslora,(b+i)->manga,((b+i)->nMax-(b+i)->ocupado));
for (j=0;j<(b+i)->ocupado2;++j)
{
if((b+i)->propietario->status==1) 
{
	printf("Propietario:\n%s\t%s\tedad: %d años\trol: %s\t%d\n",((b+i)->propietario+j)->nombreP, ((b+i)->propietario+j)->apellido,((b+i)->propietario+j)->edad,((b+i)->propietario+j)->rol,((b+i)->propietario+j)->status);
}//Cierre de if propietario
}//Cierre de for
	for (j=0;j<(b+i)->ocupado;++j)
{

if((b+i)->tripulacion->status==1)
	printf("Tripulacion:\n%s\t%s\tedad: %d años\trol: %s\t%d\n",((b+i)->tripulacion+j)->nombreP, ((b+i)->tripulacion+j)->apellido,((b+i)->tripulacion+j)->edad,((b+i)->tripulacion+j)->rol,((b+i)->tripulacion+j)->status);
}//Cierre interno
}//Cierre de for
}//Cierre de funcion imprimir

void salir(Barco *b, Persona*p, int a, int c)
{
Barco *aux;
Persona *aux2;
Barco *final=b+a;
Persona *final2=p+c;
int j=0; int k=0;
i=0;

for (aux = b; aux < final; ++aux) {
	i++;
        free(aux->propietario);
	aux->propietario=NULL;
	free(aux->nombreB);
	aux->nombreB=NULL;
	free(aux->tripulacion);
	aux->tripulacion=NULL;
    }

printf("Borre Barcos %d veces\n", i);
i=0;

for (aux2 = p; aux2 < final2; ++aux2) {
	i++;
        free(aux2->nombreP);
	aux2->nombreP=NULL;
        free(aux2->apellido);
	aux2->apellido=NULL;
	free(aux2->rol);
	aux2->rol=NULL;
    }
printf("Borre Personas %d veces\n", i);

free(b);
free(p);
exit(0);
}

