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
#define ADDRESS "172.21.77.0" //this is the server address
#define IS_LOCAL_MACHINE 1
#define PROJECT_TYPE 3 // OPT 1: TO-DO Calender, OPT 2: Class Schedule, OPT 3: Managign Grades
#define SERVER_NAME "CMSC481 HOST"

int main(int argc,char *argv[]){ 
  int fileDescriptor = -1;
  int connectionDescriptor = -1;
  int returnValue = -1;
  int length;
  char buffer[MAX_BUFFER_LENGTH];
  struct Grades grades;
  memset(&grades, 0, sizeof(grades));
  struct sockaddr_in serverAddress;
  //struct addrinfo hints, *res;


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


  //for testing only
  memset(buffer, '1', sizeof(buffer));
  returnValue = send(fileDescriptor, buffer, sizeof(buffer), 0);
  if(returnValue < 0)
    {
      perror("send() failed.");
      exit(1);	     
    }

  
  
  
  

  




  
  return 0;
}
