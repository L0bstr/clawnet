#pragma once

#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

/*
 * Receive Length–Value protocol.
 * Returns the number of bytes read, 0 if the socket is closed and -1 on error.
*/
ssize_t recv_lv(int fd, void **buf);

/*
 * Send Length–Value protocol.
 * Returns the number of bytes sent, 0 if the socket is closed and -1 on error.
*/
ssize_t send_lv(int fd, void *buf, size_t n);
