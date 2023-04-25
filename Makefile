all: clean build run

dev: clean build

build:
	gcc ./linked-list/polynomial-parsing/polynomial-parsing.c -o ./linked-list/polynomial-parsing/polynomial-parsing.sh -lm
clean:
	rm -rf ./linked-list/polynomial-parsing/polynomial-parsing.sh
run:
	./linked-list/polynomial-parsing/polynomial-parsing.sh