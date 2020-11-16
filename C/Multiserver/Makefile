CC = gcc
CFLAGS =-Wall -Wextra -Wpedantic -o2
CFILES=$(shell ls *.c)
PROGS=$(CFILES:%.c=%)

install: prog_pmcsn

prog_pmcsn: main.c basic.c basic.h rngs.h rngs.c distributions.c distributions.h dynamic_list.c dynamic_list.h next_event.c next_event.h parser.c parser.h rvms.h rvms.c multiserver_func.c multiserver_func.h stats.c stats.h
	$(CC) $(CFLAGS) -o $@ $^ -lm -std=c99 -lpthread

risultati:risultati-teorici.c
	$(CC) $(CFLAGS) -o $@ $^

