all: test

test:
	g++ -std=c++17 test_main.cc -lgtest -lgtest_main -pthread -o s21_containers
	./s21_containers

clean:
	rm -rf s21_containers
	rm -rf coverage*

clang:
	clang-format --style=google -i array/*
	clang-format --style=google -i avl_tree/*
	clang-format --style=google -i list/*
	clang-format --style=google -i map/*
	clang-format --style=google -i multiset/*
	clang-format --style=google -i queue/*
	clang-format --style=google -i set/*
	clang-format --style=google -i stack/*
	clang-format --style=google -i vector/*
	clang-format --style=google -i *.h *.cc

clang_check:
	clang-format --style=google -n array/*
	clang-format --style=google -n avl_tree/*
	clang-format --style=google -n list/*
	clang-format --style=google -n map/*
	clang-format --style=google -n multiset/*
	clang-format --style=google -n queue/*
	clang-format --style=google -n set/*
	clang-format --style=google -n stack/*
	clang-format --style=google -n vector/*
	clang-format --style=google -n *.h *.cc

.PHONY: all test clean
