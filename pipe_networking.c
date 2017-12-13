#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  if (mkfifo(ACK, 0600))
    printf("Server error: %s\n", strerror(errno));

  int from_client = open(ACK, O_RDONLY, 0600);
  remove(ACK);

  //opening private fifo
  char *fifo_name = (char *)calloc(BUFFER_SIZE, sizeof(char));
  read(from_client, fifo_name, BUFFER_SIZE);
  *to_client = open(fifo_name, O_WRONLY, 0600);

  //send response to client
  int i = 1;
  write(*to_client, &i, sizeof(int));

  //confirm client's response
  read(from_client, &i, sizeof(int));
  if (i == 2)
    printf("Handshake complete\n");

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  if (mkfifo("CLIENT", 0600))
    printf("Client error: %s\n", strerror(errno));

  *to_server = open(ACK, O_WRONLY, 0600);

  //sending private fifo
  char *fifo_name = (char *)calloc(BUFFER_SIZE, sizeof(char));
  strcpy(fifo_name, "CLIENT");
  write(*to_server, fifo_name, BUFFER_SIZE);
  
  int from_server = open("CLIENT", O_RDONLY, 0600);

  int message;
  read(from_server, &message, sizeof(int));
  remove("CLIENT");
  message += 1;
  write(*to_server, &message, sizeof(int));

  return from_server;
}
