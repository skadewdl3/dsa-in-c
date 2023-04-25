all: clean build run

dev: clean build

build:
	gcc ./searching/binary-search.c -o ./searching/binary-search.sh -lm
clean:
	rm -rf ./searching/binary-search.sh
run:
	./searching/binary-search.sh