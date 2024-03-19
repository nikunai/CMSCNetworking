#include <sys/socket.h>

int main(int argc,char *argv[]){

  int fileDescriptor;
  fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);


  
  return 0;
}
