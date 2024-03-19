#include <sys/socket.h>

int main(int argc,char *argv[]){

  int fileDescriptor;

  //AF_INET: IP_v4
  //SOCK_STREAM: Full Duplex (read/write)
  //0: the default
  fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);


  
  return 0;
}
