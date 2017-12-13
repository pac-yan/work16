#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  while (from_client){
    char *message = (char *)calloc(BUFFER_SIZE, sizeof(char));
    read(from_client, message, BUFFER_SIZE);
    strcat(message, " is very nice");
    write(to_client, message, BUFFER_SIZE);
  }
}
