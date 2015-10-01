/*Rodrigo Solana Chao
ITESM CSF Ejercicio2 Server
con  -1  se sale del programa.
Programación Avanzada
 Basado en tutorial
http://www.cs.cf.ac.uk/Dave/C/node27.html 
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     1 //Tamaño

int main(int argc, const char * argv[])
{
    int c;
    int shmid;
    key_t key;
    int *shm;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
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
     * Now put some things into the memory for the
     * other process to read.
     */
printf("shmid: %d \n" , shmid);
while (*shm != -1)
{
printf("Dame un numero: ");
scanf("%d",shm);

*(shm+1) = 1;
//printf("\nValor alterno: %d", *(shm+1));
}

*shm=0;
*(shm+1)=0;
shmdt (shm); //Separa el segmento de memoria
shmctl (shmid, IPC_RMID, 0); //Borra el segmento de memoria


    exit(0);
}
