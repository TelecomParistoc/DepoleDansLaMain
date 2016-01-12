main:
	@echo "gcc -Wall -Wextra -O3 main.c -o main"
	@touch main.o
	@touch main

clean:
	rm -rf main.o main

run: main
	@echo "Hello World !"
