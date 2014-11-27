#include "funciones.h"

char* buscar_valor(const char * donde, const char* que){

        char* aux;

        aux = strstr(donde,que);

        if (aux!=NULL){
                return aux+strlen(que);
        }
	else{
                return NULL;
        }

}

        
