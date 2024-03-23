#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> //for the inet_addr()
#include <unistd.h> // for close()
#include "grades.h"
#include "md5.h"
#include "helperFunctions.h"

#define PORT 42069 //PORT for server
#define MAX_CONNECTION_BACKLOG 10 //how many connections listen will allow before it bounces
#define MAX_BUFFER_LENGTH 256 //This is the buffer such that the sent item will be injective.
#define ADDRESS "172.21.77.0" //this is the server address
#define IS_LOCAL_MACHINE 1
#define PROJECT_TYPE 3 // OPT 1: TO-DO Calender, OPT 2: Class Schedule, OPT 3: Managign Grades
#define SERVER_NAME "CMSC481 HOST"

int main(int argc,char *argv[]){
  int isConnected = -1;
  uint8_t hash = -1; 
  int fileDescriptor = -1;
  int connectionDescriptor = -1;
  int returnValue = -1;
  int length;
  int bytesReceived = 0;
  char buffer[MAX_BUFFER_LENGTH];
  struct Grades grades;
  memset(&grades, 0, sizeof(grades));
  memset(buffer, 0, sizeof(buffer));
  struct sockaddr_in serverAddress;
  //struct addrinfo hints, *res;
  
  if(argc < 3){
    printf("Please run again with format ./CLIENT <username> <password>\n");
    exit(1);
  } 


  fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  if(fileDescriptor < 0)
    {
    perror("socket() failed.");
    exit(1);
    }
  
  //USE THE addrinfo structs for ipv6, otherwise sockaddr_in should be fine

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

  //connect to server
  returnValue = connect(fileDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  if(returnValue < 0)
    {
      perror("Connect Failed");
      exit(1);
    }


  //Begin handshake, send username
  //send username
  returnValue = send(fileDescriptor, argv[1], MAX_BUFFER_LENGTH, 0);
  if(returnValue < 0)
    {
      perror("send() failed.");
      exit(1);	     
    }
  //receive the hash or if the username failed
  memset(buffer, '0', sizeof(char) * MAX_BUFFER_LENGTH);
  while(bytesReceived < MAX_BUFFER_LENGTH)
    {
      returnValue = recv(fileDescriptor, buffer ,MAX_BUFFER_LENGTH - bytesReceived, 0);
      if(returnValue < 0)
	{
	  perror("recv() failed.");
	  exit(1);
	}
      bytesReceived += returnValue;
      printf("%s, %d", buffer, bytesReceived);
    }

  //IF the username is found by host, proceed to send password
  if(strcmp(buffer, "400") == 0)
    {
      printf("ERROR 400, user not found");
      exit(1);
    }
  else //if the user is found
    {
      //sending password
      //memset(buffer, '0', sizeof(char) * MAX_BUFFER_LENGTH);
      concatenateString(buffer, argv[2]);
      printf("TO BE HASHED: %s\n", buffer);
      md5String(buffer, &hash);
      char* toBeDeleted = convert(&hash);
      strcpy(buffer, toBeDeleted);
      free(toBeDeleted);
      printf("HASH: %s\n", buffer); 
      //  actually sending the stuff
      returnValue = send(fileDescriptor, buffer, MAX_BUFFER_LENGTH, 0);
      if(returnValue < 0)
	{
	  perror("send() failed.");
	  exit(1);	     
	}

      //check to see if it was a good password
     memset(buffer, '0', sizeof(char) * MAX_BUFFER_LENGTH);
     bytesReceived = 0;
     while(bytesReceived < MAX_BUFFER_LENGTH)
       {
	 returnValue = recv(fileDescriptor, buffer ,MAX_BUFFER_LENGTH - bytesReceived, 0);
	 if(returnValue < 0)
	   {
	     perror("recv() failed.");
		exit(1);
	   }
	 bytesReceived += returnValue;
	 printf("%s, %d", buffer, bytesReceived);
       }

     if(strcmp(buffer, "200") == 0)
       {
	 isConnected = 1;
	 printf("Connected...\n");
       } else {
	 printf("Bad Password\n");
	 exit(1);
       } 
    }
  
  return 0;
}
