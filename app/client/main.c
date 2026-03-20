#include <arpa/inet.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   const char *SERVER_IP = "127.0.0.1";
   const uint16_t SERVER_PORT = 3000;

   // server socket
   int server_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (server_socket == -1) {
      fprintf(stderr, "[%s] Failed to create socket for server\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // server address
   struct sockaddr_in server_address;
   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(SERVER_PORT);
   int success = inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);
   if (success != 1) {
      fprintf(stderr, "[%s] Failed to set address for server\n", argv[0]);
      close(server_socket);
      exit(EXIT_FAILURE);
   }

   // connect to the server
   if (connect(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
      fprintf(stderr, "[%s] Failed to initiate connection to server: %s:%d\n", argv[0], SERVER_IP, SERVER_PORT);
      close(server_socket);
      exit(EXIT_FAILURE);
   }
   printf("[%s] Connected to server: %s:%d\n", argv[0], SERVER_IP, SERVER_PORT);

   while (1) {
      const char request_body[] = "Hello world from client!\n";

      // host, 16-bit byte order → network byte order  
      uint16_t len = strlen(request_body);
      uint16_t request_body_length = htons(len);

      // send request header
      if(send(server_socket, &request_body_length, sizeof(request_body_length), 0) == -1) {
         fprintf(stderr, "[%s] Failed to send request header to server: %s:%d\n", argv[0], SERVER_IP, SERVER_PORT);
         close(server_socket);
         fprintf(stderr, "[%s] Server connection closed: %s:%d\n", argv[0], SERVER_IP, SERVER_PORT);
         exit(EXIT_FAILURE);
      }
      printf("[%s] Request header was sent successfully\n", argv[0]);
      
      // send request body
      if(send(server_socket, request_body, len, 0) == -1) {
         fprintf(stderr, "[%s] Failed to send request body to server: %s:%d\n", argv[0], SERVER_IP, SERVER_PORT);
         close(server_socket);
         fprintf(stderr, "[%s] Server connection closed: %s:%d\n", argv[0], SERVER_IP, SERVER_PORT);
         exit(EXIT_FAILURE);
      }
      printf("[%s] Request body was sent successfully\n", argv[0]);
      break;
   }

   return 0;
}
