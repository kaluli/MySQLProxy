#include "funciones.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>



int iniciarServidor (char *puerto)
{
	int opc = 1, sfd;
	struct addrinfo Direccion,*res;
	int ret;
	char buffer[50];
	int pp = atoi(datosConexion.puerto);	

	/* Vamos a atender el servicio */
	bzero(&Direccion,sizeof (struct addrinfo));
	Direccion.ai_family = AF_UNSPEC; 
	Direccion.ai_socktype= SOCK_STREAM; //Puerto del servicio
	Direccion.ai_flags = AI_PASSIVE; //Se puede atender cualquier cliente

	printf("-- puerto: %s\n", datosConexion.puerto);

	sprintf( buffer, "%d", pp );   


	//if(getaddrinfo(NULL,datosConexion.puerto,&Direccion,&res)!=0){
	ret = getaddrinfo(NULL,buffer,&Direccion,&res);

	//printf("ret: %d\n", ret);
	
	//printf("ERROR: %s", gai_strerror(ret));
	//exit(EXIT_FAILURE);	
	do
	{
		sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sfd  < 0)
			continue;
		setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&opc,sizeof (opc));
		if (bind(sfd, res->ai_addr, res->ai_addrlen) != 0){
			perror("bind");
			exit(EXIT_FAILURE);
		}                 
	}while((res=res->ai_next)!=NULL);
	listen(sfd,10);
	return sfd;
}


