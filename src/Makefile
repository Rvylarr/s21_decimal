CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -std=c11 
CHECKFLAGS=$(shell pkg-config --cflags --libs check)
SANITIZER=-g -fsanitize=address
GCOVFLAGS=--coverage -fprofile-arcs -ftest-coverage
OBJ_FILES=base.o s21_arithmetic.o s21_comparison.o s21_extra.o s21_other.o s21_converters.o
OBJ_GCOV_FILES=base_test.o s21_arithmetic_test.o s21_comparison_test.o s21_extra_test.o s21_other_test.o s21_converters_test.o
LINUX = -lcheck -lm -lrt -lpthread -lsubunit

all: test

test: tests.o s21_decimal.a
	$(CC) $(SANITIZER) $(CHECKFLAGS) tests.o -L. s21_decimal.a -o test
# Ubuntu variation
#	$(CC) $(SANITIZER) $(CHECKFLAGS) tests.o -L. s21_decimal.a -lm -lcheck -o test -g $(LINUX)
tests.o:
	$(CC) $(CFLAGS) tests.c -o tests.o

test_gcov: test_gcov.o s21_decimal_test.a
	$(CC) $(SANITIZER) $(CHECKFLAGS) $(GCOVFLAGS) test_gcov.o -L. s21_decimal_test.a -o test_gcov
# Ubuntu variation
#	$(CC) $(SANITIZER) $(CHECKFLAGS) $(GCOVFLAGS) test_gcov.o -L. s21_decimal_test.a $(LINUX) -o test_gcov
test_gcov.o:
	$(CC) $(CFLAGS) $(GCOVFLAGS) tests.c -o test_gcov.o

base.o: base.c s21_decimal.h
	$(CC) $(CFLAGS) base.c -o base.o

%.o: s21_%.c s21_decimal.h
	$(CC) $(CFLAGS) $< -o $@

base_test.o: base.c s21_decimal.h
	$(CC) $(CFLAGS) base.c -o base_test.o

%_test.o: %.c s21_decimal.h
	$(CC) $(CFLAGS) $(GCOVFLAGS) $< -o $@

s21_decimal.a: $(OBJ_FILES) s21_decimal.h
	ar rc s21_decimal.a $(OBJ_FILES)
	ranlib s21_decimal.a

s21_decimal_test.a: $(OBJ_GCOV_FILES) s21_decimal.h
	ar rc s21_decimal_test.a $(OBJ_GCOV_FILES)
	ranlib s21_decimal_test.a

gcov_report: $(OBJ_GCOV_FILES) s21_decimal_test.a test_gcov
	./test_gcov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage
#	rm tests.gcda tests.gcno
	open coverage/index.html

valgrind: # only for Ubuntu
	rm -f *.log
	gcc -g *.c -lcheck -lm -lrt -lpthread -lsubunit -o test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --trace-children=yes --track-fds=yes --log-file=valgrind.log ./test 

leaks: test
	leaks -atExit -- ./test | grep LEAK:

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -n *.h
	rm -rf .clang-format

style_format: style_check
	cp ../materials/linters/.clang-format .
	clang-format -i *.c
	clang-format -i *.h
	rm -rf .clang-format

clean:
	rm -f *.o *.a *.gcno *.gcda *.info test test_gcov *.log
	rm -rf coverage

rebuild: clean all
