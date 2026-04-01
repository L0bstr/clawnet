#pragma once

#include <stdint.h>
#include <stdio.h>
#include <time.h>

/**
 * @struct ServerInfo
 * @brief Represents information about the server
 */
typedef struct {
   time_t start_time;
   uint32_t total_client_count;
   uint32_t active_client_count;
} ServerInfo;

/*
 * Prints help manual for server
*/
void print_help(const char *program_name);
