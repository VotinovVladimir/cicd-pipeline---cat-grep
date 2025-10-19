CC=gcc
CFLAGS=-Wall -Werror -Wextra
SRC=s21_cat.c
TARGET=s21_cat

all: main

test: $(TARGET)
	bash cattest.sh

main: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)