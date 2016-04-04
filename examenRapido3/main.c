#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#define TIEMPO 3
#define PATH "datos"
#define N 50
char * buffer[20];
FILE *fp= NULL;
int grabar =0;
void gestor(int s)
{
    printf("Se manda llamar la alarma, no está bloqueada.\n");
grabar = 0;
}

void carpetaDir(void)
{
int status;
DIR* dir = opendir(PATH);
if (dir)
{
    printf(" Directory exists. \n");
borraContenido();
   closedir(dir);

}
else if (ENOENT == errno)
{
    printf(" Directory does not exist. \n");
	mkdir(PATH, 0777);

}
else
{
    printf(" opendir() failed for some other reason. \n");
}

}//Cierre de creaCarpeta

void borraContenido(void)
{

 struct dirent *d;
        DIR *dir;
        char buf[256];
        dir = opendir(PATH);
        while(d = readdir(dir))
        {               
                sprintf(buf, "%s/%s", PATH, d->d_name);
                remove(buf);
        }


}


int main(int argc, const char * argv[])
{

sigset_t mask, pendientes;
sigfillset(&mask);
sigdelset(&mask, SIGALRM);
sigprocmask(SIG_SETMASK, &mask, NULL);
signal(SIGALRM, SIG_DFL);
alarm(2);
signal(SIGALRM, gestor);
carpetaDir();

int k = 0;
    while (k < 5)
    {
        printf("Creando archivo... (Bloqueando senales)\n");
        int sig;
        grabar = 1;
        sprintf(buffer, "./datos/a%d", k);
        k++;
        fp = fopen(buffer, "w+");
        //char unChar = 'x';
        alarm(TIEMPO);
        while(grabar){
           // fputc('x', fp);  //Aqui va lo que se quiere imprimir adentro de cada archivo
        }
        sigpending(&pendientes);
        for(sig=1; sig < NSIG; sig++)
        {
            if(sigismember(&pendientes, sig))
                fprintf(fp, "\nEstaba bloqueada: la senal %d\n", sig);
        }
        fclose(fp);
        
    }
    printf("Imprimiendo informacion ...\n\n");
                       system("ls -lh datos");
                       sigprocmask(SIG_UNBLOCK, &mask, NULL);
    
    return 0;


}//Cierre de main
