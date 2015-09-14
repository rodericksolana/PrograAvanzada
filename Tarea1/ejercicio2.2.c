/*Rodrigo Solana Chao
ITESM CSF Ejercicio3.
Programación Avanzada*/
#include <stdio.h>
#include<stdlib.h>
#define N 6
int i=0;
typedef struct{
	
	char *nombreP;	
	char *apellido;
	int edad;
	char *telefono;
	//int cama;
	
	
} Persona;

typedef struct{

	Persona *paciente;
	int status;
	char *status2;
} Hospital;



typedef void(* opcion_t) (Hospital *, int);
typedef void(* opcion_t2) (Persona *, int);
typedef void(* opcion_t3) (Hospital *, Persona *, int, int);

void agregaP(Hospital *, Persona *, int, int);
void altaP(Hospital *, Persona *, int, int);
int contarCamasD(Hospital *, int);//regresa el numero de camas disponibles que hay
int contarCamasOcup(Hospital *, int);
void imprimirCamasOcu(Hospital *, int);
void imprimirCamasDisp(Hospital *, Persona *, int, int);
void imprimirCamas(Hospital *, Persona *, int, int);
void salir(Hospital *, Persona *, int, int);

int main(int argc, const char * argv[])
{

	   opcion_t * menu=((opcion_t*) malloc(N * sizeof(opcion_t)));
	   opcion_t2 * menu2=((opcion_t2*) malloc(N * sizeof(opcion_t2)));
	   opcion_t3 * menu3=((opcion_t3*) malloc(N * sizeof(opcion_t3)));

	int tamH=0;
	int tamP=0;
	*(menu3)=agregaP;
	*(menu3+1)=altaP;
	*(menu3+2)=imprimirCamasDisp;
	*(menu3+3)=imprimirCamas;
	*(menu3+4)=salir;
	*(menu3+5)=salir;
	   /**(menu)=agregarBarco;
	   *(menu2+1)=agregarPersona;
	   *(menu3+2)=relacionar;
	   *(menu3+3)=imprimir2;
	   
	*/
	   int opcion=-1;
	   int camas=5;
		Persona *p;
		Hospital *h;

	   h=(Hospital*)malloc(5*sizeof (Hospital));
	   p=(Persona*)malloc(1*sizeof(Persona));
	   
	while(opcion!=0)
	{

	//printf("Direccion en main %p\n",p);
		printf("---Opciones---\n1-Ingresar Paciente\n2-Alta Paciente\n3-ImprimirCamasDesocupadas\n4-ImprimirInformaciónCompleta\n5-Total de Camas Ocupadas y Desocupadas\n6-Salir\nEscoge tu opción:  ");

		scanf("%d", &opcion);
		if(opcion==1)
		{
	if(contarCamasD(h,camas)==0)
	{
		h = (Hospital*)realloc(h, (camas+5) * sizeof(Hospital));
	printf("Agregué más camas\n");
	camas+=5;
	}
	
	p = (Persona*)realloc(p, (tamP+1) * sizeof(Persona));
	(*(menu3+opcion-1))(h, p, camas, tamP);
	tamH++;
	tamP++;
	}//Cierre if anidado

	else if(opcion==2)
		{
	}//Cierre if anidado

	else
	(*(menu3+opcion-1))(h, p, camas, tamP);
	
	

	}//Cierre de while
	printf("---Opciones---\n1-Agregar Barco\n2-Agregar Persona\n3-Salir\n4-Copiar\nEscoge tu opción:  ");

	free(h);
	free(p);
	//free(menu);
	//free(menu2);
	free(menu3);

	printf("\n");

	return 0;
}//Cierre de main


void agregaP(Hospital *h, Persona *p, int a, int c)
{
	   int idC=0;
	   (p+c)->nombreP = malloc(sizeof(char)*10); //asigno memoria al arreglo de la estructura
	   printf("Dame el nombre: ");
       	   scanf("%s",(p+c)->nombreP);
	   (p+c)->apellido = malloc(sizeof(char)*10);
	   printf("Dame el apellido: ");
           scanf("%s",(p+c)->apellido);	  
	   //(p+a)->edad = malloc(sizeof(int)*10);
      	   printf("Dame la edad: ");
      	   scanf("%d",&(p+c)->edad);
	   (p+c)->telefono = malloc(sizeof(char)*10);
	   printf("Dame el telefono: ");
      	   scanf("%s",(p+c)->telefono);	
 	  
	int correcto=1;
	while(correcto!=0)
	{

	 imprimirCamasDisp(h,p,a,c+1);
		   printf("A que cama lo vas a asignar?  DAME EL ID:  ");
			scanf("%d", &idC);
			printf("Elejiste la cama  %d\n", idC);
		idC--;
	if(idC<=a && (h+idC)->status==0 )
	{
		(h+idC)->paciente = malloc(sizeof(Persona)* 5);
		*(h+idC)->paciente=*(p+c);
		(h+idC)->status=1;
		if((h+idC)->status==1)
		{
			(h+idC)->status2=("ocupada");
		correcto=0;//Cambio variable para salir de while
		}
	}//Cierre de if
	else 
		printf("Esa opcion no está disponible\n");
		//*((b+idB)->propietario+(b+idB)->ocupado2)=*(p+idP);
	}//Cierre de while
}//Cierre de funcion agregaP
	


void altaP(Hospital *h, Persona *p, int a, int c)
{

int idC=0;
int correcto=1;
printf("Dando de alta a paciente\n");

	while(correcto!=0)
	{

	 imprimirCamasOcu(h, a);
		   printf("Dame el id de la cama que quieres desocupar: ");
			scanf("%d", &idC);
			printf("Elejiste la cama  %d\n", idC);
		idC--;
	if(idC<=a && (h+idC)->status==1 )
	{
		//*(h+idC)->paciente=NULL;
		(h+idC)->status=0;
		if((h+idC)->status==0)
		{
			(h+idC)->status2=("Paciente dado de alta");
		correcto=0;//Cambio variable para salir de while
		}
	}//Cierre de if
	else 
		printf("Esa opcion no está disponible\n");
		//*((b+idB)->propietario+(b+idB)->ocupado2)=*(p+idP);
	}//Cierre de while


}//Cierre de altaP


void imprimirCamasDisp(Hospital *h, Persona *p, int a, int c)
{

	int j=0;
	 printf("Displaying Information Camas:\n");
	   for(i=0;i<a;++i)
	{
	if((h+i)->status==0)
	       printf("IDC: %d Status: %d Status2: %s \n",i+1, (h+i)->status, (h+i)->status2);

	}
}//Cierre de funcion imprimir

void imprimirCamas(Hospital *h, Persona *p, int a, int c)
{

	int j=0;
	 printf("Displaying Information Camas:\n");
	   for(i=0;i<a;++i)
	{

	       printf("IDC: %d Status: %d Status2: %s \n",i+1, (h+i)->status, (h+i)->status2);
	if((h+i)->status==1)
		printf("Paciente: %s  %s\tedad: %d\ttelefono: %s \n",(h+i)->paciente->nombreP, (h+i)->paciente->apellido, (h+i)->paciente->edad, (h+i)->paciente->telefono);
	}//Cierre de for
	
}//Cierre de funcion imprimir



int contarCamasD(Hospital *h, int a)
{

	int j=0;
	   for(i=0;i<a;++i)
	{
	if((h+i)->status==0)
	       j++;
	}//Cierre de for
	return j;

}//Cierre de numero camas Disponibles


int contarCamasOcup(Hospital *h, int a)
{

	int j=0;
	   for(i=0;i<a;++i)
	{
	if((h+i)->status==1)
	       j++;
	}//Cierre de for
	return j;

}//Cierre de numero camas Disponibles



void imprimirCamasOcu(Hospital *h, int a)
{

int j=0;
	 printf("Displaying Information Camas:\n");
	   for(i=0;i<a;++i)
	{
	if((h+i)->status==1)
{
	       printf("IDC: %d Status: %d Status2: %s \n",i+1, (h+i)->status, (h+i)->status2);
		printf("Paciente: %s  %s\tedad: %d\ttelefono: %s \n",(h+i)->paciente->nombreP, (h+i)->paciente->apellido, (h+i)->paciente->edad, (h+i)->paciente->telefono);
}//Cierre de if
	}//Cierre de for

}//Cierre de camas Ocup

void salir(Hospital *h, Persona *p, int a, int c)
{

	Hospital *aux;
	Persona *aux2;
	Hospital *final=h+a;
	Persona *final2=p+c;
	int i=0; int k=0;

	i=0;
	for (aux=h; aux<final;++aux)
	{

	i++;
		free(aux->paciente);

	}//Cierre de for
	printf("Borre hospital %d veces\n", i);

	i=0;
	for (aux2 = p; aux2 < final2; ++aux2) {
		i++;
		free(aux2->nombreP);
		free(aux2->apellido);
		free(aux2->telefono);
	    }
	printf("Borre Personas %d veces\n", i);

	free(h);
	free(p);

	exit(0);

}//Cierre de funcion salir


