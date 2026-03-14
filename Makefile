CC = gcc
CFLAGS = -Wall -Wextra -std=c11 \
         -I$(shell pg_config --includedir) \
         -I$(shell pg_config --includedir-server) \
         -I/usr/include/postgresql/server
LDFLAGS = -L$(shell pg_config --libdir) -lpq
TARGET = pgprogram
SOURCES = connect.c  # Your source file

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)

