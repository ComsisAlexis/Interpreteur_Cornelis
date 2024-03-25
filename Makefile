CC = gcc
CFLAGS = -Wall -Wextra -g #-fsanitize=address
EXE = prog

OFILES = main.o stack.o extract.o block.o color.o

all: $(EXE)

main.o: stack.h extract.h block.h
stack.o: stack.h
extract.o: extract.h color.h
block.o: color.h block.h stack.h
color.o: color.h

$(EXE): $(OFILES)
	$(CC) $(CFLAGS) -o $@ $^
