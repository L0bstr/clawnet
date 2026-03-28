#include "client.h"

void print_help(const char *program_name) {
   printf("%s is a TCP client implementation\n", program_name);
   printf("\n");
   printf("Usage: %s --ip <IP> --port <PORT> [OPTIONS]...\n", program_name);
   printf("\n");
   printf("Arguments:\n");
   printf("\t<IP> - IPv4 address\n");
   printf("\t<PORT> - port number [1-65535]\n");
   printf("\n");
   printf("Options:\n");
   printf("\t--help       \t\tPrints this message\n");
   printf("\t--ip <IP>    \t\tIPv4 address of the server\n");
   printf("\t--port <PORT>\t\tA port number on the server\n");
   printf("\t--keep-alivet\t\tKeep the connection with the server alive\n");
}
