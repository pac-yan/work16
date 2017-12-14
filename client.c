#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  
  while (from_server){
    char *message = (char *)calloc(BUFFER_SIZE, sizeof(char));
    printf("Send message: ");
    fgets(message, BUFFER_SIZE, stdin);
    write(to_server, message, BUFFER_SIZE);
    read(from_server, message, BUFFER_SIZE);
    printf("Recieved: %s", message);
  }
}
