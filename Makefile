SHELL=/bin/bash
INSTALLDIR=/usr/local/lib

PROJECT=mipea

# define your chip here (BCM2835, BCM2836 or BCM2837):
DEFINES=

CC=gcc
CFLAGS=-Wall -Wextra -g $(DEFINES)
LFLAGS=

LDCONFIG=ldconfig
LDCONFIGFLAGS=

SRCDIR=src
SRCS=$(wildcard $(SRCDIR)/*.c)

OBJS=$(SRCS:.c=.o)
HEADERS=$(SRCS:.c=.h)

%.o: %.c
	$(CC) -fpic -c -o $@ $< $(CFLAGS)

.PHONY: all
all: lib$(PROJECT).so.0.0
lib$(PROJECT).so.0.0: $(OBJS)
	$(CC) -shared -Wl,-soname,lib$(PROJECT).so.0 -lc -o $@ $^ $(CFLAGS) $(LFLAGS)

.PHONY: install
install: lib$(PROJECT).so.0.0
	cp lib$(PROJECT).so.0.0 $(INSTALLDIR)
	$(LDCONFIG) $(LDCONFIGFLAGS)
	ln -sf $(INSTALLDIR)/lib$(PROJECT).so.0 $(INSTALLDIR)/libmipea.so
	cp $(HEADERS) $(INSTALLDIR)/../include

.PHONY: uninstall
uninstall:
	rm -f $(INSTALLDIR)/lib$(PROJECT).so*
	rm -f $(patsubst src/%,$(INSTALLDIR)/../include/%,$(HEADERS))

.PHONY: clean
clean:
	rm -f $(SRCDIR)/*.o *.o lib$(PROJECT).so.0.0
