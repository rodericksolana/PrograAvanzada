/*Rodrigo Solana Chao
ITESM CSF Ejercicio3.
con  -1  se sale del programa.
Programación Avanzada*/
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <sys/sem.h>
 #include <signal.h>


	int factorial(int a)
	{
	int i=0; int resultado=1;
	for (i=2;i<=a; ++i)
	resultado *=i;

	return resultado;
	}

int main(int argc, const char * argv[])
{

	key_t key; /* key to pass to semget() */ 
	int semflg; /* semflg to pass tosemget() */ 
	int nsems; /* nsems to pass to semget() */ 
	int semid; /* return value from semget() */ 

	int semnum; //selecciona un semaforo dentro de una matriz por su indice
	//int a=0;

	key =  1234;
	nsems = 2;
	semflg = IPC_CREAT | 0666;
	/*semget() inicializa o nos da acceso a un semaforo*/
	if ((semid = semget(key, nsems, semflg)) == -1) {
			perror("semget: semget failed"); 
			exit(1); } 
	else 
	printf("Semaforo correcto\n");


	while(semctl(semid, semnum, GETVAL, 0)!=-1)
	{

		if(semctl(semid, semnum+1, GETVAL, 0)==0)
{
		printf("%d\n",factorial(semctl(semid, semnum, GETVAL, 0))); //me regresa el valor del semaforo
		semctl(semid, semnum+1, SETVAL, 2);
}
		
	}//Cierre de while
	 	
	printf("Sali del while\n");

	return 0;

}//Cierre de main

