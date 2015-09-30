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
	nsems = 1;
	semflg = IPC_CREAT | 0666;
	/*semget() inicializa o nos da acceso a un semaforo*/
	if ((semid = semget(key, nsems, semflg)) == -1) {
			perror("semget: semget failed"); 
			exit(1); } 
	else 
	printf("Se creo el semaforo\n");

		pid_t pid;
	 	//pid = fork();
	 if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	    }

printf("pid antes de entrar:  %d", pid);


	while(1)
	{
	if (pid == 0)
	 { /* child */
		/*semctl(int semid, int semnum, int cmd, union semun arg); //permite realizar operaciones en el semaforo o cambiar cosas*/
		printf("%d\n",factorial(semctl(semid, semnum, GETVAL, 0))); //me regresa el valor del semaforo
		pid=1;
	 }

	else
	{
		int a=0;
		a=valor(a);
		semctl(semid, semnum, SETVAL, a); //asigna un valor nuevo al semaforo
		pid=0;
		if(a==-1)
		{
			semctl(semid, semnum, IPC_RMID, 0); //Elimino el semaforo
			kill(pid, SIGKILL);
		}
	}//Cierre de padre

	}//Cierre de while
	 	
	printf("Sali del while\n");

	return 0;

}//Cierre de main

	int valor(int a)
	{
		printf("Dame un numero:  ");
		scanf ("%d", &a);
		return a;
	}
