CFLAGS = -Wall -Werror -Wextra -std=c11
EXECUTABLE = test

ifeq ($(shell uname), Linux)
	GFLAGS = -lcheck_pic -lsubunit -lm
endif
ifeq ($(shell uname), Darwin)
	GFLAGS = -lcheck -lm
endif

all: clean s21_matrix.a gcov_report

clean:
	@rm -rf s21_matrix.a
	@rm -rf $(EXECUTABLE)
	@rm -rf ./report
	@rm -rf *.o
	@rm -rf *.gcno *.gcda *.gcov *.info
	@rm -rf $(OBJ_SUPPORT) $(OBJ_BASIC) $(OBJ_COMPARISON) $(OBJ_ARITHMETIC) $(OBJ_ANOTHER) $(OBJ_TESTS)

test: clean s21_matrix.a tests.o
	@gcc $(CFLAGS) tests.c s21_matrix.c $(GFLAGS) -o $(EXECUTABLE)
	@./$(EXECUTABLE)

s21_matrix.a: 
	gcc -Wall -Werror -Wextra -c s21_matrix.c
	ar rc s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

gcov_report: clean s21_matrix.a tests.o
	@gcc $(CFLAGS) tests.c s21_matrix.c $(GFLAGS) -o $(EXECUTABLE) --coverage
	@./$(EXECUTABLE)
	@rm -rf test-test* test-eq* test-is* equal_size* is_* test_*
	@lcov -t "tests" -o tests.info -c -d .
	@genhtml -o report tests.info
	open report/index.html

style:
	clang-format -style=google -i *.c *.h

debug: clean
	gcc -g tests.c s21_matrix.c $(GFLAGS) -o $(EXECUTABLE)

