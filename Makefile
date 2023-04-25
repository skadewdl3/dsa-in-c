all: clean build run

dev: clean build

build:
	gcc ./sorting/selection-sort.c -o ./sorting/selection-sort.sh -lm
clean:
	rm -rf ./sorting/selection-sort.sh
run:
	./sorting/selection-sort.sh