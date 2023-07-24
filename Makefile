all: clean build run

dev: clean build

build:
	gcc ./trees/binary-search-tree/bst.c -o ./trees/binary-search-tree/bst.sh -lm
clean:
	rm -rf ./trees/binary-search-tree/bst.sh
run:
	./trees/binary-search-tree/bst.sh