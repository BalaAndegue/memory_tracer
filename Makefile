CC=gcc
CFLAGS=-Wall -Wextra -fPIC -Iinclude -g
LDFLAGS=-shared
SRC=src/tracer.c
OBJ=$(SRC:.c=.o)
TARGET=bin/libmemorytracer.so

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(LDFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf bin/*.so src/*.o memory_access_log.csv

.PHONY: all clean
