#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

/**
 * Receive buffer
*/
typedef struct {
   /**
    * Pointer to the buffer in memory.
   */
   uint8_t *buf;

   /**
    * Start of the available buffer data.
   */
   size_t start;

   /**
    * Length of buffer data in bytes.
   */
   size_t len;

   /**
    * The capacity of the buffer in bytes.
   */
   size_t capacity;
} recv_buffer_t;

/**
 * Initializes a receive buffer.
 * RETURNS 1 on success or 0 on error.
*/
int recv_buffer_init(recv_buffer_t *recv_buffer);

/**
 * Frees buffer of the receive buffer struct.
*/
void recv_buffer_free(recv_buffer_t *recv_buffer);

/**
 * Resizes receive buffer.
 * RETURNS 1 on success or 0 on error.
*/
int recv_buffer_resize(recv_buffer_t *recv_buffer, size_t capacity);

/**
 * Shifts available data to the front of the buffer.
*/
void recv_buffer_compact(recv_buffer_t *recv_buffer);

/**
 * Writes data to the buffer.
 * RETURNS 1 on success or 0 on error.
*/
int recv_buffer_write(recv_buffer_t *recv_buffer, char *buf, size_t n);

/**
 * Peek into the available buffer data.
 * RETURNS a read only pointer to the start of the available data or NULL if the recv_buffer is NULL.
*/
const uint8_t *recv_buffer_peek(recv_buffer_t *recv_buffer);

/**
 * Reads data into buf, marking the contents of receive buffer as consumed.
 * RETURNS the number of bytes read into buf.
*/
ssize_t recv_buffer_read(recv_buffer_t *recv_buffer, char *buf, size_t n);

/**
 * Receives data from a socket into the recv_buffer.
 * RETURNS the number of bytes received, -1 on error or 0 if the connection is closed.
*/
size_t recv_buffer_recv(recv_buffer_t *recv_buffer, size_t n, int fd, int flags);
