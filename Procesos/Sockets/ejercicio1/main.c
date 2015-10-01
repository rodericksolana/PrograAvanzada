

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define TCP_PORT 8000

int main(int argc, const char * argv[]) {
	int continuar=1;
pid_t pid;
    
    struct sockaddr_in direccion;
    char buffer[1000];
    
    int servidor, cliente;
    
    int leidos, escritos;
    
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    servidor = socket(PF_INET, SOCK_STREAM, 0);
    
    // Enlace con el socket
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Escuchar a los clientes
    listen(servidor, 10);
    
    // Comunicación
    socklen_t tamano = sizeof(direccion);


while(continuar)
{
    
    cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);
 
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
	
	pid=fork();
if(pid==0) continuar=0;

}//Cierre de while

if(pid==0)
{
	close (servidor);
if (cliente>=0)
{
// Leer de socket y escribir en pantalla
        while (leidos = read(cliente, &buffer, sizeof(buffer))) {
            write(fileno(stdout), &buffer, leidos);
            
            leidos = read(fileno(stdin), &buffer, sizeof(buffer));
            write(cliente, &buffer, leidos);
       }

}//Cierre if pid
    
    // Cerrar el socket
    
    close(servidor);
    close(cliente);
    
    return 0;
}
}
