#include "funciones.h"
#include <time.h>

int contar(int tipo){

	float total = 0;
	
	switch (tipo){	//handshake
		case 2:
			total = clock();
			break;
		case 3:
			total = clock();
//			total = (float)(fin - inicio) / CLOCKS_PER_SEC;
			break;

		default: break;
	}

	return total;
}
