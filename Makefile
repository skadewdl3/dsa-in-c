all: clean build run

dev: clean build

build:
	gcc ./sorting/radix-sort.c -o ./sorting/radix-sort.sh -lm
clean:
	rm -rf ./sorting/radix-sort.sh
run:
	./sorting/radix-sort.sh