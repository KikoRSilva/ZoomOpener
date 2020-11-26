# Makefile
# ZoomOpener by Francisco Ribeiro e Silva, 2020

CC   = gcc
LD   = gcc
CFLAGS =-Wall -g -std=gnu99 -I../
LDFLAGS=-lm

# A phony target is one that is not really the name of a file
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean run

all: zoomopener

zoomopener: main.o parsing.o
		$(LD) $(CFLAGS) $(LDFLAGS) -o zoomopener main.o parsing.o

parsing.o: parsing.c parsing.h
		$(LD) $(CFLAGS) -o parsing.o -c parsing.c

main.o: main.c
		$(LD) $(CFLAGS) -o main.o -c main.c

clean:
	@echo Cleaning...
	rm -f *.o zoomopener

run: zoomopener
	./zoomopener
