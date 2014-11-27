CC = gcc
CFLAGS = -g -Wall  
LDLIBS= -lpthread -lrt
TARGETS = final muestra

all: $(TARGETS)

final: main.c iniciarServidor.c atenderCliente.c handshake.c lee_escribe.c contar.c parser.c recuperarDatos.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)  

test: 
	./final -p 4000 -m 3306 -h 127.0.0.1

clean:	
	rm -f $(TARGETS) *.o *~ *.swp log 
