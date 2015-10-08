#include <signal.h>
#include <stdio.h>
int c=0; 
int x=3;
int z=0;
int i=10; 
int s=0;
int j=1;
void valor(void)
{
s=1;
}
void gestor_ctrlc(int senial)
{
   
   c++;
   x++;

/*kill(getppid(), SIGKILL);
kill(getpid(), SIGKILL);    
*/

}

void gestor_ctrlz(int senial)
{
  z++;
if(x>1)
  x--;
}


int main(int argc, const char * argv[])
{
     if ( signal (SIGTSTP, SIG_IGN) == SIG_ERR )//cambio el comportamiento para ignorar la señal
    {
        printf("error crenado el manejador.\n");
        exit(-1); 
    }
if ( signal (SIGINT, SIG_IGN) == SIG_ERR )//cambio el comportamiento para ignorar la señal
    {
        printf("error crenado el manejador.\n");
        exit(-1); 
    }
  
  

    pid_t pid = fork();
while(1)
{
    if(!pid)
    {
	for(;i>=0;--i)
    {
if(i==0)
{
printf("soy el hijo y Desperté!");
    kill(getppid(), SIGUSR1); 
}
        sleep(1);
        printf("%d segundo durmiendo Hijo\n",i);
    }

    }//Cierre hijo
    else
    {
if ( signal (SIGINT, gestor_ctrlc) == SIG_ERR )//cambio el comportamiento para ignorar la señal
    {
       printf("Error en el gestor de señales.\n");
        exit(-1); 
    }

   if ( signal (SIGTSTP, gestor_ctrlz) == SIG_ERR )//cambio el comportamiento para ignorar la señal
    {
       printf("Error en el gestor de señales.\n");
        exit(-1); 
    }
        //padre
signal(SIGUSR1, valor);
  if ( s==1 )//cambio el comportamiento para ignorar la señal
        {
        printf("Se presionó Ctrl C  %d  veces. y Ctrl Z  %d  veces.\n", c , z); 
kill(getpid(), SIGKILL); 
         }

for(;j<=x;++j)
    {
        sleep(1);
        printf("%d segundo durmiendo Padre\n",j);
    }
printf("Aparezco  %d  segundos \n", x);
j=1;
   
       
       
        
    }//Cierre padre
}//Cierre de while
    
    return 0;
}
