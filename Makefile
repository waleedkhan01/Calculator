all: calc format

calc: calc.c
	gcc -lm -o calc calc.c 

format: format.c
	gcc -lm -o format format.c 

clean:
	rm calc format

target: dependencies
	command
