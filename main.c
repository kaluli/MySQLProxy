#include "funciones.h"
/* Final Computación II
Karina Pángaro 
Leg: 4835
Ing. Informática
18/11/14
*/

int main (int argc, char** const argv)
{	
	int fd, maxHilos,leido;
//	FILE * file;
	int file;
	struct sockaddr_in addr_cli;
	char buffer[256];
	socklen_t addrlen;
	pthread_t tid;
	cantHilos = 1;
	char * op_cortas = "f:p:m:h:k";
	char * puerto;
	char * puerto_mysql;
	char * host;
	char * archivo;
	char siguiente_opcion;
	static fs_t fs;
//	conf datosConf;

//        COPIAR(archivoconfig,"proxy.conf");

	memset(buffer, 0, sizeof buffer);
	memset(datosConexion.puerto,0,sizeof datosConexion.puerto);
//	memset(datosConf.puerto,0,sizeof datosConf.puerto);
//	memset(datosConf.puerto_mysql,0,sizeof datosConf.puerto_mysql);
//	memset(datosConf.host,0,sizeof datosConf.host);
	memset(fs.puerto,0,sizeof fs.puerto);
	memset(fs.host,0,sizeof fs.host);

	maxHilos = 200;

	while(1){
		siguiente_opcion = getopt(argc, argv, op_cortas);

		if (siguiente_opcion == -1)
			break; /* No hay más opciones. Rompemos el bucle */
		switch (siguiente_opcion)
		{
			case 'p' :
				puerto = optarg;
				break;
			case 'm':
				puerto_mysql = optarg;
				break;
			case 'h' :
				host = optarg;
				break;
			case 'f' :
				archivo = optarg;			
				file = open(archivo, O_RDONLY);
				if (file) {
					if ((leido = read(file,buffer,sizeof buffer)) > 0 ){		
//						puerto = recuperarDatos(buffer);	
					 	puerto = strtok(buffer,"puerto=");
						//strncpy(puerto, aux, sizeof puerto); 

			      			//puerto = strtok(buffer,"puerto=");
					}
				close(file);

				//strncpy(puerto, datosConf.puerto, sizeof datosConf.puerto); 
				//strncpy(puerto_mysql, datosConf.puerto_mysql, sizeof datosConf.puerto_mysql); 
//				strncpy(puerto, datosConf.puerto, datosConf.puerto); 
//				printf("PUERTO: %s", puerto);
//				printf("PUERTO_MY: %s", datosConf.puerto_mysql);
				}
				break;
			case 'k':
				puts(
                        "\n Uso del servidor proxy: \n"
			"[-p]	: Puerto del servidor proxy \n"
                        "[-m]	: Puerto por defecto MySQL (Escriba: grep port /etc/mysql/my.cnf) \n"
                        "[-h]	: Host de MySQL\n");
				break;	
		}
	}
	

	if ((semaforo = sem_open ("/semaforo", O_CREAT | O_RDWR, 0666, 1)) < 0)
		perror ("sem_open\n");

	//strncpy(datosConexion.puerto,puerto, sizeof datosConexion.puerto); 
	memcpy(datosConexion.puerto, puerto, sizeof datosConexion.puerto); 
	strncpy(fs.puerto,puerto_mysql, sizeof fs.puerto);
	strncpy(fs.host,host, sizeof fs.host);

	fd = iniciarServidor(datosConexion.puerto);
	// Aceptar los clientes

	while ((fs.sockdata = accept (fd, (struct sockaddr *) &addr_cli, &addrlen)) > 0)
	{
		if (cantHilos <= maxHilos) //datosConexion.concur
		{
			fs.addr_cli = addr_cli;
			pthread_create (&tid, NULL, (void*)atenderCliente, (void*)&fs);
			sem_wait(semaforo);
			cantHilos++;
			sem_post(semaforo);
		}
	}
	close (fd);

	return 0;
}	
