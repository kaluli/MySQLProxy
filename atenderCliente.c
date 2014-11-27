#include "funciones.h"

void *atenderCliente (fs_t *fs)
{
	int fd_mysql;
	int fd_cliente = fs->sockdata;
	int leido;
	pthread_mutex_t sema = PTHREAD_MUTEX_INITIALIZER;
        struct sockaddr_in server={};
 	FILE *file = fopen("log", "a");
	char mensaje[100];
		
	memset(mensaje,0, sizeof mensaje);
	// El servidor es ahora cliente para el MySQL Server
	if ((fd_mysql = socket(AF_INET, SOCK_STREAM,0)) > 0){
		server.sin_family = AF_INET;
		server.sin_port = htons(atoi(fs->puerto)) ;//hton host to network
		inet_aton(fs->host, &server.sin_addr);// ascii to net
		if(connect(fd_mysql,(const struct sockaddr *) &server ,sizeof server) < 0){
			perror("socket()");
			return NULL;
		}
		leido = 0;
	 	fprintf(file, "\n Conectado desde: %s:%d ", inet_ntoa(fs->addr_cli.sin_addr), ntohs(fs->addr_cli.sin_port));
		fclose(file);

		//Handshake inicial inicial
		if (handshake(fd_mysql, fd_cliente, fs) < 0)
			snprintf(mensaje,18,"Falló el handshake");
		else
		{
			// handshake 0 y 1 - queries 2 y 3
			while (leido >= 0){
				leido = lee_escribe(fd_cliente, fd_mysql, 2, fs);
				lee_escribe(fd_mysql, fd_cliente, 3, fs);
			}
		}
		
		close (fd_cliente);
		close (fd_mysql);
		pthread_mutex_lock(&sema);
		cantHilos--;
		pthread_mutex_unlock(&sema);
		pthread_exit (NULL);
	}
	else{
		perror("socket()");
		exit(-1);
	}
	return NULL;
}
