#include "server.h"

void print_help(const char *program_name) {
   printf("%s is a TCP server implementation\n", program_name);
   printf("\n");
   printf("Usage: %s --ip <IP> --port <PORT> [OPTIONS]...\n", program_name);
   printf("\n");
   printf("Arguments:\n");
   printf("\t<IP> - IPv4 address\n");
   printf("\t<PORT> - port number [1-65535]\n");
   printf("\n");
   printf("Options:\n");
   printf("\t--help\t\t\tPrints this message\n");
   printf("\t--ip <IP>\t\tNetwork interface address to listen on\n");
   printf("\t--port <PORT>\t\tA port number on which the server should listen\n");
}
