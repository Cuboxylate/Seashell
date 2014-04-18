CC = gcc
CFLAGS  = -g -W -Wall -ansi -pedantic -std=gnu99
RM = rm -f

all: Seashell

Seashell: Seashell.o chooser.o simple_cmds.o call_prog.o
	$(CC) $(CFLAGS) -o Seashell Seashell.o chooser.o simple_cmds.o call_prog.o

Seashell.o: Seashell.c 
	$(CC) $(CFLAGS) -c Seashell.c 

chooser.o: chooser.c
	$(CC) $(CFLAGS) -c chooser.c

simple_cmds.o: simple_cmds.c
	$(CC) $(CFLAGS) -c simple_cmds.c

call_prog.o: call_prog.c
	$(CC) $(CFLAGS) -c call_prog.c

clean:
	$(RM) Seashell *.o 

again:
	make clean
	make all