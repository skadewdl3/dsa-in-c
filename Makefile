all: clean build run

dev: clean build

build:
	gcc ./bingo/main.c -o ./bingo/main.sh -lm
clean:
	rm -rf ./bingo/main.sh
run:
	./bingo/main.sh