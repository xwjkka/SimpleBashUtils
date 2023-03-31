CC=gcc
CFLAGS=-Wall -Werror -Wextra -D_GNU_SOURCE
SOURCES=s21_grep.c
EXECUTABLE=s21_grep

all: s21_grep

s21_grep:
	$(CC) $(SOURCES) -o $(EXECUTABLE)

rebuild: clean all

clean:
	rm -rf s21_grep results_grep.txt results.txt

tests:
	sh s21_grep.sh

style:
	clang-format -i *.c *.h