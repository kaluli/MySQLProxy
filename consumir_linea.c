#include "funciones.h"

char* consumir_linea(char* buffer){

        char *linea,*aux;

        linea=buffer;

        //busco linea
        if( (aux=strstr(*buffer,"\n")) == NULL)
                return NULL;

        //buffer apunta al comienzo de la siguiente linea
        *buffer = aux+1;

        //inserto caracter de fin de cadena donde estaba '/n'
        *aux=0;

        return linea;

}

