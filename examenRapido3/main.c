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
                printf(buf, "%s/%s", "mydir", d->d_name);
                remove(buf);
        }


/*
DIR* dp;
struct dirent* ep;
char* path = "mydir";

dp = opendir(path);
if (dp != NULL)
{
  printf("Dir content:\n");
  while(ep = readdir(dp))
  {
    printf("%s\n", ep->d_name);
   remove("prueba.txt");
system("rm ep->d_name");
  }
}
closedir(dp);
*/

}


int main(int argc, const char * argv[])
{

borraContenido();

sigset_t mask;
sigfillset(&mask);
sigdelset(&mask, SIGALRM);
sigprocmask(SIG_SETMASK, &mask, NULL);
signal(SIGALRM, SIG_DFL);
alarm(2);
signal(SIGALRM, gestor);
carpetaDir();
borraContenido();

while(1);
    
    return 0;


}//Cierre de main
