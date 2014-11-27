#include "funciones.h"
/*
	fd_lee: File descriptor de donde leerá
	fd_escribe: File descriptor de destino, escribirá
	Tipo
		0: handshake servidor
		1: handshake cliente
		2: consulta cliente
		3: respuesta servidor
*/

int lee_escribe(int fd_lee, int fd_escribe, int tipo, fs_t *fs){
	char buffer[BUFFER_SIZE];
	int leido=0;
	memset(buffer, 0, sizeof buffer);
	
/*	while ((leido = read(fd_lee, buffer, sizeof buffer)) > 0){
		printf("leido %d\n", leido);
		if(write(fd_escribe ,buffer, leido) < 0)
                        return -1;
		memset(buffer, 0, sizeof buffer);
	}
	if (leido < 0)
		return -1;
*/

	leido = read(fd_lee, buffer, sizeof buffer);
	write(fd_escribe, buffer, leido);
	parser(buffer, leido, tipo, fs);
	memset(buffer, 0, sizeof buffer);

	if (leido == 0)
		return -1;
	else
		return 0;

}
