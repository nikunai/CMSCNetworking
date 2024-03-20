#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> //for the inet_addr()
#include "grades.h"
#define PORT 42069 //PORT for server
#define MAX_CONNECTION_BACKLOG 10 //how many connections listen will allow before it bounces
#define MAX_BUFFER_LENGTH 256 //This is the buffer such that the sent item will be injective.
#define ADDRESS "172.21.77.0"
#define IS_LOCAL_MACHINE 1

int main(int argc,char *argv[]){

  int fileDescriptor = -1;
  int connectionDescriptor = -1;
  int returnValue = -1;
  char buffer[MAX_BUFFER_LENGTH];
  struct Grades grades;
  memset(&grades, 0, sizeof(grades));
  struct sockaddr_in serverAddress;
  //AF_INET: IP_v4
  //SOCK_STREAM: Full Duplex (read/write)
  //0: the default
  
  fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if(fileDescriptor < 0)
    {
    perror("socket() failed");
    exit(1);
    }


  //Zero out the struct
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);

  if(IS_LOCAL_MACHINE)
    {
      serverAddress.sin_addr.s_addr = INADDR_ANY;
    }
  else
    {
      serverAddress.sin_addr.s_addr = inet_addr(ADDRESS);
    }

  
  //copies the constant INADDR_ANY to server address.
  //Basically, anything that is sent through port 13 will be readd

  
  // memcpy(&serverAddress.sin_addr, INADDR_ANY, sizeof(INADDR_ANY)); //CAUSES A SEG FAULT
  
  returnValue = bind(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  if(returnValue < 0){
    perror("Bind() failed");
    exit(1);
  }

  
  //listens for incoming connectinos
  //pretty sure this behaves as opening and connecting the file descriptor
  //so this doesnt block, but rather sets the max connections that can be queued
  returnValue = listen(fileDescriptor, MAX_CONNECTION_BACKLOG);
  if(returnValue < 0){
    perror("listen() failed.");
    exit(1);

  }
  
  //Accepts incoming connectinos
  //this is a blocking function
  //so after listen opens the port, the accept will block until a connection comes in
  connectionDescriptor = accept(fileDescriptor, NULL, NULL);
  if(connectionDescriptor < 0){
    perror("connect() failed");
    exit(1);
  }
  
  
  
  
  
  
  return 0;
}
