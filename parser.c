#include "funciones.h"
#include <time.h>

int parser(char* data, int longitud, int tipo, fs_t *fs){
	estadistica_t query;
	int i=0;
	FILE *file;
	struct tm *tm_p;
	time_t epoch_time;
	mqd_t mq;
	char buffer[BUFFER_SIZE];

	epoch_time = time( NULL );	
	tm_p = localtime( &epoch_time );

	memset(query.data, 0, sizeof query.data);

	while (i < longitud){
		if (isalnum(data[i]))
			query.data[i] = data[i];		
		else	
			query.data[i] = '-';
		i++;
	}

	if (query.data != NULL){
		file = fopen("log", "a");
		if(file==NULL) {
			perror("Error en file");
		}
		switch (tipo){	
			case 0: //handshake 

				fprintf(file, "\n Conectado: %s:%d - [%.2d:%.2d:%.2d] %s\n",
				inet_ntoa(fs->addr_cli.sin_addr), ntohs(fs->addr_cli.sin_port),tm_p->tm_hour, tm_p->tm_min, tm_p-> tm_sec,
						"Handshake -> Servidor");

				break;
			case 1:	//handshake
				fprintf(file, "\n Conectado: %s:%d - [%.2d:%.2d:%.2d] %s\n",
				inet_ntoa(fs->addr_cli.sin_addr), ntohs(fs->addr_cli.sin_port),tm_p->tm_hour, tm_p->tm_min, tm_p-> tm_sec,
						"Handshake -> Servidor");
				break;
			case 2: //cliente
				fprintf(file, "\n Conectado: %s:%d - [%.2d:%.2d:%.2d] %s\n",
				inet_ntoa(fs->addr_cli.sin_addr), ntohs(fs->addr_cli.sin_port),tm_p->tm_hour, tm_p->tm_min, tm_p-> tm_sec,
				"Consulta del Cliente");
				fprintf(file, "\n %s \n",query.data);
				fs->inicio = clock();
				//Cola de mensajes
				mq = mq_open(COLA, O_WRONLY | O_NONBLOCK);
				if (mq  > 0){
					memset(buffer, 0, sizeof buffer);
					snprintf(buffer,sizeof buffer,"\n\n Consulta del cliente: %s \n ", query.data);
					if (0 <= mq_send(mq, buffer, MAX_SIZE, 0)){
						mq_receive(mq, buffer, MAX_SIZE, NULL);
					}
					mq_close(mq);
				}
				break;

			case 3: //servidor
				fprintf(file, "\n Conectado: %s:%d - [%.2d:%.2d:%.2d] %s\n",
				inet_ntoa(fs->addr_cli.sin_addr), ntohs(fs->addr_cli.sin_port),tm_p->tm_hour, tm_p->tm_min, tm_p-> tm_sec,
				"Respuesta del Servidor");
				fprintf(file, "\n %s \n\n",query.data);
				fs->fin = clock();
				query.tiempo = (float)(fs->fin - fs->inicio) / CLOCKS_PER_SEC;
				fprintf(file, 
				"%s %f \n\n ******************************************************","Tiempo de demora: ", 
				query.tiempo);
				if (query.tiempo > 0)				
				{
					mq = mq_open(COLA, O_WRONLY | O_NONBLOCK);
					if (mq > 0){
						CHECK((mqd_t)-1 != mq);
						memset(buffer, 0, sizeof buffer);
						snprintf(buffer,sizeof buffer, "\n\n Respuesta cola de mensajes: %s \n\n Tiempo de demora: %f \n\n\n", 
						query.data, query.tiempo);
						if (0 <= mq_send(mq, buffer, MAX_SIZE, 0)){
							mq_receive(mq, buffer, MAX_SIZE, NULL);
						}

						mq_close(mq);
					}
				}
				break;


			default: break;
		}
	}
	fclose(file);
	return 0;

}

