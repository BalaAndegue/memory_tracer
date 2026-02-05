#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../include/tracer.h"

static FILE* log_file = NULL;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

static void open_log() {
    if (!log_file) {
        log_file = fopen("memory_access_log.csv", "w");
        if (log_file) {
            fprintf(log_file, "timestamp,thread_id,access_type,address,size\n");
            fflush(log_file);
        }
    }
}

void tracer_init() {
    open_log();
}

void tracer_finalize() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

void log_memory_access(const char* type, void* addr, size_t size) {
    pthread_mutex_lock(&log_mutex);
    open_log();
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    unsigned long tid = (unsigned long)pthread_self();
    if (log_file) {
        fprintf(log_file, "%ld.%09ld,%lu,%s,%p,%zu\n", ts.tv_sec, ts.tv_nsec, tid, type, addr, size);
        fflush(log_file);
    }
    pthread_mutex_unlock(&log_mutex);
}

// Wrappers for malloc/free/calloc/realloc

typedef void* (*malloc_t)(size_t);
typedef void  (*free_t)(void*);
typedef void* (*calloc_t)(size_t, size_t);
typedef void* (*realloc_t)(void*, size_t);

void* malloc(size_t size) {
    static malloc_t real_malloc = NULL;
    if (!real_malloc) real_malloc = (malloc_t)dlsym(RTLD_NEXT, "malloc");
    void* ptr = real_malloc(size);
    log_memory_access("malloc", ptr, size);
    return ptr;
}

void free(void* ptr) {
    static free_t real_free = NULL;
    if (!real_free) real_free = (free_t)dlsym(RTLD_NEXT, "free");
    log_memory_access("free", ptr, 0);
    real_free(ptr);
}

void* calloc(size_t nmemb, size_t size) {
    static calloc_t real_calloc = NULL;
    if (!real_calloc) real_calloc = (calloc_t)dlsym(RTLD_NEXT, "calloc");
    void* ptr = real_calloc(nmemb, size);
    log_memory_access("calloc", ptr, nmemb * size);
    return ptr;
}

void* realloc(void* ptr, size_t size) {
    static realloc_t real_realloc = NULL;
    if (!real_realloc) real_realloc = (realloc_t)dlsym(RTLD_NEXT, "realloc");
    void* new_ptr = real_realloc(ptr, size);
    log_memory_access("realloc", new_ptr, size);
    return new_ptr;
}
