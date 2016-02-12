main:
	@echo "gcc -Wall -Wextra -O3 main.c -o main"
	@touch main.o
	@touch main

galette:
	gcc galette.c -Wall -Wextra -O2 -lrobotdriver -o galette
clean:
	rm -f galette main.o main

run: main
	@echo "Hello World !"
