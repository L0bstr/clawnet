#include "server.h"
#include <arpa/inet.h>
#include <clawnet/protocol.h>
#include <errno.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   char *ip_arg;
   char *port_arg;

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

   ServerInfo server_info;
   server_info.start_time = 0;
   server_info.total_client_count = 0;
   server_info.active_client_count = 0;

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

   // Reuse TIMEWAIT port
   int enable = 1;
   setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

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

   time(&server_info.start_time);
   printf("[%s] Server is listening (%s:%d)\n", argv[0], SERVER_IP, SERVER_PORT);

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
      server_info.total_client_count++;
      server_info.active_client_count++;

      // client info
      char *client_ip = inet_ntoa(client_address.sin_addr);
      int client_port = ntohs(client_address.sin_port);
      printf("[%s] Client connected (%s:%d)\n", argv[0], client_ip, client_port);

      // loop communication
      while (1) {
         // recv
         char *request;
         ssize_t bytes_read = recv_lv(client_socket, (void*)&request);
         if (bytes_read == -1) {
            fprintf(stderr, "[%s] Failed to read message: ", argv[0]);
            perror("");
         } else if (bytes_read == 0) {
            printf("[%s] Client ended the connection (%s:%d)\n", argv[0], client_ip, client_port);
            break;
         }

         printf("[%s] Client sent:\n%s\n", argv[0], request);

         // send
         ssize_t response_length;
         char *response = NULL;
         //    help
         if (strcmp(request, "help") == 0) {
            response = 
               "Help:\n"
               "  Commands:\n"
               "    [help]    - sends this message\n"
               "    [info]    - sends server info\n"
               "    <unknown> - the server will echo back what the client sends"
               "\n";
            response_length = strlen(response);
         }
         //    server info
         else if (strcmp(request, "info") == 0) {
            time_t current = time(NULL);
            time_t up_time = (time_t)difftime(current, server_info.start_time);

            int hours = up_time / 3600;
            int minutes = (up_time % 3600) / 60;
            int seconds = up_time % 60;

            char buf[1024];
            snprintf(buf, sizeof(buf), 
                  "ServerInfo\n"
                  "  Uptime:         %02d:%02d:%02d\n"
                  "  Total clients:  %d\n"
                  "  Active clients: %d\n",
                  hours, minutes, seconds,
                  server_info.total_client_count,
                  server_info.active_client_count);
            response = buf;
            response_length = strlen(buf);
         }
         //    echo
         else {
            response = request;
            response_length = bytes_read;
         }

         ssize_t bytes_sent = send_lv(client_socket, response, strlen(response));
         if (bytes_sent <= 0) {
            fprintf(stderr, "[%s] Failed to send message to client (%s:%d)\n", argv[0], client_ip, client_port);
            break;
         }
      }

      close(client_socket);
      server_info.active_client_count--;
      printf("[%s] Client connection closed (%s:%d)\n", argv[0], client_ip, client_port);
   }

   server_info.active_client_count = 0;

   close(server_socket);
   printf("[%s] Server closed\n", argv[0]);
   return 0;
}
