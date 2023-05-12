CFLAGS=-Wall -g
make:
	gcc -o main -Wall -g  main.c ip_maths.c
clean:
	rm -f main