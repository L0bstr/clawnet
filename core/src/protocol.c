#include <clawnet/protocol.h>

ssize_t recv_lv(int fd, void **buf) {
   uint16_t length;
   size_t bytes_read = recv(fd, &length, sizeof(length), MSG_WAITALL);
   if (bytes_read <= 0) {
      *buf = NULL;
      return bytes_read;
   }

   // network to host
   uint16_t value_length = ntohs(length);

   *buf = malloc(value_length + 1);
   if (!*buf) return -1;

   bytes_read = recv(fd, *buf, value_length, MSG_WAITALL);
   if (bytes_read <= 0) {
      free(*buf);
      *buf = NULL;
   }

   ((char*)*buf)[value_length] = '\0';

   return bytes_read;
}

ssize_t send_lv(int fd, void *buf, size_t n) {
   if (n > UINT16_MAX) n = UINT16_MAX;
   
   // host to network
   uint16_t value_length = htons(n);

   char all_data[sizeof(value_length) + n];
   memcpy(all_data, &value_length, sizeof(value_length));
   memcpy(all_data + sizeof(value_length), buf, n);

   size_t bytes_sent = send(fd, &all_data, sizeof(all_data), 0);
   return bytes_sent;
}
