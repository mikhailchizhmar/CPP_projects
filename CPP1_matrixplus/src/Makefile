CC+FLAGS = g++ -std=c++17 -Wall -Werror -Wextra
GCOVFLAGS = -L. --coverage
OS = $(shell uname)
FILES_CPP = my_matrix_oop.cpp
FILES_A = my_matrix_oop.a
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -pthread
else
	CHECK_FLAGS = -lgtest
endif

TEST_COMPILE = $(CC+FLAGS) $(FILES_A) tests.cpp $(CHECK_FLAGS) -L. $(FILES_A)

all: clean test

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM .clang-format

test: $(FILES_A)
	$(TEST_COMPILE)
	./a.out

gcov_report: test
	rm -f *.g*
	$(CC+FLAGS) $(FILES_CPP) tests.cpp $(FILES_A) $(CHECK_FLAGS) $(GCOVFLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info


$(FILES_A):
	$(CC+FLAGS) -c $(FILES_CPP)
	ar rcs $(FILES_A) *.o
	rm -rf *.o
	ranlib $(FILES_A)

check:
ifeq ("","$(wildcard ./.clang-format)")
	cp -f ../materials/linters/.clang-format ./.clang-format
endif
	clang-format -n *.cpp *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes ./a.out
endif
	make clean

style:
	clang-format -i *.cpp *.h

git:
	git add .
	git commit -m "$(c)"
	git push origin develop
# make git c=commit