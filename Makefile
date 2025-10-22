# Makefile for EECS 348 Lab 8 (C Programming)
# Targets: score_combos (Task 1), temp_convert (Task 2)

CC      := gcc
CFLAGS  := -Wall -Wextra -O2

.PHONY: all clean

all: score_combos temp_convert

score_combos: score_combos.c
	$(CC) $(CFLAGS) -o $@ $<

temp_convert: temp_convert.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f score_combos temp_convert
