/*Rodrigo Solana Chao
ITESM CSF Ejercicio2.
Programación Avanzada*/
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
#define M 2 //Numero de personas
#define N 7  //numero menu
#define X 2 //numero de preguntas
#define Y 3// numero de respuestas

int i=0;
typedef struct{
	
	char *nombreP;	
	char *apellido;
	int edad;
	
} Persona;



typedef struct{
	char *respuestas;	
	
} Respuestas;

typedef struct{
	
	char *preguntas;
	Respuestas *respuestas2;
	
} Preguntas;

typedef struct{

	Persona *participante;
	int *respU;
} Encuesta;



typedef void(* opcion_t) (Encuesta *, int);
typedef void(* opcion_t2) (Persona *, int);
typedef void(* opcion_t3) (Persona *, Encuesta *, Preguntas *, int, int, int);


void agregarPreguntas(Preguntas *, Respuestas *, int, int);
void agregarP(Persona *, int);
void salir(Persona *, Encuesta *, Preguntas *,Respuestas *,  int, int, int);
void agregarEncuesta(Persona *, Encuesta *, Preguntas *, int, int, int);
void imprimirP(Preguntas *, int, int);
void imprimirPersona(Persona *, int );
void imprimirRes(Encuesta *,int, int, int);

int main(int argc, const char * argv[])
{

	   opcion_t3 * menu3=((opcion_t3*) malloc(N * sizeof(opcion_t3)));


	*(menu3+2)=agregarEncuesta;
	//*(menu3+6)=salir;
	
	   int opcion=-1;
		Persona *p;
		Encuesta *e;
		Preguntas *pr;
		Respuestas *resp;

	   p=(Persona*)malloc(M*sizeof(Persona));
	   pr=(Preguntas*) malloc(X* sizeof(Preguntas));
	   e=(Encuesta*)malloc(M*sizeof (Encuesta));
	   resp=(Respuestas*)malloc(Y*sizeof (Respuestas));

	int numP=10; //numero de preguntas
	int numR=6; //numero de respuestas
	int par=0; int pre=0;
	   
	   
	while(opcion!=7)
	{

	//printf("Direccion en main %p\n",p);
		printf("---Opciones---\n1-Ingresar Preguntas\n2-Ingresar Participantes\n3-Realizar Encuesta\n7-Salir\nEscoge tu opción:  ");

		scanf("%d", &opcion);
		if(opcion==1)
		{
		pre++;
		agregarPreguntas(pr, resp, X,Y);
		
		}
		else if(opcion==2)
		{
		par++;
		agregarP(p,M);
		}
else if(opcion==7)
{
	salir(p, e, pr, resp,M ,M ,X );
}

	else if(par>0 && pre>0 && opcion==3)
{
	(*(menu3+opcion-1))(p, e, pr, M ,M, X);
}
else
printf("Necesitas agregar los Participantes o las Preguntas\n");


	}//Cierre de while

	//free(p);
	//free(e);
	
	//free(menu);
	//free(menu2);
	free(menu3);


	return 0;
}//Cierre de main


void agregarPreguntas(Preguntas *e, Respuestas *r, int a, int b)
{

	printf("Agregando Preguntas\n");
int i=0; int j=0;
	for(i=0;i<a;i++)
	{
	(e+i)->preguntas=malloc(sizeof(char)*30); //asigno memoria al arreglo de la estructura
	(e+i)->respuestas2=malloc(sizeof(Respuestas)*30);
	 	 

	if(i==0)
	{
	fflush( stdin );
	fgets ((e+i)->preguntas, 30, stdin);
	}//Parchando...
	printf("Dame la pregunta %d: ", i+1);
	fflush( stdin );
	fgets ((e+i)->preguntas, 30, stdin);
		for(j=0;j<Y;++j)
		{
		(r+j)->respuestas=malloc(sizeof(char)*30);
		printf("Dame la opción %d: ", j+1);
			fflush( stdin );
			fgets ((r+j)->respuestas, 30, stdin);

	*((e+i)->respuestas2+j)=*(r+j);
		}//Cierre de for j
	}//Cierre de for i
imprimirP(e,a,b);
}//cierre de agrega preguntas



void agregarP(Persona *p, int a)
{

	printf("Se van a agregar %d Personas\n", a);
int i=0; int correcto=1;
	for(i=0;i<a;++i)
{
	printf("Participante %d\n", i+1);
 	   (p+i)->nombreP = malloc(sizeof(char)*10); //asigno memoria al arreglo de la estructura
	   printf("Dame el nombre: ");
       	   scanf("%s",(p+i)->nombreP);
	   (p+i)->apellido = malloc(sizeof(char)*10);
	   printf("Dame el apellido: ");
           scanf("%s",(p+i)->apellido);	
correcto=1;
while(correcto!=0)
{  
      	   printf("Dame la edad: ");
      	   scanf("%d",&(p+i)->edad);
	if((p+i)->edad>17 && (p+i)->edad<120)
	correcto=0;
	else printf("No está en el rango de edad\n");
}
}//Cierre de for
	   imprimirPersona(p,a);

}//Cierre de funcion jugar


void agregarEncuesta(Persona *p, Encuesta *e, Preguntas *pr, int a, int b, int c)
{
	srand((int) time(NULL));
	int i=0; int j=0;
	for (i=0;i<b;++i)
	{
	(e+i)->participante = malloc(sizeof(char)*10);

	*((e+i)->participante)= *(p+i);
for(j=0;j<X;++j)
{
(e+i)->respU = malloc(sizeof(int)*Y);
	*((e+i)->respU+j)=rand() % 100;
printf("Pregunta: %d R:%d\n",j+1,*((e+i)->respU+j));
}
	}

imprimirRes(e,M,X,Y);

}//Cierre de funcion agregarEncuesta


void imprimirP(Preguntas *e, int a, int b)
{
printf("Imprimiendo Preguntas\n");
int i=0; int j=0;
	for(i=0;i<a;++i)
	{
	 printf("%d: %s\n", i+1, (e+i)->preguntas);
	for(j=0;j<Y;++j)
{
	printf("Pregunta: %d Opcion:%d %s ",i+1 , j+1, (((e+i)->respuestas2+j)->respuestas));
}//Cierre de for j
	}//Cierre de for i

}//Cierre de imprimirP

void imprimirPersona(Persona *p, int a)
{
printf("Imprimiendo Personas\n");
int i=0;
	for(i=0;i<a;++i)
	{
	 printf("%d: Nombre: %s  %s\tedad: %d\n", i+1, (p+i)->nombreP, (p+i)->apellido, (p+i)->edad);

	}//Cierre de for

}//Cierre de imprimirP

void imprimirRes(Encuesta *e,int a,int b,int c)
{
printf("Voy a imprimir Resultados\n");
int i=0; int j=0; int k=0;
for (i=0;i<a;++i)
{


	for(j=0; j<b;++j)
{

printf("Pregunta: %d  ", j+1);
for(k=0; k<c;++k)
{
printf("Respuesta: %d   ", k+1);

}//Cierre de  k Y

}//Cierre de j X

}//Cierre de i M



}//Cierre de imprimirRes



void salir(Persona *p, Encuesta *e, Preguntas *pr, Respuestas *resp, int a, int b, int c)
{

	Encuesta *aux;
	Encuesta *final=e+b;
	Persona *aux2;
	Persona *final2=p+a;
	Preguntas *aux3;
	Preguntas *final3=pr+c;
	Respuestas * aux4;
	Respuestas *final4=resp+Y;
	
	int i=0; int k=0; int j=0;

	i=0;
	for (aux=e; aux<final;++aux)
	{

	i++;
		free(aux->participante);
		aux->participante=NULL;
		

	}//Cierre de for
	printf("Borre encuesta %d veces\n", i);

	i=0;
	for (aux2 = p; aux2 < final2; ++aux2) {
		i++;
		free(aux2->nombreP);
		free(aux2->apellido);
	    }
	printf("Borre Personas %d veces\n", i);


	i=0;
	for (aux3 = pr; aux3 < final3; ++aux3) {
		i++;
		free(aux3->preguntas);
		free(aux3->respuestas2);
	    }
	printf("Borre Preguntas %d veces\n", i);


	i=0;
	for (aux4 = resp; aux4 < final4; ++aux4) {
		i++;
		free(aux4->respuestas);
	    }

	for(j=0;j<X;++j)
{
free((e+i)->respU);
}
	printf("Borre Respuestas %d veces\n", i);
	free(p);
	free(e);
	free(pr);
	free(resp);
	


}//Cierre de funcion salir


