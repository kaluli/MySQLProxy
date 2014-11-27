#include "funciones.h"

int main(int argc, char **argv)
{
	mqd_t mq;
	struct mq_attr attr;
	int flag = 0;
	char buffer[MAX_SIZE];
	// inicializar los atributos de la cola 
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_SIZE;
	attr.mq_curmsgs = 0;

	mq = mq_open(COLA, O_CREAT | O_RDONLY, 0644, &attr);
	CHECK((mqd_t)-1 != mq);

	memset(buffer,0,sizeof buffer);

	do {
		/* recibe el mensaje */
		ssize_t leido;
		leido = 0;
		memset(buffer,0,sizeof buffer);
		leido = mq_receive(mq, buffer, MAX_SIZE, NULL);
		write(STDOUT_FILENO, buffer, leido);
	} while (!flag);

	CHECK((mqd_t)-1 != mq_close(mq));
	CHECK((mqd_t)-1 != mq_unlink(COLA));

	return 0;
}
