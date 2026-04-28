#include <recv_buffer.h>

#define RECV_BUFFER_INIT_SIZE 512

int recv_buffer_init(recv_buffer_t *recv_buffer) {
   if (!recv_buffer) return 0;

   recv_buffer->capacity = RECV_BUFFER_INIT_SIZE;
   recv_buffer->buf = malloc(RECV_BUFFER_INIT_SIZE);
   if (!recv_buffer->buf) return 0;

   recv_buffer->start = 0;
   recv_buffer->len = 0;

   return 1;
}

void recv_buffer_free(recv_buffer_t *recv_buffer) {
   if (!recv_buffer) return;

   free(recv_buffer->buf);
}

int recv_buffer_resize(recv_buffer_t *recv_buffer, size_t capacity) {
   if (!recv_buffer) return 0;

   uint8_t *tmp = realloc(recv_buffer->buf, capacity);
   if (!tmp) return 0;

   recv_buffer->buf = tmp;
   recv_buffer->capacity = capacity;

   return 1;
}

void recv_buffer_compact(recv_buffer_t *recv_buffer) {
   if (!recv_buffer) return;

   memmove(recv_buffer->buf, recv_buffer->buf + recv_buffer->start, recv_buffer->len);
   recv_buffer->start = 0;
}

int recv_buffer_write(recv_buffer_t *recv_buffer, char *buf, size_t n) {
    if (!recv_buffer || !buf) return 0;

    size_t space_back = recv_buffer->capacity - recv_buffer->start - recv_buffer->len;
    size_t space_total = space_back + recv_buffer->start;

    if (space_back < n) {
       if (space_total < n) {
          size_t double_cap = recv_buffer->capacity * 2;
          size_t needed_cap = recv_buffer->len + n;
          size_t new_cap = double_cap > needed_cap ? double_cap : needed_cap;
          if (!recv_buffer_resize(recv_buffer, new_cap)) return 0;
       }
       recv_buffer_compact(recv_buffer);
    }

    uint8_t *write_ptr = recv_buffer->buf + recv_buffer->start + recv_buffer->len;
    memcpy(write_ptr, buf, n);
    recv_buffer->len += n;

    return 1;
}

const uint8_t *recv_buffer_peek(recv_buffer_t *recv_buffer) {
   if (!recv_buffer) return NULL;

   return recv_buffer->buf + recv_buffer->start;
}

ssize_t recv_buffer_read(recv_buffer_t *recv_buffer, char *buf, size_t n) {
   if (!recv_buffer || !buf) return 0;

   uint8_t *read_ptr = recv_buffer->buf + recv_buffer->start;
   size_t read_size = recv_buffer->len > n ? n : recv_buffer->len;
   memcpy(buf, read_ptr, read_size);

   recv_buffer->start += read_size;
   recv_buffer->len -= read_size;

   return read_size;
}

size_t recv_buffer_recv(recv_buffer_t *recv_buffer, size_t n, int fd, int flags) {
   if (!recv_buffer) return -1;

    size_t space_back = recv_buffer->capacity - recv_buffer->start - recv_buffer->len;
    size_t space_total = space_back + recv_buffer->start;

    if (space_back < n) {
       if (space_total < n) {
          size_t double_cap = recv_buffer->capacity * 2;
          size_t needed_cap = recv_buffer->len + n;
          size_t new_cap = double_cap > needed_cap ? double_cap : needed_cap;
          if (!recv_buffer_resize(recv_buffer, new_cap)) return -1;
       }
       recv_buffer_compact(recv_buffer);
    }

    uint8_t *write_ptr = recv_buffer->buf + recv_buffer->start + recv_buffer->len;
    ssize_t bytes = recv(fd, write_ptr, n, flags);
    if (bytes > 0) recv_buffer->len += bytes;

    return bytes;
}
