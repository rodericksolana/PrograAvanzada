/*Rodrigo Solana Chao
ITESM CSF Ejercicio3.
con  -1  se sale del programa.
Programación Avanzada*/
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <sys/sem.h>
 #include <signal.h>

	int valor(int);

int main(int argc, const char * argv[])
{

	key_t key; /* key to pass to semget() */ 
	int semflg; /* semflg to pass tosemget() */ 
	int nsems; /* nsems to pass to semget() */ 
	int semid; /* return value from semget() */ 

	int semnum; //selecciona un semaforo dentro de una matriz por su indice
	int a=0;

	key =  1234;
	nsems = 2;
	semflg = IPC_CREAT | 0666;
	/*semget() inicializa o nos da acceso a un semaforo*/
	if ((semid = semget(key, nsems, semflg)) == -1) {
			perror("semget: semget failed"); 
			exit(1); } 
	else 
	printf("Semaforo correcto\n");

	while(a!=-2)
	{
		
		a=valor(a);
if(a==-1)
{
		
		semctl(semid, semnum+1, SETVAL, 1); //asigna un valor nuevo al semaforo 2
		semctl(semid, semnum, IPC_RMID, 0);
		exit(0);
		
}
else
{
		semctl(semid, semnum, SETVAL, a); //asigna un valor nuevo al semaforo
		printf("El valor es de : %d \n",semctl(semid, semnum, GETVAL, 0));
		semctl(semid, semnum+1, SETVAL, 0);
}
		
	}//Cierre de while


	return 0;

}//Cierre de main

	int valor(int a)
	{
		printf("Dame un numero:  ");
		scanf ("%d", &a);
		return a;
	}
