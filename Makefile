CC=gcc
CFLAGS=-pthread -Wall -Wextra -O2 -std=c99 -pedantic

build:
	$(CC) $(CFLAGS) -g -fsanitize=address -o bf main.c
