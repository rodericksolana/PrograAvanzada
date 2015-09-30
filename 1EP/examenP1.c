/*Rodrigo Solana Chao
ITESM CSF ExamenP1.
Programación Avanzada*/
#include <stdio.h>
#include<stdlib.h>
#define N 7
int i=0, aux=0;
int pT=0 , torT=0 , edT=0 , navT=0, modT=0;
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
	int simetrico;
	int periodo;
	int pisos;
	
} Edificio;

typedef struct{
	int *modal;
	int *diametroSup;
	int *diametroInf;
	int periodo;
	int pisos;
	
} Torre;

typedef struct{
	int modal;
	int periodo;
	char * tipoTecho;
	
} Nave;

typedef struct{
	Persona *empleado;
	Edificio *ed;
	Torre *tor;
	Nave *nav;
	char *fecha;
	char *hora;
	int tipo;
} Modelado;


void agregaP(Persona *, int);
void editarP(Persona *, int);
void borrarP(Persona *, int);
void agregaE(Edificio*);
void agregaT(Torre*);
void agregaNav(Nave*);
void agregaMod(Modelado *, Persona *, Edificio *, Torre *, Nave *, int , int );

void agregaEstructura(Persona *, Edificio *, Torre *, Nave *, Modelado *, int);

void imprimirEmpleados(Persona *, int);
void imprimirEd(Edificio *ed);
void imprimirNav(Nave *nav);
void imprimirMod(Modelado *mod);
int contador(Modelado *mod);
void salir(Modelado *, Persona *, Edificio *, Torre *, Nave *);

typedef void(* opcion_t3) (Persona *, int);

	int main(int argc, const char * argv[])
	{

	opcion_t3 * menu3=((opcion_t3*) malloc(N * sizeof(opcion_t3)));

	
	*(menu3)=agregaP;

	int opcion=-1;

	Persona *p;
	Torre *tor;
	Edificio *ed;
	Nave *nav;
	Modelado *mod;

	p=(Persona*)malloc(1*sizeof(Persona));
	tor=(Torre*)malloc(1*sizeof(Torre));
	ed=(Edificio*)malloc(1*sizeof(Edificio));
	nav=(Nave*)malloc(1*sizeof(Nave));
	mod=(Modelado*)malloc(1*sizeof(Modelado));
int op=0;
		while(opcion!=7)
	{

		printf("---Opciones---\n1-Ingresar Persona \n2-Generar una estructura \n3-Imprime \n4-Editar Persona \n5-Borrar Persona\n7-Salir\nEscoge tu opción:  ");

		scanf("%d", &opcion);
		if(opcion==1)
		{
	
	p = (Persona*)realloc(p, (pT+1) * sizeof(Persona));
	(*(menu3+opcion-1))( p, pT);
	pT++;
	}//Cierre if
		else if(opcion==2)
		{
	if(pT<1)
{
printf("Aun no hay empleados Registradas\n");
}
else
{
		imprimirEmpleados(p, pT);
		printf("Selecciona un empleado por su ID: ");
		scanf("%d", &aux);

		printf("Que tipo de estructura quieres? \n1.Edificio \n2.Torre \n3.Nave \nOpcion: ");
		scanf("%d", &op);

		if(op==1)
		{
		ed = (Edificio*)realloc(ed, (edT+1) * sizeof(Edificio));
		}
		else if(op==2)
		{
		tor = (Torre*)realloc(tor, (torT+1) * sizeof(Torre));
		}

		else if(op==3)
		{
		nav = (Nave*)realloc(nav, (navT+1) * sizeof(Nave));
		}
			printf("Voy a agregar una estructura\n");
			agregaEstructura(p, ed, tor, nav, mod, op);

		mod = (Modelado*)realloc(mod, (modT+1) * sizeof(Modelado));
		agregaMod(mod, p, ed, tor, nav, aux-1, op);
		modT++;

		}//Cierre de else
		}//Cierre de opcion 2
		else if(opcion==3)
		{

		//imprimirEd(ed);

		//imprimirTor(tor);
		//imprimirNav(nav);

		if(fork()==0)
		{
		imprimirMod(mod);
		}//Cierre de hijo
		else
		{
		wait(0);
		}//Padre
		//imprimirEmpleados(p, pT);

		}
		else if(opcion==4)
		{
		if(pT<1)
		{
		printf("Aun no hay Empleados Registrados\n");
		}
		else
		{
		imprimirEmpleados(p,pT);
		printf("Dame el ID de la persona que quieres editar: ");
		scanf("%d", &aux);
		editarP(p, aux-1);
		}//Cierre de else
		}//Cierre de else 4
		else if(opcion==5)
		{
		if(pT<1)
		{
		printf("Aun no hay Empleados Registrados\n");
		}
		else
		{
		imprimirEmpleados(p,pT);
		printf("Dame el ID de la persona que quieres Borrar: ");
		scanf("%d", &aux);
		borrarP(p, aux-1);
		}//Cierre de else

		}//Cierre de else 5

		else if(opcion==7)
		{
			free(menu3);
		salir(mod, p,ed,tor,nav);
free(p);
free(tor);
free(ed);
free(nav);
free(mod);

		exit(0);

		}//Cierre de SALIR
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
	printf("Dame la fecha nacimiento en este formato ejemplo 1989-02-04 :  ");
	scanf("%s",(p+c)->fechaNacimiento);  

	(p+c)->fechaIngreso = malloc(sizeof(char)*10);
	printf("Dame la fecha de Ingreso en este formato ejemplo 1989-02-04 :  ");
	scanf("%s",(p+c)->fechaIngreso);

	printf("Dame el salario: ");
	scanf("%f",(&(p+c)->salario));
	(p+c)->puesto = malloc(sizeof(char)*10);
	printf("Dame el puesto: ");
	scanf("%s",(p+c)->puesto);	
 	  
}//Cierre de funcion agregaP

void editarP(Persona *p, int c)
{
	printf("Dame el numero de nomina: ");
	scanf("%d",(&(p+c)->nomina)); //asigno memoria al arreglo de la estructura
	printf("Dame el nombre: ");
	scanf("%s",(p+c)->nombreP);
	printf("Dame el apellido: ");
	scanf("%s",(p+c)->apellido);	
	printf("Dame la fecha nacimiento en este formato ejemplo 1989-02-04 :  ");
	scanf("%s",(p+c)->fechaNacimiento);  
	printf("Dame la fecha de Ingreso en este formato ejemplo 1989-02-04 :  ");
	scanf("%s",(p+c)->fechaIngreso);
	printf("Dame el salario: ");
	scanf("%f",(&(p+c)->salario));
	printf("Dame el puesto: ");
	scanf("%s",(p+c)->puesto);	

}//Cierre de editar

void borrarP(Persona *p, int c)
{
(p+c)->nomina=0;
(p+c)->nombreP=NULL;
(p+c)->apellido=NULL;
(p+c)->fechaNacimiento=NULL;
(p+c)->fechaIngreso=NULL;
(p+c)->salario=0;
(p+c)->puesto=NULL;

}//Cierre de editar


void agregaEstructura(Persona *p, Edificio *ed, Torre *tor,  Nave *nav,  Modelado *mod, int op)
{

	if(op==1)
	{
	printf("Voy agregar Edificio\n");	

	agregaE(ed);
	edT++;
	//imprimirEd(ed);

	}//Cierre de opcion 1
	else if(op==2)
	{
	printf("Voy agregar Torre\n");
	agregaTor(tor);
	torT++;
	//imprimirTor(tor);

	}//Cierre de opcion 2-

	else if(op==3)
	{
	printf("Voy agregar Nave\n");
	agregaNav(nav);
	navT++;
	//imprimirNav(nav);

	}//Cierre de nave


}//Cierre de agregaEstructura

void agregaE(Edificio *ed)
{

printf("Cuantos pisos tiene el edificio?  ");
	int pis=0;

	scanf("%d", &(ed->pisos));
pis=ed->pisos;
	(ed+edT)->modal = malloc(sizeof(int)*pis); //asigno memoria al arreglo de la estructura

for(i=0; i<pis; ++i)
{
printf("Dame el modal del piso  %d : ", i+1);
	scanf("%d",(&(ed+edT)->modal+i));
}

printf("Es simetrico?\n1. SI\n0. NO \nOpcion: ");
	scanf("%d",(&(ed+edT)->simetrico));
printf("Dame el periodo : ");
	scanf("%d",(&(ed+edT)->periodo));

}//Cierre de agrega Edificio

void agregaTor(Torre *tor)
{
int pis=0;
printf("Cuantos pisos tiene la Torre?  ");

	scanf("%d", &(tor->pisos));
pis=tor->pisos;
	(tor+torT)->modal = malloc(sizeof(int)*pis); //asigno memoria al arreglo de la estructura

for(i=0; i<pis; ++i)
{
printf("Dame el modal del piso  %d : ", i+1);
	scanf("%d",(&(tor+torT)->modal+i));
printf("Dame el diametroSup del piso  %d : ", i+1);
	scanf("%d",(&(tor+torT)->diametroSup+i));

printf("Dame el diametroInf del piso  %d : ", i+1);
	scanf("%d",(&(tor+torT)->diametroInf+i));
}//Cierre de for

printf("Dame el periodo : ");
	scanf("%d",(&(tor+torT)->periodo));

}//Agrega tor

void agregaNav(Nave *nav)
{

printf("Dame el modal : ");
	scanf("%d",(&(nav+navT)->modal));

printf("Dame el periodo : ");
	scanf("%d",(&(nav+navT)->periodo));

(nav+navT)->tipoTecho = malloc(sizeof(char)*10); //asigno memoria al arreglo de la estructura

printf("Dame el tipo de techo : ");
	scanf("%s",(nav+navT)->tipoTecho);
}//Cierre de agrega Nave



		void agregaMod(Modelado *mod, Persona *p, Edificio *ed, Torre *tor, Nave *nav, int idP, int op)
		{

		(mod+modT)->empleado = malloc(sizeof(Persona) * (1));
		*((mod+modT)->empleado)=*(p+idP);

	if(op==1)
	{
	//printf("Voy agregar Edificio\n");	
		(mod+modT)->ed = malloc(sizeof(Edificio) * (1));
		*((mod+modT)->ed)=*(ed+(edT-1));
	}//Cierre de opcion 1
	else if(op==2)
	{
	//printf("Voy agregar Torre\n");
	
		(mod+modT)->tor = malloc(sizeof(Torre) * (1));
		*((mod+modT)->tor)=*(tor+(torT-1));

	}//Cierre de opcion 2-

	else if(op==3)
	{
	//printf("Voy agregar Nave\n");
	
		(mod+modT)->nav = malloc(sizeof(Nave) * (1));
		*((mod+modT)->nav)=*(nav+(navT-1));
	}//Cierre de nave
	
	(mod+modT)->fecha = malloc(sizeof(Persona) * 15);
		printf("Dame la fecha de Modelacion en este formato ejemplo 1989-02-04 : ");
scanf("%s", (mod+modT)->fecha);

	(mod+modT)->hora = malloc(sizeof(Persona) * 10);
printf("Dame la hora de Modelacion en este formato Ejemplo 15:35  -  ");
		scanf("%s", (mod+modT)->hora);
	(mod+modT)->tipo=op;


		}//Cierre de agregarMod




void imprimirEmpleados(Persona *p, int c)
{

	 printf("Displaying Information Empleados:\n");
	   for(i=0;i<c;++i)
	{

		printf("ID: %d  Nomina: %d\tEmpleado: %s  %s\tfechaNacimiento: %s\tfechaIngreso: %s\tsalario :%f \tpuesto: %s \n",   i+1, (p+i)->nomina, (p+i)->nombreP, (p+i)->apellido, (p+i)->fechaNacimiento, (p+i)->fechaIngreso, (p+i)->salario, (p+i)->puesto);

	}//Cierre de for

}//Cierre imprimir empleados

/*
void imprimirEd(Edificio *ed)
{

	 printf("Displaying Information Edificio:\n");
	   for(i=0;i<edT;++i)
	{
	
	printf("ID: %d  Modal: %d\tSimetrico: %d \tPeriodo: %d\n", i+1, (ed+i)->modal, (ed+i)->simetrico, (ed+i)->periodo);

	}//Cierre de for
	
}//Cierre imprimir edificio

void imprimirTor(Torre *tor)
{

	 printf("Displaying Information Torres:\n");
	   for(i=0;i<torT;++i)
	{
	
	printf("ID: %d  Modal: %d\tDsup: %d \tDinf: %d \tPeriodo: %d\n", i+1, (tor+i)->modal, (tor+i)->diametroSup, (tor+i)->diametroInf, (tor+i)->periodo);
	}//Cierre de for
	
}//Cierre imprimir Torre

void imprimirNav(Nave *nav)
{

	 printf("Displaying Information Naves:\n");
	   for(i=0;i<navT;++i)
	{
	
	printf("ID: %d  Modal: %d\tPeriodo: %d\tTipo Techo: %s\n", i+1, (nav+i)->modal,(nav+i)->periodo, (nav+i)->tipoTecho);
	}//Cierre de for
	
}//Cierre imprimir Nav
*/

void imprimirMod(Modelado *mod)
{

if(modT<1)
{
printf("Aun no hay Modelos existentes\n");
}
else
{
Modelado *mod2=mod;
int contador=0;
char *inicio;
inicio = malloc(sizeof(char)*10);
printf("Dame una fecha de inicio: ");
scanf("%s", inicio);
char *final;
final = malloc(sizeof(char)*10);
printf("Dame una fecha final: ");
scanf("%s", final);



int j=0;
	 printf("\nDisplaying Information Modelado:\n");
	   for(i=0;i<modT;++i)
{

if(strcmp(inicio, (mod+i)->fecha)<=0 && strcmp((mod+i)->fecha, final)<=0)
{
	
	printf("Nomina: %d \tNombre: %s  %s\tFecha Nacimiento: %s\tFecha Ingreso: %s\tSalario: %f\tPuesto: %s\n", (mod+i)->empleado->nomina, (mod+i)->empleado->nombreP, (mod+i)->empleado->apellido, (mod+i)->empleado->fechaNacimiento, (mod+i)->empleado->fechaIngreso, (mod+i)->empleado->salario, (mod+i)->empleado->puesto);
	if((mod+i)->tipo==1)
{
	printf("Construccion Edificio\n");
	for(j=0; j<(mod+i)->ed->pisos;++j)
	printf("Piso %d\tModal: %d\n",j+1, (mod+i)->ed->modal+j);
	printf("Simetrico: %d\tPeriodo: %d\n", (mod+i)->ed->modal, (mod+i)->ed->simetrico, (mod+i)->ed->periodo, (mod+i)->ed->pisos);
	
}

	if((mod+i)->tipo==2)
{
	printf("Construccion Torre\n");
	for(j=0; j<(mod+i)->tor->pisos;++j)
	printf("Piso %d\tModal: %d\n",j+1, (mod+i)->tor->modal+j);
	printf("Diametro Sup: %d\tDiametro Inf: %d\tPeriodo: %d\n", (mod+i)->tor->diametroSup, (mod+i)->tor->diametroInf, (mod+i)->tor->periodo);

}
if((mod+i)->tipo==3)
{
	printf("Construccion Nave\n");
	printf("Modal: %d \tperiodo: %d\tTipo de Techo: %s\n", (mod+i)->nav->modal, (mod+i)->nav->periodo, (mod+i)->nav->tipoTecho);


}
printf("\n\n");
}//Cierre de if fecha
else printf("No se encontro nada entre esas fechas");
	}//Cierre de forPrincipal

}//Cierre de else
	
}//Cierre imprimir modelos


	int contador(Modelado *mod)
	{
	int contador=0;

	

	return contador;

	}//Cierre de contador



void salir(Modelado *mod, Persona *p, Edificio *ed, Torre *tor, Nave *nav)
{
int j=0; int k=0;
i=0;
Modelado *aux;  Modelado *final=mod+modT;
Persona *aux2;  Persona *final2=p+pT;
Edificio *aux3;  Edificio *final3=ed+edT;
Torre *aux4;  Torre *final4=tor+torT;
Nave *aux5;  Nave *final5=nav+navT;

for (aux = mod; aux < final; ++aux) {
	i++;
        free(aux->empleado);
	aux->empleado=NULL;
	free(aux->ed);
	aux->ed=NULL;
	free(aux->tor);
	aux->tor=NULL;
	free(aux->nav);
	aux->nav=NULL;
	free(aux->fecha);
	aux->fecha=NULL;
	free(aux->hora);
	aux->hora=NULL;
    }

printf("Borre Modelos %d veces\n", i);
/*
Persona *empleado;
	Edificio *ed;
	Torre *tor;
	Nave *nav;
	char *fecha;
	char *hora;
	int tipo;
*/
i=0;

for (aux2 = p; aux2 < final2; ++aux2) {
	i++;
        free(aux2->nombreP);
	aux2->nombreP=NULL;
	free(aux2->apellido);
	aux2->apellido=NULL;
	free(aux2->fechaNacimiento);
	aux2->fechaNacimiento=NULL;
	free(aux2->fechaIngreso);
	aux2->fechaIngreso=NULL;
	free(aux2->puesto);
	aux2->puesto=NULL;
    }

printf("Borre Personas %d veces\n", i);

i=0;
for (aux3 = ed; aux3 < final3; ++aux3) {
	i++;
	aux3->modal=NULL;
        free(aux3->modal);
	
    }
printf("Borre Edificio %d veces\n", i);

i=0;

for (aux4 = tor; aux4 < final4; ++aux4) {
	i++;
	aux4->diametroSup=NULL;
	free(aux4->diametroSup);
	aux4->diametroInf=NULL;
	free(aux4->diametroInf);
	
	
    }
printf("Borre Torre %d veces\n", i);

i=0;
for (aux5 = nav; aux5 < final5; ++aux5) {
	i++;
	aux5->tipoTecho=NULL;
        free(aux5->tipoTecho);

    }
printf("Borre NAVE %d veces\n", i);

}//Cierre de salir



