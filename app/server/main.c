#include "server.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   char *ip_arg = NULL;
   char *port_arg = NULL;

   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "--help") == 0) {
         print_help(argv[0]);
         return 0;
      }
      else if (strcmp(argv[i], "--ip") == 0 && i + 1 < argc) ip_arg = argv[++i];
      else if (strcmp(argv[i], "--port") == 0 && i + 1 < argc) port_arg = argv[++i];
      else {
         fprintf(stderr, "[%s] Wrong usage: '%s'\n", argv[0], argv[i]);
         fprintf(stderr, "[%s] Try '%s --help'\n", argv[0], argv[0]);
         exit(EXIT_FAILURE);
      }
   }

   if (ip_arg == NULL || port_arg == NULL) {
      fprintf(stderr, "[%s] Not enough options\n", argv[0]);
      fprintf(stderr, "[%s] Try '%s --help'\n", argv[0], argv[0]);
      exit(EXIT_FAILURE);
   }

   char *SERVER_IP = ip_arg;

   errno = 0;
   char *end;
   uint16_t SERVER_PORT = strtol(port_arg, &end, 10);
   if (errno != 0 || SERVER_PORT < 1 || SERVER_PORT > 65535) {
      fprintf(stderr, "[%s] Wrong port\n", argv[0]);
      fprintf(stderr, "[%s] Try '%s --help'\n", argv[0], argv[0]);
      exit(EXIT_FAILURE);
   }

   // server socket
   int server_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (server_socket == -1) {
      fprintf(stderr, "[%s] Failed to create server socket\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // server address
   struct sockaddr_in server_address;
   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(SERVER_PORT);
   int success = inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);
   if (success != 1) {
      fprintf(stderr, "[%s] Failed to set server address\n", argv[0]);
      close(server_socket);
      exit(EXIT_FAILURE);
   }

   // bind
   if(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
      fprintf(stderr, "[%s] Failed to bind server address to server socket\n", argv[0]);
      close(server_socket);
      exit(EXIT_FAILURE);
   }

   // listen
   if (listen(server_socket, SOMAXCONN)) {
      fprintf(stderr, "[%s] Failed to listen for connections\n", argv[0]);
      close(server_socket);
      exit(EXIT_FAILURE);
   }
   printf("[%s] Listening on %s:%d\n", argv[0], SERVER_IP, SERVER_PORT);

   // keep listening for connections
   while (1) {
      // prepare client data
      int client_socket;
      struct sockaddr_in client_address;
      socklen_t client_address_length = sizeof(client_address);

      // block until a client is connected
      client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
      if (client_socket == -1) {
         fprintf(stderr, "[%s] Failed to accept client connection\n", argv[0]);
         close(server_socket);
         exit(EXIT_FAILURE);
      }

      // client info
      char *client_ip = inet_ntoa(client_address.sin_addr);
      int client_port = ntohs(client_address.sin_port);
      printf("[%s] Client connected: %s:%d\n", argv[0], client_ip, client_port);

      // keep connection alive with client
      while(1) {
         // reveice request header
         uint16_t request_header;
         int header_bytes_read = recv(client_socket, &request_header, sizeof(request_header), MSG_WAITALL);
         if (header_bytes_read == -1) {
            fprintf(stderr, "[%s] Failed to read client request header: %s:%d\n", argv[0], client_ip, client_port);
            break;
         } else if (header_bytes_read == 0) break;

         // network byte order → host, 16-bit byte order
         uint16_t request_body_length = ntohs(request_header);

         // revceive request body
         char *request_body = malloc(request_body_length + 1);
         if (request_body == NULL) {
            fprintf(stderr, "[%s] Failed to allocate buffer for client request\n", argv[0]);
            break;
         }
         int body_bytes_read = recv(client_socket, request_body, request_body_length, MSG_WAITALL);
         if (body_bytes_read == -1) {
            fprintf(stderr, "[%s] Failed to read client request body: %s:%d\n", argv[0], client_ip, client_port);
            break;
         } else if (body_bytes_read == 0) break;

         request_body[request_body_length] = '\0';
         printf("[%s] Client sent (%d bytes):\n%s\n", argv[0], body_bytes_read, request_body);
         free(request_body);
      }
      close(client_socket);
      printf("[%s] Client connection closed: %s:%d\n", argv[0], client_ip, client_port);
   }

   close(server_socket);
   printf("[%s] Server closed\n", argv[0]);
   return 0;
}
