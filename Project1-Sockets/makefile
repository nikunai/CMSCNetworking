CC = gcc
CFAGS = -Wall -g -O2

client: client.c packet.h.gch
	$(CC) $(CFLAGS) client.c -o CLIENT packet.h

server: server.c packet.h.gch
	$(CC) $(CFLAGS) server.c -o SERVER packet.h

packet.h.gch: packet.h
	$(CC) $(CFLAGS) -c packet.h


clean:
	rm *~ *.h.gch -f SERVER CLIENT
