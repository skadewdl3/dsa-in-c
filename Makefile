all: clean build run

dev: clean build

build:
	gcc ./stack-new/prefix/infix-to-prefix.c -o ./stack-new/prefix/infix-to-prefix.sh -lm
clean:
	rm -rf ./stack-new/prefix/infix-to-prefix.sh
run:
	./stack-new/prefix/infix-to-prefix.sh