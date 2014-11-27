#ifndef _FUNCIONES_H_
	#define _FUNCIONES_H_
	
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <ctype.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <netdb.h>
	#include <string.h>
	#include <errno.h>
	#include <stdlib.h>
	#include <pthread.h>
	#include <semaphore.h>
	#include <mqueue.h>
	#include "common.h" 

	int cantHilos;
	sem_t *semaforo;
	
	typedef struct DATOS{
		char puerto[16];
	} datos; 

	typedef struct conf{
		char* puerto;
		char puerto_mysql[16];
		char host[40];
	} conf; 


	typedef struct{
		char data[10240];
		float tiempo;
	}estadistica_t;
	

        typedef struct{
                char path[100];
                int sockdata;
		char puerto[16];
		char host[40];
                struct sockaddr_in addr_cli;
                socklen_t addrlen;
                char type;
		float inicio;
		clock_t fin;
        }fs_t;

	datos datosConexion;

	int iniciarServidor (char*);
	int parser(char*, int, int, fs_t*);
	int contar(int);
	void* atenderCliente (fs_t*);
	int handshake(int, int, fs_t*);
	int lee_escribe(int, int, int, fs_t*);
	char* recuperarDatos (char *);

#endif
