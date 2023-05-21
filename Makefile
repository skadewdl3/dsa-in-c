all: clean build run

dev: clean build

build:
	gcc ./stack-new/postfix/infix-to-postfix.c -o ./stack-new/postfix/infix-to-postfix.sh -lm
clean:
	rm -rf ./stack-new/postfix/infix-to-postfix.sh
run:
	./stack-new/postfix/infix-to-postfix.sh