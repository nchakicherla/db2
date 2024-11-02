CC = gcc
CFLAGS = -std=c99 -Wall -Wpedantic -Werror -o3 #-luuid
OS := $(shell uname)

mkBinDir := $(shell mkdir -p bin)
mkObjDir := $(shell mkdir -p obj)
mkLibObjDir := $(shell mkdir -p obj/lib)

BIN = ./bin/main.run

MAIN = 	./obj/main.o

LIBOBJS = ./obj/lib/mempool.o

OBJS = 

default: reset $(BIN)
ifeq ($(OS),Darwin) 
	$(BIN)
else 
	valgrind --track-origins=yes --leak-check=full $(BIN)  
endif

reset: clear $(BIN)

run: reset $(BIN)
	$(BIN)

$(BIN): $(LIBOBJS) $(OBJS) $(MAIN)
	$(CC) $(CFLAGS) $(LIBOBJS) $(OBJS) $(MAIN) -o $(BIN)

./obj/lib/%.o: ./src/lib/%.c ./src/lib/%.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj/%.o: ./src/%.c ./src/%.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj/main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -o ./obj/main.o
	
clear: clear-bin clear-obj

clear-bin:
	-rm ./bin/*

clear-obj:
	-rm ./obj/*
