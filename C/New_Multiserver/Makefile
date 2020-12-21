CC = gcc
CFLAGS =-Wall -Wextra -Wpedantic -o2
CFILES=$(shell ls *.c)
PROGS=$(CFILES:%.c=%)

install: prog_pmcsn_multi_server risultati

prog_pmcsn_multi_server: main.c basic.c basic.h rngs.h rngs.c distributions.c distributions.h dynamic_list.c dynamic_list.h next_event.c next_event.h parser.c parser.h rvms.h rvms.c stats.c stats.h multiserver_func.h multiserver_func.c
	$(CC) $(CFLAGS) -o $@ $^ -lm -std=c99 -lpthread

risultati:jackson.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

