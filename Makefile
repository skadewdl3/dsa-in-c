all: clean build run

dev: clean build

build:
	gcc ./tower-of-hanoi/toh.c -o ./tower-of-hanoi/toh.sh -lm
clean:
	rm -rf ./tower-of-hanoi/toh.sh
run:
	./tower-of-hanoi/toh.sh