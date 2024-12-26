#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

typedef enum {
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR
} log_level_t;

#define LOG_DEBUG(format, ...) (print_log(LOG_LEVEL_DEBUG, format __VA_OPT__(,) __VA_ARGS__))
#define LOG_INFO(format, ...) (print_log(LOG_LEVEL_INFO, format __VA_OPT__(,) __VA_ARGS__))
#define LOG_WARNING(format, ...) (print_log(LOG_LEVEL_WARNING, format __VA_OPT__(,) __VA_ARGS__))
#define LOG_ERROR(format, ...) (print_log(LOG_LEVEL_ERROR, format __VA_OPT__(,) __VA_ARGS__))

#define LOG_BUFFER_SIZE 256U
#define DEFAULT_LOG_LEVEL LOG_LEVEL_DEBUG

void logger_init(void);
void print_log(log_level_t level, const char *format, ...);

#endif /* LOGGER_H */
