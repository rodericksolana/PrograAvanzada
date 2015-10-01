#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#define MSGSZ     20


	int factorial(int a)
	{
	int i=0; int resultado=1;
	for (i=2;i<=a; ++i)
	resultado *=i;

	return resultado;
	}

/*
 * Declare the message structure.
 */

typedef struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
} message_buf;


main()
{
int val=0;

    int msqid;
    key_t key;
    message_buf  rbuf;

    /*
     * Get the message queue id for the
     * "name" 1234, which was created by
     * the server.
     */
    key = 1234;

while(val!=-1)
{
    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    
    /*
     * Receive an answer of message type 1.
     */
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    /*
     * Print the answer.
     */
	val = atoi(rbuf.mtext);	
	//printf("%d\n", val);
	printf("%d\n", factorial(val));
}//Cierre de while
    exit(0);
}

