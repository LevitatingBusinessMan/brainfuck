CC=gcc
CFLAGS=-pthread -Wall -Wextra -O2 -std=c99 -pedantic

build:
	$(CC) $(CFLAGS) -g -fsanitize=address -o bf main.c

install:
	install -Dvm 755 ./bf ${DESTDIR}/usr/bin/bf
uninstall:
	rm -v ${DESTDIR}/usr/bin/bf
