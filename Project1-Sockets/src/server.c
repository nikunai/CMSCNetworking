#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> //for the inet_addr()
#include <unistd.h> // for close()
#include "grades.h"
#define PORT 42069 //PORT for server
#define MAX_CONNECTION_BACKLOG 10 //how many connections listen will allow before it bounces
#define MAX_BUFFER_LENGTH 256 //This is the buffer such that the sent item will be injective.
#define ADDRESS "172.21.77.0"
#define IS_LOCAL_MACHINE 1
#define PROJECT_TYPE 3 // OPT 1: TO-DO Calender, OPT 2: Class Schedule, OPT 3: Managign Grades
#define MAX_CONNECTIONS 32


void establishServer(int *fileDescriptor);
void acceptAndValidate(int* pipes, int *fileDescriptor, char* buffer);


int main(int argc,char *argv[]){
  int fileDescriptor = -1;
  int connectionDescriptor = -1;
  int returnValue = -1;
  int length;
  int pipes[MAX_CONNECTIONS];
  char buffer[MAX_BUFFER_LENGTH];
  struct Grades grades;
  memset(&grades, 0, sizeof(grades));
  memset(pipes, -1, sizeof(pipes));
  memset(buffer, 0, sizeof(buffer));
  
  establishServer(&fileDescriptor);
  
  
  /*
    Variable SETUP - THe following Block sets up the variables of the above
    length - the summation of the respective structs based on PROJECT_TYPE
    

   */
  switch(PROJECT_TYPE)
    {
    case 1:
      perror("Case 1 NOT Implemented");
      exit(1);
      break;
      
    case 2:
      perror("Case 2 NOT Implemented");
      exit(1);
    break;
    
    case 3:
    //Determine the length of the true buffer
      length = sizeof(grades._semester) + sizeof(grades._subject) + sizeof(grades._grade) + sizeof(grades._creditHour);
      break;
      
    default:
      perror("Check the constant PROJECT_TYPE: It is not set properly");
      exit(1);
    }

  

  
  while(1){
    acceptAndValidate(pipes, &fileDescriptor, buffer);


  //Set send receive loop here NOT YET IMPLEMENTED----------------------------------------------------------------------------------------------------

  //socket will wait for the entirety of the object to be sent over before it mvoes on. E.g, the sum of all of the structs primitives.
  returnValue = setsockopt(connectionDescriptor, SOL_SOCKET, SO_RCVLOWAT, (char*)&length, sizeof(length));
  if(returnValue < 0){
    perror("setsockopt(SO_RCVLOWAT) failed");
    exit(1);
  }
  
  //receive all data
  //Third param is the size of the buffer, not the length of receive.


  returnValue = recv(connectionDescriptor, buffer, sizeof(buffer), 0);
  if(returnValue < 0)
    {
      perror("bad recieve");
      exit(1);
    }
  printf(buffer);
      
  returnValue = send(connectionDescriptor, buffer, length, 0);
  if(returnValue < 0)
    {
      perror("bad send()");
      exit(1);
    }
  }

  
		    

 
  
  

  
  
  
  if(fileDescriptor != -1){
    close(fileDescriptor);
  }
  if(connectionDescriptor != -1){
    close(connectionDescriptor);
  }
			  
  
  
  
  return 0;
}


/*###########################################################################################################################*/
/*                                                                                                                           */
/*FUNCTION DEFS BELOW*FUNCTION DEFS BELOW* FUNCTION DEFS BELOW* FUNCTION DEFS BELOW* FUNCTION DEFS BELOW* FUNCTION DEFS BELOW*/
/*                                                                                                                           */
/*###########################################################################################################################*/




/* Name: establishServer */
/* DESC: This is the function that sets up a server to a socket */
/* Param: a passed by reference to the filedescriptor. */
void establishServer(int *fileDescriptor){
  struct sockaddr_in serverAddress;
  int returnValue = -1;
  
  //AF_INET: IP_v4
  //SOCK_STREAM: Full Duplex (read/write)
  //0: the default
  *fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if(*fileDescriptor < 0)
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
  
  returnValue = bind(*fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  if(returnValue < 0){
    perror("Bind() failed");
    exit(1);
  }

  
  //listens for incoming connectinos
  //pretty sure this behaves as opening and connecting the file descriptor
  //so this doesnt block, but rather sets the max connections that can be queued
  returnValue = listen(*fileDescriptor, MAX_CONNECTION_BACKLOG);
  if(returnValue < 0){
    perror("listen() failed.");
    exit(1);
  }


}



/* Name: acceptAndVerify */
/* DESC: accepts a new connection, and verifies whether it should be maintained */
/* Param: the array that contains all the client connections, file descriptor */ 
void acceptAndValidate(int* pipes, int* fileDescriptor, char* buffer){
  int connectionDescriptor = -1;
  int returnValue = -1;
  FILE *userFile = NULL;
  
  //Accepts incoming connectinos
  //this is a blocking function
  //so after listen opens the port, the accept will block until a connection comes in
  connectionDescriptor = accept(*fileDescriptor, NULL, NULL);
  if(connectionDescriptor < 0){
    perror("accept() failed");
    exit(1);
  }

  
  //Authentication here
  returnValue = recv(connectionDescriptor, buffer, sizeof(buffer), 0);
  if(returnValue < 0)
    {
      perror("bad recieve");
      exit(1);
    }
  printf(buffer);
  returnValue = send(connectionDescriptor, buffer, sizeof(buffer), 0);
  if(returnValue < 0)
    {
      perror("bad send()");
      exit(1);
    }

  userFile = fopen(buffer, "r");

  if(userFile != NULL)
    {
      /*promt for password */
      

    }
  else
    {
      printf("User Not Found");
    }
		     



  

  //as pipes was memset to -1, this should mean that either a, the pipe has been closed, or b that it has never been used.
  for(int i = 0; i < sizeof(pipes)/sizeof(int); i++){
    if(pipes[i] == -1){
      pipes[i] = connectionDescriptor;
    }

  }
}
