all: clean build run

dev: clean build

build:
	gcc ./sorting/quick-sort.c -o ./sorting/quick-sort.sh -lm
clean:
	rm -rf ./sorting/quick-sort.sh
run:
	./sorting/quick-sort.sh