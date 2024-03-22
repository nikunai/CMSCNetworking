CC = gcc
CFAGS = -Wall -g -O2
SERVER_EXE = SERVER
CLIENT_EXE = CLIENT

client: client.c packet.h.gch grades.h.gch
	$(CC) $(CFLAGS) client.c -o $(CLIENT_EXE) packet.h grades.h

server: server.c packet.h.gch grades.h.gch
	$(CC) $(CFLAGS) server.c -o $(SERVER_EXE) packet.h grades.h

packet.h.gch: packet.h
	$(CC) $(CFLAGS) -c packet.h

grades.h.gch: grades.h
	$(CC) $(CFLAGS) -c grades.h

VSER: server
	valgrind ./$(SERVER_EXE)

VCLI: client
	valgrind ./$(CLIENT_EXE)

RSER: server
	./$(SERVER_EXE)

RCLI: client
	./$(CLIENT_EXE)	



clean:
	rm *~ *.h.gch -f vgcore.*  SERVER CLIENT
