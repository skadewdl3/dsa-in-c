all: clean build run

dev: clean build

build:
	gcc ./linked-list/linked-list.c -o ./linked-list/linked-list.sh -lm
clean:
	rm -rf ./linked-list/linked-list.sh
run:
	./linked-list/linked-list.sh