#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define READ 0
#define WRITE 1

int factorial(int a)
{
int i=0; int resultado=1;
for (i=2;i<=a; ++i)
resultado *=i;

return resultado;
}

int main(int argc, const char * argv[])
{
	
	int arreglo[2];
	pipe(arreglo);
	pid_t pid;
 	pid = fork();
	pid_t pid2;
	pid2=fork();
while(1)
{
	if(pid==0)
	{
	close(arreglo[WRITE]);
	
	}//hijo

	else 
	{
	close(arreglo[READ]);
	int num=0;
	scanf("%d", &num);
	write(arreglo[WRITE], &num, sizeof(num));

	}//padre Proceso 1

	if(pid2==0)
	{
	close(arreglo[WRITE]);
	int num=0;
	read(arreglo[READ], &num, sizeof (num));
	printf("\nSoy el hijo Proceso 2\n");
	printf("%d\n", factorial(num));
	}
	else 
	{
		close(arreglo[READ]);
	}//Fin de proceso 2
	
}

return 0;

}//Cierre de main
