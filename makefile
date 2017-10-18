CC = gcc
CFLAGS = -Wall -Werror -pedantic -ansi -g
EXEC = checkWord
OBJ = checkWord.o check.o linkedList.o config.o

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -g

checkWord.o : checkWord.c checkWord.h
	$(CC) -c checkWord.c $(CFLAGS)

linkedList.o : linkedList.c linkedList.h
	$(CC) -c linkedList.c $(CFLAGS)

config.o: config.c config.h
	$(CC) -c config.c $(CFLAGS)

clean:
	rm -f $(EXEC) checkWord.o 
