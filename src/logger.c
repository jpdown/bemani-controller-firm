#include <pico/stdio.h>
#include <stdio.h>

#include "logger.h"

static log_level_t current_log_level = DEFAULT_LOG_LEVEL;

static const char *log_level_to_string(log_level_t level);

void logger_init(void) { stdio_init_all(); }

void print_log(log_level_t level, const char *format, ...) {
  if (level < current_log_level) {
    return;
  }

  char buffer[LOG_BUFFER_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, LOG_BUFFER_SIZE, format, args);
  va_end(args);

  printf("[%s] %s\n", log_level_to_string(level), buffer);
}

static const char *log_level_to_string(log_level_t level) {
  switch (level) {
  case LOG_LEVEL_DEBUG:
    return "DEBUG";
  case LOG_LEVEL_INFO:
    return "INFO";
  case LOG_LEVEL_WARNING:
    return "WARN";
  case LOG_LEVEL_ERROR:
    return "ERROR";
  default:
    return "UNKWN";
  };
}
