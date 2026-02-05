#ifndef TRACER_H
#define TRACER_H
#include <stddef.h>

void tracer_init();
void tracer_finalize();
void log_memory_access(const char* type, void* addr, size_t size);

#endif // TRACER_H
