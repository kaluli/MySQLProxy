#include "funciones.h"

int handshake (int fd_mysql, int fd_cliente, fs_t *fs) {
	
	if (lee_escribe(fd_mysql, fd_cliente, 0, fs) == -1)	// Lee del servidor SQL la forma de autenticación
		return -1;

	if (lee_escribe(fd_cliente, fd_mysql, 1, fs) == -1)	// Lee la respuesta del cliente con la forma de autenticación
		return -1;

	if (lee_escribe(fd_mysql, fd_cliente, 0, fs) == -1)	// Le envía al servidor SQL la autenticación del cliente
		return -1;

	if (lee_escribe(fd_cliente, fd_mysql, 1, fs) == -1)	// El cliente envía la versión del cliente que utiliza
		return -1;
	
	if (lee_escribe(fd_mysql, fd_cliente, 0, fs) == -1)	// El servidor acepta la petición
		return -1;

	return 0;
}
