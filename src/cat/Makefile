CC=gcc
CFLAGS=-Wall -Werror -Wextra
SOURCES=s21_cat.c
EXECUTABLE=s21_cat

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

rebuild: clean all

clean:
	rm -rf s21_cat results_cat.txt results.txt

tests:
	sh s21_cat.sh

style:
	clang-format -i *.c *.h