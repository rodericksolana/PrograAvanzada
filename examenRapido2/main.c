#include <signal.h>
#include <stdio.h>
int c=0; 
int x=3;
int z=0;
int i=10; 
int s=0;
int j=1;
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
  
    pid_t pid = fork();
while(1)
{
    if(!pid)
    {
	for(;i>0;--i)
    {
        sleep(1);
        printf("%d segundo durmiendo\n",i);
    }
printf("soy el hijo y Desperté!");
s=1;


    kill(getpid(), SIGKILL); 
     
    
        
    }//Cierre hijo
    else
    {
        //padre
for(;j<=x;++j)
    {
        sleep(1);
        printf("%d segundo durmiendo\n",i);
    }
printf("Aparezco  %d  segundos", x);
j=1;
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
         if ( s==1 )//cambio el comportamiento para ignorar la señal
        {
        printf("Se presionó Ctrl C  %d  veces. y Ctrl Z  %d  veces.\n", c , z); 
         }
       
        
    }//Cierre padre
}//Cierre de while
    
    return 0;
}
