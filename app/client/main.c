#include "client.h"
#include <arpa/inet.h>
#include <trawl/protocol.h>
#include <errno.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   char *ip_arg;
   char *port_arg;
   int keep_alive = 0;

   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "--help") == 0) {
         print_help(argv[0]);
         return 0;
      }
      else if (strcmp(argv[i], "--ip") == 0 && i + 1 < argc) ip_arg = argv[++i];
      else if (strcmp(argv[i], "--port") == 0 && i + 1 < argc) port_arg = argv[++i];
      else if (strcmp(argv[i], "--keep-alive") == 0) keep_alive = 1;
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
      fprintf(stderr, "[%s] Failed to connect to server: %s:%d\n", argv[0], SERVER_IP, SERVER_PORT);
      close(server_socket);
      exit(EXIT_FAILURE);
   }
   printf("[%s] Connected to server (%s:%d)\n", argv[0], SERVER_IP, SERVER_PORT);

   do {
      // input
      size_t n = 256;
      char *input = malloc(n);
      if (!input) {
         fprintf(stderr, "[%s] Failed to allocate memory\n", argv[0]);
         close(server_socket);
         fprintf(stderr, "[%s] Connection with server closed (%s:%d)\n", argv[0], SERVER_IP, SERVER_PORT);
         break;
      }

      printf("Input: ");
      size_t char_read = getline(&input, &n, stdin);
      if (char_read == EOF) break;

      // send
      ssize_t bytes_sent = send_lv(server_socket, input, char_read - 1);
      if (bytes_sent <= 0) {
         fprintf(stderr, "[%s] Failed to send message to server (%s:%d)\n", argv[0], SERVER_IP, SERVER_PORT);
         break;
      }

      // recv
      char *response;
      ssize_t bytes_read = recv_lv(server_socket, (void*)&response);
      if (bytes_read == -1) {
         fprintf(stderr, "[%s] Failed to read message: ", argv[0]);
         perror("");
         break;
      } else if (bytes_read == 0) {
         printf("[%s] Server ended the connection (%s:%d)\n", argv[0], SERVER_IP, SERVER_PORT);
         break;
      }

      printf("[%s] Server sent:\n%s\n", argv[0], response);
   } while (keep_alive);

   close(server_socket);
   fprintf(stderr, "[%s] Sever connection closed (%s:%d)\n", argv[0], SERVER_IP, SERVER_PORT);
   return 0;
}
