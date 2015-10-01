/*Rodrigo Solana Chao
ITESM CSF Ejercicio2 Cliente
Programación Avanzada
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     1

int factorial(int a)
{
int i=0; int resultado=1;
for (i=2;i<=a; ++i)
resultado *=i;

return resultado;
}


int main(int argc, const char * argv[])
{
    int shmid;
    key_t key;
    int *shm;

    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 5678;

    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now read what the server put in the memory.
     */
while (*shm != -1)
{
if(*(shm+1)==1)
{
printf("%d\n", factorial(*shm));
*(shm+1)=0;
}
}

shmdt (shm);
shmctl (shmid, IPC_RMID, 0);
    exit(0);
}
