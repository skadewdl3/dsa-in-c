all: clean build run

dev: clean build

build:
	gcc ./linked-list/queue/queue.c -o ./linked-list/queue/queue.sh -lm
clean:
	rm -rf ./linked-list/queue/queue.sh
run:
	./linked-list/queue/queue.sh