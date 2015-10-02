#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#define PATH "procesos.txt"
#define N 50

int main(int argc, char* argv[])
{
    int tiempo;
    DIR * directorio;
    struct dirent* in_file;
    FILE *fp= NULL, *lectura=NULL;
    char leeChar,  buffer[N];
    pid_t pid = 0, sid = 0;
	
    if ( argc != 2 )
    {
        

    printf( "usage: %s cuantosMinutos(int)\n", argv[0] );
    return 0;

    }
    else
    {
        if (atoi(argv[1]) > 0)
            tiempo = atoi(argv[1]);
        else
        {
            printf("Ingrese un numero como parametro\n");
            return 0;
        }
    }
	pid = fork();

	if (pid < 0)
	{
		printf("fork failed!\n");
		exit(1);
	}

	if (pid > 0)
	{
		// MATAR PROCESO PADRE
		exit(0);
	}
	umask(0); //mascara para archivos
	sid = setsid(); //ya es demonio
	if(sid < 0)
	{
		exit(1);
	}
	
	
	fp = fopen (PATH, "w+"); 


	while (1)
	{	
		
        fclose(fp);
        fp = fopen(PATH, "w+"); 
        directorio = opendir("/proc"); //volver a abrir el directorio
        while((in_file = readdir(directorio)))
        {
    if(atoi(in_file->d_name) > 0) //si es un numero ie. es un proceso
    {
        fprintf(fp, "PROCESO NUMERO: %s\n", in_file->d_name);
	        snprintf(buffer,N, "/proc/%s/status", in_file->d_name); 
        lectura = fopen(buffer, "r"); //abrir en modo solo lectura
	
        do{
            leeChar = fgetc(lectura);
            fputc(leeChar, fp);
        }while(leeChar!=EOF); //para copiar los contenidos del archivo
        
        fclose(lectura); //cerrar el archivo de status
    }//Cierre de if
        }//Cierre de while interno
        sleep(tiempo * 60); //ciclo en minutos

	}//Cierre de while
	return (0);
}//cierre de main




