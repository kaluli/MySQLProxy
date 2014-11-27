#include "funciones.h" 

char* recuperarDatos (char *buffer){

	char buff[256];
	char *aux;
	
	memset (buff, 0, sizeof buff);

	aux = buffer;
        aux = strtok(aux,"puerto=");
//        strcpy(datosConf.puerto,aux);

/*        aux = strtok(NULL,"puerto=");	
        strcpy(datosConf.puerto_mysql,aux);
	
        aux = strtok(NULL,"host=");	
        strcpy(datosConf.host,aux);
*/
	
	return aux;
}
