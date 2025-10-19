CC=gcc
CFLAGS=-Wall -Werror -Wextra
SRC=s21_grep.c
TARGET=s21_grep

all: main

test: $(TARGET)
	bash greptest.sh

main: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)