CC = gcc
CFAGS = -Wall -g -O2
SERVER_EXE = SERVER
CLIENT_EXE = CLIENT

publish: client server
	cp SERVER ..
 
client: client.c packet.h.gch grades.h.gch helperFunctions.o connectionDescription.h.gch md5.o
	$(CC) $(CFLAGS) client.c -o $(CLIENT_EXE) packet.h grades.h helperFunctions.o connectionDescription.h md5.o

server: server.c packet.h.gch grades.h.gch helperFunctions.o connectionDescription.h.gch md5.o
	$(CC) $(CFLAGS) server.c -o $(SERVER_EXE) packet.h grades.h helperFunctions.o connectionDescription.h md5.o

packet.h.gch: packet.h
	$(CC) $(CFLAGS) -c packet.h

md5.o: md5.c md5.h
	$(CC) $(CFLAGS) -c md5.c

grades.h.gch: grades.h
	$(CC) $(CFLAGS) -c grades.h

connectionDescription.h.gch: grades.h
	$(CC) $(CFLAGS) -c connectionDescription.h

helperFunctiosn.o: helperFunctions.c helperFunctions.h
	$(CC) $(CFLAGS) -c helperFunctions.c

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
