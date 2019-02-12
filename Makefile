PROJECT=spi_example

DEFINES=

CC=gcc
CFLAGS=-Wall $(DEFINES)

SRCDIR=src
SRCS = $(wildcard $(SRCDIR)/*.c)

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROJECT): $(PROJECT).o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(SRCDIR)/*.o $(PROJECT).o $(PROJECT)
