CC+FLAGS = g++ -std=c++17 -Wall -Wextra -Werror
GCOVFLAGS = -L. --coverage
OS = $(shell uname)
FILES_CPP = SmartCalculator.cpp
FILES_A = SmartCalculator.a
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -pthread
else
	CHECK_FLAGS = -lgtest
endif

TEST_COMPILE = $(CC+FLAGS) $(FILES_A) test.cpp $(CHECK_FLAGS) -L. $(FILES_A)

all: install

install:
	rm -rf build
	mkdir build
	qmake SmartCalc/SmartCalc.pro -o build
	cd build && make && cd ../ && ./build/SmartCalc

dvi:
	cat doc.txt

uninstall:
	rm -rf build

dist: install
	tar -czf build.tar.gz --directory=build/ .

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM build.tar.gz

tests: $(FILES_A)
	$(TEST_COMPILE)
	./a.out

$(FILES_A):
	$(CC+FLAGS) -c $(FILES_CPP)
	ar rcs $(FILES_A) *.o
	rm -rf *.o
	ranlib $(FILES_A)

check:
ifeq ("","$(wildcard ./.clang-format)")
	cp -f ../materials/linters/.clang-format ./.clang-format
endif
	clang-format -n *.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind  --leak-check=full --track-origins=yes ./a.out
endif
	make clean

style:
	clang-format -i *.c *.h
