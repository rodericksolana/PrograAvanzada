#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define READ 0
#define WRITE 1


int main(int argc, const char * argv[])
{
	
	int arreglo[2];
	int arreglo2[2];
	int sum=0;
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
	sum+=num;
	if(num==0)
{
	printf("Este es el resultado  %d \n", sum);
	exit(0);
	
}
	}//hijo

	else 
	{
	close(arreglo[READ]);
	int num=0;
	scanf("%d", &num);
	write(arreglo[WRITE], &num, sizeof(num));
	if(num==0)
	exit(0);
	
	}//padre
}

return 0;

}//Cierre de main
