CC+FLAGS = g++ -std=c++17 -Wall -Werror -Wextra
CHECK_FLAGS = -lgtest -pthread

all: build

build: clean
	$(CC+FLAGS) project_task.cpp
	./a.out

test: clean
	$(CC+FLAGS) -o test tests.cpp project_task.cpp $(CHECK_FLAGS) -DRUN_TESTS
	./test

clean:
	rm -rf test a.out