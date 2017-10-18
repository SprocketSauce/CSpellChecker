CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi -g
EXEC = spellCheck
OBJ = spellCheck.o check.o linkedList.o config.o

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -g

spellCheck.o : spellCheck.c
	$(CC) -c spellCheck.c $(CFLAGS)

linkedList.o : linkedList.c linkedList.h
	$(CC) -c linkedList.c $(CFLAGS)

config.o: config.c config.h
	$(CC) -c config.c $(CFLAGS)

clean:
	rm -f $(EXEC) spellCheck.o linkedList.o config.o
