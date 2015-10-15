#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#define PATH "datos"
#define N 50
void gestor(int s)
{
    printf("Se manda llamar la alarma, no está bloqueada.\n");
}

void carpetaDir(void)
{
int status;
DIR* dir = opendir("mydir");
if (dir)
{
    printf(" Directory exists. \n");
borraContenido();
   closedir(dir);

}
else if (ENOENT == errno)
{
    printf(" Directory does not exist. \n");
	mkdir("mydir", 0777);

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
        dir = opendir("mydir");
        while(d = readdir(dir))
        {               
                sprintf(buf, "%s/%s", "mydir", d->d_name);
                remove(buf);
        }


}


int main(int argc, const char * argv[])
{

sigset_t mask;
sigfillset(&mask);
sigdelset(&mask, SIGALRM);
sigprocmask(SIG_SETMASK, &mask, NULL);
signal(SIGALRM, SIG_DFL);
alarm(2);
signal(SIGALRM, gestor);
carpetaDir();

while(1);
    
    return 0;


}//Cierre de main