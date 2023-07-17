all: clean build run

dev: clean build

build:
	gcc ./trees/binary-tree/serde.c -o ./trees/binary-tree/serde.sh -lm
clean:
	rm -rf ./trees/binary-tree/serde.sh
run:
	./trees/binary-tree/serde.sh