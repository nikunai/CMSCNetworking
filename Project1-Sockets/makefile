CC = gcc
CFAGS = -Wall -g -O2

client: client.h packet.h.gch
	$(CC) $(CFLAGS) -o CLIENT packet.h

server: server.h packet.h.gch
	$(CC) $(CFLAGS) -o server packet.h

packet.h.gch: packet.h
	$(CC) $(CFLAGS) -c packet.h


clean:
	rm *~ *.h.gch -f
