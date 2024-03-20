#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORT 13 //PORT for server
#define MAX_CONNECTION_BACKLOG 10 //how many connections listen will allow before it bounces

int main(int argc,char *argv[]){

  int fileDescriptor = -1;
  int connectionDescriptor = -1;
  int returnVal = -1;
  struct sockaddr_in serverAddress;
  //AF_INET: IP_v4
  //SOCK_STREAM: Full Duplex (read/write)
  //0: the default
  
  fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if(fileDescriptor < 0){
    perror("socket() failed");
    exit(1);
  }

  //Zero out the struct
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(PORT);
  //copies the constant INADDR_ANY to server address.
  //Basically, anything that is sent through port 13 will be readd
  memcpy(&serverAddress.sin_addr, INADDR_ANY, sizeof(INADDR_ANY));
  returnValue = bind(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  if(returnValue < 0){
    perror("Bind() failed");
    exit(1);
  }

  returnValue = listen(fileDescriptor, MAX_CONNECTION_BACKLOG);
  if(returnValue < 0){
    perror("listen() failed.");
    exit(1);

  }
  

  connectionDescriptor = accept(fileDescriptor, NULL, NULL);
  if(connectionDescriptr < 0){
    perror("connect() failed");
    exit(1);
  }
  
  
  
  
  
  return 0;
}
