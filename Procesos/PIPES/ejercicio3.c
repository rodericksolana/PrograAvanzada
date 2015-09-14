#include <stdio.h>
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
	int arreglo2[2];
	pipe(arreglo);
	pipe(arreglo2);
	pid_t pid;
 	pid = fork();
while(1)
{
	if(pid==0)
	{
	close(arreglo[WRITE]);
	int num=0;
	read(arreglo[READ], &num, sizeof (num));
	printf("\nSoy el hijo\n");
	close (arreglo2[READ]);
	num=factorial(num);
	write(arreglo2[WRITE], &num, sizeof(num));
	
	}//hijo

	else 
	{

	close(arreglo[READ]);
	int num=0;
	scanf("%d", &num);
	write(arreglo[WRITE], &num, sizeof(num));
	close(arreglo2[WRITE]);
	read(arreglo2[READ], &num, sizeof (num));
	printf("\nSoy el padre imprimiendo\n");
	printf("%d\n", num);

	}//padre
}

return 0;

}//Cierre de main
