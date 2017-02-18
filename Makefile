CC = g++
FLAGS = -W -Wall -Werror -pedantic -ansi
PARAMS = main.o

all: $(PARAMS)
	mkdir -p ./bin
	$(CC) $(FLAGS) $(PARAMS) -o ./bin/rshell
	rm *o

main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp -c
	

clean:
	rm -rf bin