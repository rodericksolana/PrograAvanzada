/*Rodrigo Solana Chao
ITESM CSF ExamenP1.
Programación Avanzada*/
#include <stdio.h>
#include<stdlib.h>

#define N 7
int i=0;
typedef struct{
	int nomina;	
	char *nombreP;	
	char *apellido;
	char *fechaNacimiento;
	char *fechaIngreso;
	float salario;
	char *puesto;
	
} Persona;

typedef struct{
	int *modal;
	int  simetrico;
	int periodo;
	
} Edificio;

typedef struct{
	int *modal;
	int periodo;
	int diametro;
	
} Torre;

typedef struct{
	int modal;
	int periodo;
	int tipoTecho;
	
} Nave;

typedef struct{
	Persona empleado;
	Edificio ed;
	Torre tor;
	Nave nav;
	
	
} Modelado;


void agregaP(Persona *, int);

void agregaEstructura(Persona *, int, Edificio *, int, Torre *, int, Nave *, int, Modelado *, int);

void imprimirEmpleados(Persona *, int);


typedef void(* opcion_t3) (Persona *, int);

	int main(int argc, const char * argv[])
	{

	opcion_t3 * menu3=((opcion_t3*) malloc(N * sizeof(opcion_t3)));

	
	*(menu3)=agregaP;
int tamP=0 , tamTor=0 , tamEd=0 , tamNav=0, tamMod=0;

	int opcion=-1;
	Persona *p;
	Torre *tor;
	Edificio *ed;
	Nave *nav;
	Modelado *mod;

	p=(Persona*)malloc(1*sizeof(Persona));
	tor=(Torre*)malloc(1*sizeof(Torre));
	p=(Edificio*)malloc(1*sizeof(Edificio));
	p=(Nave*)malloc(1*sizeof(Nave));
	p=(Modelado*)malloc(1*sizeof(Modelado));
		while(opcion!=7)
	{

		printf("---Opciones---\n1-Ingresar Persona \n2-Generar una estructura\n7-Salir\nEscoge tu opción:  ");

		scanf("%d", &opcion);
		if(opcion==1)
		{
	
	
	p = (Persona*)realloc(p, (tamP+1) * sizeof(Persona));
	(*(menu3+opcion-1))( p, tamP);
	tamP++;
	}//Cierre if
else if(opcion==2)
{
	printf("Voy a agregar una estructura\n");
}//Cierre de opcion 2

	}//Cierre de while
	
	return 0;
	}//Cierre de main

void agregaP(Persona *p, int c)
{
	
	printf("Dame el numero de nomina: ");
	scanf("%d",(&(p+c)->nomina));
	(p+c)->nombreP = malloc(sizeof(char)*10); //asigno memoria al arreglo de la estructura
	printf("Dame el nombre: ");
	scanf("%s",(p+c)->nombreP);
	(p+c)->apellido = malloc(sizeof(char)*10);
	printf("Dame el apellido: ");
	scanf("%s",(p+c)->apellido);	

	(p+c)->fechaNacimiento = malloc(sizeof(char)*10);
	printf("Dame la fecha nacimiento en este formato ejemplo 04-Febrero-1989 :  ");
	scanf("%s",(p+c)->fechaNacimiento);  

	(p+c)->fechaIngreso = malloc(sizeof(char)*10);
	printf("Dame la fecha de Ingreso en este formato ejemplo 04-Febrero-1989 :  ");
	scanf("%s",(p+c)->fechaIngreso);

	printf("Dame el salario: ");
	scanf("%f",&(p+c)->salario);
	(p+c)->puesto = malloc(sizeof(char)*10);
	printf("Dame el puesto: ");
	scanf("%s",(p+c)->puesto);	
 	  

}//Cierre de funcion agregaP


void agregaEstructura(Persona *p, int pT, Edificio *ed, int edT, Torre *tor, int torT, Nave *nav, int navT, Modelado *mod, int modT)
{
	printf("Selecciona primero un empleado");
	imprimirEmpleados(p, pT);


}//Cierre de agregaEstructura


void imprimirEmpleados(Persona *p, int c)
{

int j=0;
	 printf("Displaying Information Empleados:\n");
	   for(i=0;i<c;++i)
	{

		printf("ID: %d  Nomina: %d\tEmpleado: %s  %s\tfechaNacimiento: %s\tfechaIngreso: %s\tsalario :%f \tpuesto: %s \n",   i+1, (p+i)->nomina, (p+i)->nombreP, (p+i)->apellido, (p+i)->fechaNacimiento, (p+i)->fechaIngreso, (p+i)->salario, (p+i)->puesto);

/*
printf("Nomina: %d\tEmpleado: %s  %s\tfechaNacimiento: %s\tfechaIngreso: %s\tsalario :%f \tpuesto: %s \n",(p+i)->paciente->nombreP, (h+i)->paciente->apellido, (h+i)->paciente->edad, (h+i)->paciente->telefono, i+1);
*/


	}//Cierre de for

}//Cierre imprimir pacientes

