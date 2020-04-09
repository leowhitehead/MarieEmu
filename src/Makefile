CC = gcc
FLAGS = -Wall -Wpedantic
STD = c11
BINNAME = marie

main: main.c
	$(CC) main.c -o $(BINNAME) $(FLAGS) -std=$(STD)

clean: $(BINNAME)
	rm $(BINNAME)
